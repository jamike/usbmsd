# USB Mass Storage example

This basic example shows how to use a Serial NOR Flash using USB Mass Storage class.

It has been tested on the NUCLEO_F303ZE platform only.

## Clone the project

`git clone https://github.com/jamike/usbmsd.git`

## Download all libraries

All these steps below must be done prior to build

`cd usbmsd`

`mbed new . -v`

`mbed deploy -v`

## Apply patches on mbed-os

`cd mbed-os`

`git checkout -b test 75f6f2db30db5e4de90e63b989e6557df02b6958`

`git am ../configs/00*`

## Build the example

`cd ..`

`./build.sh`

Two bin files are created in the usbmsd/ root folder:

`format.bin` : use this file to format the Serial NOR Flash

`usbmsd.bin` : use this file as usb mass storage example

