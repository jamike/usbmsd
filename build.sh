#!/bin/bash - 
# prior to build the patch from configs dir must be apply on mbed-os
# cd mbed-os
# git am ../configs/000*.patch
mbed compile -m NUCLEO_F303ZE -t GCC_ARM --profile mbed-os/tools/profiles/debug.json -DFORMAT
cp BUILD/NUCLEO_F303ZE/GCC_ARM/usbmsd.bin format.bin
touch main.cpp
mbed compile -m NUCLEO_F303ZE -t GCC_ARM --profile mbed-os/tools/profiles/debug.json 
cp  BUILD/NUCLEO_F303ZE/GCC_ARM/usbmsd.bin usbmsd.bin

