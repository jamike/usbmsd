#include "mbed.h"
#include "FATFileSystem.h" 
#include "SPIFBlockDevice.h"
#include "USBMSD_SPIF.h"
#include <stdio.h> 
#include <errno.h> 

/*  the device is waiting for host plug, and host removal */
void USB_stick () {
	USBMSD_SPIF spif(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);

	spif.connect(false);
	if (spif.configured())
		printf("usb device connected to host\n");
	else {
		printf("connect usb device to host\n");
		spif.connect(true);
		printf("usb device connected to host\n");
	}
	while(spif.configured())
		wait(1);
	printf("usb device disconnected\n");

}
void errno_error(void* ret_val){
	if (ret_val == NULL)
		printf(" Failure. %d \n", errno);
	else
		printf(" done.\n");
}

void format_nor()
{
	SPIFBlockDevice spif(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);
	FATFileSystem fs;
	printf("formating\n");
	int res=fs.format(&spif);
	if (res) {
		printf("formating error %d\n",res);
		while(1);
	}
	else  printf("format done\n");
	while(1);

}

void Local_fs ()
{
    SPIFBlockDevice spif(SPI_MOSI, SPI_MISO, SPI_SCK, SPI_CS);
    FATFileSystem fs("sd",&spif);
    printf("use filesystem locally\n");
    printf("Opening root directory\n");
    DIR* dir = opendir("/sd/");
    errno_error(dir);
    struct dirent* de;
    printf("Printing all filenames:\n");
    while((de = readdir(dir)) != NULL){
        printf("  %s\n", &(de->d_name)[0]);
    }
}


int main()
{
#ifdef FORMAT
	format_nor();
#else
	while(1) {
		USB_stick();
		Local_fs();
	}
#endif
}
