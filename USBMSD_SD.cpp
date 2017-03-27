/* mbed Microcontroller Library
 * Copyright (c) 2006-2012 ARM Limited
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
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */ 

#include "USBMSD_SD.h"
#include "mbed_debug.h"
/*  value from USBMSD class */
#define DISK_OK         0x00
#define NO_INIT         0x01
#define NO_DISK         0x02


USBMSD_SD::USBMSD_SD(PinName mosi, PinName miso, PinName sclk, PinName cs, uint16_t vendor_id , uint16_t product_id , uint16_t product_release):
    USBMSD(vendor_id , product_id, product_release),
    SDBlockDevice(mosi, miso, sclk, cs ),
    initialized(false)
{
       connect(true);
}

int USBMSD_SD::disk_initialize()
{
    int ret = 0;
    if (!initialized) {
        ret = init();
        initialized = true;
    }
    return ret;
}

int USBMSD_SD::disk_write(const uint8_t *buffer, uint64_t block_number, uint8_t count)
{
    bd_size_t ssize = get_erase_size();
    int res = erase(block_number*ssize,count*ssize);
    if (res) return res;
    return program(buffer, block_number*ssize, count*ssize);
}

int USBMSD_SD::disk_read(uint8_t *buffer, uint64_t block_number, uint8_t count)
{
    bd_size_t ssize = get_erase_size();
    return read(buffer, block_number*ssize, count*ssize);
}

int USBMSD_SD::disk_status()
{
    if (initialized)
        return DISK_OK;
    else
        return NO_INIT;
}

int USBMSD_SD::disk_sync() { return 0; }
uint64_t USBMSD_SD::disk_sectors()
{
	uint64_t number = size()/ get_program_size();
	return number;
}



