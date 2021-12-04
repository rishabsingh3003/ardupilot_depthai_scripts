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

    spatialDetectionNetwork.setBlobPath(str(Path("utils/landing_target.blob").resolve().absolute()))
    spatialDetectionNetwork.setConfidenceThreshold(0.4)
    spatialDetectionNetwork.input.setBlocking(False)
    spatialDetectionNetwork.setBoundingBoxScaleFactor(0.5)
    spatialDetectionNetwork.setDepthLowerThreshold(200)
    spatialDetectionNetwork.setDepthUpperThreshold(10000)

    # objectTracker.setDetectionLabelsToTrack([15])  # track only person
    # possible tracking types: ZERO_TERM_COLOR_HISTOGRAM, ZERO_TERM_IMAGELESS
    objectTracker.setTrackerType(dai.TrackerType.ZERO_TERM_IMAGELESS)
    # take the smallest ID when new object is tracked, possible options: SMALLEST_ID, UNIQUE_ID
    objectTracker.setTrackerIdAssigmentPolicy(dai.TrackerIdAssigmentPolicy.SMALLEST_ID)
    objectTracker.setMaxObjectsToTrack(4)

    # Linking
    monoLeft.out.link(stereo.left)
    monoRight.out.link(stereo.right)

    manip = pipeline.create(dai.node.ImageManip)
    manip.initialConfig.setFrameType(dai.ImgFrame.Type.BGR888p)
    manip.initialConfig.setResize(300, 300)
    monoLeft.out.link(manip.inputImage)


    manip.out.link(spatialDetectionNetwork.input)
    objectTracker.passthroughTrackerFrame.link(xoutRgb.input)
    objectTracker.out.link(trackerOut.input)

    manip.out.link(objectTracker.inputTrackerFrame)
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

