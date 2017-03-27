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

#include "USBMSD_SPIF.h"
#include "mbed_debug.h"
/*  value from USBMSD class */
#define DISK_OK         0x00
#define NO_INIT         0x01
#define NO_DISK         0x02


USBMSD_SPIF::USBMSD_SPIF(PinName mosi, PinName miso, PinName sclk, PinName cs, int freq, uint16_t vendor_id , uint16_t product_id , uint16_t product_release):
    USBMSD(vendor_id , product_id, product_release),
    SPIFBlockDevice(mosi, miso, sclk, cs, freq ),
    initialized(false)
{

}

int USBMSD_SPIF::disk_initialize()
{
    int ret = 0;
    if (!initialized) {
        ret = init();
        initialized = true;
        number_of_sector = disk_sectors();
        sector_size =get_erase_size();
    }
    return ret;
}

int USBMSD_SPIF::disk_write(const uint8_t *buffer, uint64_t block_number, uint8_t count)
{
    bd_size_t ssize = sector_size;
    if (block_number < number_of_sector) {

        int res = erase(block_number*ssize,count*ssize);
        if (res) return res;
        return program(buffer, block_number*ssize, count*ssize);
    }
    else return 1;
}

int USBMSD_SPIF::disk_read(uint8_t *buffer, uint64_t block_number, uint8_t count)
{
    bd_size_t ssize = sector_size;
    if (block_number < number_of_sector)
        return read(buffer, block_number*ssize, count*ssize);
    else
        return 1;
}

int USBMSD_SPIF::disk_status()
{
    if (initialized)
        return DISK_OK;
    else
        return NO_INIT;
}

int USBMSD_SPIF::disk_sync()
{
    return 0;
}

uint64_t USBMSD_SPIF::disk_sectors()
{
    uint64_t block = ((uint64_t)get_erase_size());
    uint64_t total = ((uint64_t )size());
    uint64_t number = total/block;
    return number;
}
