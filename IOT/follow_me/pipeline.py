#!/usr/bin/env python3

from pathlib import Path
import cv2
import depthai as dai
import numpy as np
import time

import blobconverter

def create_pipeline():
    # Create pipeline
    pipeline = dai.Pipeline()

    # Define sources and outputs
    camRgb = pipeline.create(dai.node.ColorCamera)
    spatialDetectionNetwork = pipeline.create(dai.node.MobileNetSpatialDetectionNetwork)
    monoLeft = pipeline.create(dai.node.MonoCamera)
    monoRight = pipeline.create(dai.node.MonoCamera)
    stereo = pipeline.create(dai.node.StereoDepth)
    objectTracker = pipeline.create(dai.node.ObjectTracker)

    xoutRgb = pipeline.create(dai.node.XLinkOut)
    trackerOut = pipeline.create(dai.node.XLinkOut)

    xoutRgb.setStreamName("preview")
    trackerOut.setStreamName("tracklets")

    # Properties
    camRgb.setPreviewSize(544, 320)
    camRgb.setResolution(dai.ColorCameraProperties.SensorResolution.THE_1080_P)
    camRgb.setInterleaved(False)
    camRgb.setColorOrder(dai.ColorCameraProperties.ColorOrder.BGR)

    monoLeft.setResolution(dai.MonoCameraProperties.SensorResolution.THE_400_P)
    monoLeft.setBoardSocket(dai.CameraBoardSocket.LEFT)
    monoRight.setResolution(dai.MonoCameraProperties.SensorResolution.THE_400_P)
    monoRight.setBoardSocket(dai.CameraBoardSocket.RIGHT)

    # setting node configs
    stereo.initialConfig.setConfidenceThreshold(190)
    lrcheck = True
    subpixel = True

    stereo.setLeftRightCheck(lrcheck)
    stereo.setSubpixel(subpixel)
    stereo.initialConfig.setMedianFilter(dai.MedianFilter.KERNEL_7x7)

    spatialDetectionNetwork.setBlobPath(str(blobconverter.from_zoo(name="person-detection-retail-0013", shaves=4)))
    spatialDetectionNetwork.setConfidenceThreshold(0.6)
    spatialDetectionNetwork.input.setBlocking(False)
    spatialDetectionNetwork.setBoundingBoxScaleFactor(0.5)
    spatialDetectionNetwork.setDepthLowerThreshold(200)
    spatialDetectionNetwork.setDepthUpperThreshold(10000)

    # objectTracker.setDetectionLabelsToTrack([15])  # track only person
    # possible tracking types: ZERO_TERM_COLOR_HISTOGRAM, ZERO_TERM_IMAGELESS
    objectTracker.setTrackerType(dai.TrackerType.ZERO_TERM_COLOR_HISTOGRAM)
    # take the smallest ID when new object is tracked, possible options: SMALLEST_ID, UNIQUE_ID
    objectTracker.setTrackerIdAssigmentPolicy(dai.TrackerIdAssigmentPolicy.SMALLEST_ID)
    objectTracker.setMaxObjectsToTrack(1)

    # Linking
    monoLeft.out.link(stereo.left)
    monoRight.out.link(stereo.right)

    camRgb.preview.link(spatialDetectionNetwork.input)
    objectTracker.passthroughTrackerFrame.link(xoutRgb.input)
    objectTracker.out.link(trackerOut.input)

    spatialDetectionNetwork.passthrough.link(objectTracker.inputTrackerFrame)
    objectTracker.inputTrackerFrame.setBlocking(False)
    # do not block the pipeline if it's too slow on full frame
    objectTracker.inputTrackerFrame.setQueueSize(2)

    spatialDetectionNetwork.passthrough.link(objectTracker.inputDetectionFrame)
    spatialDetectionNetwork.out.link(objectTracker.inputDetections)
    stereo.depth.link(spatialDetectionNetwork.inputDepth)

    # Send tracklets via SPI to the MCU
    spiOut = pipeline.create(dai.node.SPIOut)
    spiOut.setStreamName("tracklets")
    spiOut.setBusId(0)
    spiOut.input.setBlocking(False)
    spiOut.input.setQueueSize(4)

    objectTracker.out.link(spiOut.input)
    return pipeline

