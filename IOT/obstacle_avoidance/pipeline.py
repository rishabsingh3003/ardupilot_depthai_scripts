#!/usr/bin/env python3

from pathlib import Path
import cv2
import depthai as dai
import numpy as np
import time

import blobconverter

def create_pipeline():
    # Start defining a pipeline
    pipeline = dai.Pipeline()

    # Create color camera
    camRgb = pipeline.createColorCamera()
    camRgb.setPreviewSize(300, 300)
    camRgb.setInterleaved(False)

    # Create mono cameras for StereoDepth
    left = pipeline.create(dai.node.MonoCamera)
    left.setResolution(dai.MonoCameraProperties.SensorResolution.THE_400_P)
    left.setBoardSocket(dai.CameraBoardSocket.LEFT)

    right = pipeline.create(dai.node.MonoCamera)
    right.setResolution(dai.MonoCameraProperties.SensorResolution.THE_400_P)
    right.setBoardSocket(dai.CameraBoardSocket.RIGHT)

    # StereoDepth
    stereo = pipeline.createStereoDepth()
    stereo.initialConfig.setConfidenceThreshold(130)
    stereo.initialConfig.setLeftRightCheckThreshold(150)
    # Setting node configs
    lrcheck = True
    subpixel = True

    stereo.setLeftRightCheck(lrcheck)
    stereo.setSubpixel(subpixel)
    stereo.initialConfig.setMedianFilter(dai.MedianFilter.KERNEL_7x7)

    left.out.link(stereo.left)
    right.out.link(stereo.right)

    spatialLocationCalculator = pipeline.create(dai.node.SpatialLocationCalculator)
    spatialLocationCalculator.setWaitForConfigInput(False)

    # Link StereoDepth to spatialLocationCalculator
    stereo.depth.link(spatialLocationCalculator.inputDepth)
    # Set initial config for the spatialLocationCalculator
    config = dai.SpatialLocationCalculatorConfigData()
    config.depthThresholds.lowerThreshold = 200
    config.depthThresholds.upperThreshold = 15000
    config.calculationAlgorithm = dai.SpatialLocationCalculatorAlgorithm.MIN

    # Set ROI
    for i in range(3):
        topLeft = dai.Point2f((i%3)*0.3, 0.20)
        bottomRight = dai.Point2f(((i%3)+1)*0.3, (int(i/3) + 1)*0.3)
        config.roi = dai.Rect(topLeft, bottomRight)
        spatialLocationCalculator.initialConfig.addROI(config)

    for i in range(3,6):
        topLeft = dai.Point2f((i%3)*0.3, (int(i/3))*0.3)
        bottomRight = dai.Point2f(((i%3)+1)*0.3, (int(i/3) + 1)*0.3)
        config.roi = dai.Rect(topLeft, bottomRight)
        spatialLocationCalculator.initialConfig.addROI(config)

    for i in range(6,9):
        topLeft = dai.Point2f((i%3)*0.3, (int(i/3))*0.3)
        bottomRight = dai.Point2f(((i%3)+1)*0.3, 0.8)
        config.roi = dai.Rect(topLeft, bottomRight)
        spatialLocationCalculator.initialConfig.addROI(config)

    # Send depth frames to the host
    xoutDepth = pipeline.createXLinkOut()
    xoutDepth.setStreamName("depth")
    spatialLocationCalculator.passthroughDepth.link(xoutDepth.input)

    # Send spatialLocationCalculator data to the host through the XLink
    xoutSpatialData = pipeline.createXLinkOut()
    xoutSpatialData.setStreamName("spatialData")
    spatialLocationCalculator.out.link(xoutSpatialData.input)

    # Send spatialLocationCalculator data through the SPI
    spiOutSpatialData = pipeline.create(dai.node.SPIOut)
    spiOutSpatialData.setStreamName("spatialData")
    spiOutSpatialData.setBusId(0)
    spiOutSpatialData.input.setBlocking(False)
    spiOutSpatialData.input.setQueueSize(4)
    spatialLocationCalculator.out.link(spiOutSpatialData.input)

    return pipeline

