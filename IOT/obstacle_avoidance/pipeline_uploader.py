import cv2
import numpy as np
import depthai as dai
import sys
from time import sleep
import blobconverter
from pipeline import *

def create_spi_demo_pipeline():
    print("Creating SPI pipeline: ")
    return create_pipeline()

def flash_bootloader():
    (f, bl) = dai.DeviceBootloader.getFirstAvailableDevice()
    bootloader = dai.DeviceBootloader(bl, allowFlashingBootloader= True)
    print(bootloader.getVersion())

    progress = lambda p : print(f'Flashing progress: {p*100:.1f}%')
    bootloader.flashBootloader(progress)


def flash_image():
    pipeline = create_spi_demo_pipeline()
    (found, bl) = dai.DeviceBootloader.getFirstAvailableDevice()

    if(found):
        bootloader = dai.DeviceBootloader(bl)
        progress = lambda p : print(f'Flashing progress: {p*100:.1f}%')
        bootloader.flash(progress, pipeline)
    else:
        print("No booted (bootloader) devices found...")

def write_image_to_file(filename):
    pipeline = create_spi_demo_pipeline()
    dai.DeviceBootloader.saveDepthaiApplicationPackage(filename, pipeline)

if(len(sys.argv) >= 2 and sys.argv[1] == "bootloader"):
    print("flashing bootloader")
    flash_bootloader()
elif(len(sys.argv) >= 2 and sys.argv[1] == "save"):
    filename = "pipeline.dap"
    print("saving pipeline to disk as " + filename)
    write_image_to_file(filename)
else:
    print("flashing pipeline")
    flash_image()
