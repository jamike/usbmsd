/* mbed USBMSD_SD Library, for providing file access to SD cards
 * Copyright (c) 2008-2010, sford
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef USBMSD_SD_H
#define USBMSD_SD_H

#include "mbed.h"
#include "USBMSD.h"
#include "SDBlockDevice.h" 

class USBMSD_SD : public USBMSD , public SDBlockDevice {
public:

    /** Create the File System for accessing an SD Card using SPI
     *
     * @param mosi SPI mosi pin connected to SD Card
     * @param miso SPI miso pin conencted to SD Card
     * @param sclk SPI sclk pin connected to SD Card
     * @param cs   DigitalOut pin used as SD Card chip select
     * @param name The name used to access the virtual filesystem
     */
    USBMSD_SD(PinName mosi, PinName miso, PinName sclk, PinName cs, uint16_t vendor_id = 0x0703, uint16_t product_id = 0x0104, uint16_t product_release = 0x0001);
protected:
    virtual int disk_initialize();
    virtual int disk_status();
    virtual int disk_read(uint8_t * buffer, uint64_t block_number, uint8_t count);
    virtual int disk_write(const uint8_t * buffer, uint64_t block_number, uint8_t count);
    virtual int disk_sync();
    virtual uint64_t disk_sectors();
    virtual uint64_t disk_size(){return size();};
    bool initialized;
};

#endif
