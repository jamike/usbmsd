# usbmsd
NUCLEO_F303ZE USBMSD MBED
#prior to build
mbed new . -v
mbed deploy -v
cd mbed-os
git checkout -b test 75f6f2db30db5e4de90e63b989e6557df02b6958
git am ../configs/00*
cd ..
#build
./build.sh 
#flash 
format.bin : format NOR flash
usbmsd.bin : usb mass storage example
