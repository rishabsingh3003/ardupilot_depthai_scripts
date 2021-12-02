#!/usr/bin/env python3

import cv2
import depthai as dai
import numpy as np
from time import sleep
from pipeline import *

# Pipeline is defined, now we can connect to the device
with dai.Device(create_pipeline(), usb2Mode=False) as device:

    # Output queue will be used to get the depth frames from the outputs defined above
    spatialQueue = device.getOutputQueue(name="spatialData", maxSize=2, blocking=False)
    depthQueue = device.getOutputQueue(name="depth", maxSize=2, blocking=False)

    while True:
        inSpatialDatas = spatialQueue.tryGet()
        if (inSpatialDatas == None):
            continue
        spatialDatas = inSpatialDatas.getSpatialLocations()
        depthFrame = depthQueue.get().getFrame()

        for spatialData in spatialDatas:
            roi = spatialData.config.roi
            roi = roi.denormalize(width=depthFrame.shape[1], height=depthFrame.shape[0])
            avgDepth = spatialData.depthAverage # same as Z coordinate
            avgDepthPixelCount = spatialData.depthAveragePixelCount
            depthConfidence = avgDepthPixelCount/roi.area()
            # print(f"Depth confidence: {int(depthConfidence*100)}%")
            x = spatialData.spatialCoordinates.x
            y = spatialData.spatialCoordinates.y
            z = spatialData.spatialCoordinates.z
            euclideanDistance = np.sqrt(x*x + y*y + z*z)
            print(f"Euclidean distance {int(euclideanDistance)} mm, X: {int(x)} mm, Y: {int(y)} mm, Z: {int(z)} mm")


        depthFrameColor = cv2.normalize(depthFrame, None, 255, 0, cv2.NORM_INF, cv2.CV_8UC1)
        depthFrameColor = cv2.equalizeHist(depthFrameColor)
        depthFrameColor = cv2.applyColorMap(depthFrameColor, cv2.COLORMAP_JET)

        color = (255, 255, 255)
        for spatialData in spatialDatas:
            roi = spatialData.config.roi
            roi = roi.denormalize(width=depthFrameColor.shape[1], height=depthFrameColor.shape[0])
            xmin = int(roi.topLeft().x)
            ymin = int(roi.topLeft().y)
            xmax = int(roi.bottomRight().x)
            ymax = int(roi.bottomRight().y)

            avgDepth = spatialData.depthAverage # same as Z coordinate
            avgDepthPixelCount = spatialData.depthAveragePixelCount
            depthConfidence = avgDepthPixelCount/roi.area()
            fontType = cv2.FONT_HERSHEY_TRIPLEX
            cv2.rectangle(depthFrameColor, (xmin, ymin), (xmax, ymax), color, cv2.FONT_HERSHEY_SCRIPT_SIMPLEX)
            cv2.putText(depthFrameColor, f"X: {int(spatialData.spatialCoordinates.x)} mm", (xmin + 10, ymin + 20), fontType, 0.5, color)
            cv2.putText(depthFrameColor, f"Y: {int(spatialData.spatialCoordinates.y)} mm", (xmin + 10, ymin + 35), fontType, 0.5, color)
            cv2.putText(depthFrameColor, f"Z: {int(spatialData.spatialCoordinates.z)} mm", (xmin + 10, ymin + 50), fontType, 0.5, color)

            cv2.imshow("depth", depthFrameColor)

        if cv2.waitKey(1) == ord('q'):
            break
