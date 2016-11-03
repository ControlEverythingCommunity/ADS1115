// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1115
// This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main() 
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if ((file = open(bus, O_RDWR)) < 0) 
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, ADS1115 I2C address is 0x48(72)
	ioctl(file, I2C_SLAVE, 0x48);

	// Select configuration register(0x01)
	// AINP = AIN0 and AINN = AIN1, +/- 2.048V
	// Continuous conversion mode, 128 SPS(0x84, 0x83)
	char config[3] = {0};
	config[0] = 0x01;
	config[1] = 0x84;
	config[2] = 0x83;
	write(file, config, 3);
	sleep(1);

	// Read 2 bytes of data from register(0x00)
	// raw_adc msb, raw_adc lsb
	char reg[1] = {0x00};
	write(file, reg, 1);
	char data[2]={0};
	if(read(file, data, 2) != 2)
	{
		printf("Error : Input/Output Error \n");
	}
	else 
	{
		// Convert the data
		int raw_adc = (data[0] * 256 + data[1]);
		if (raw_adc > 32767)
		{
			raw_adc -= 65535;
		}

		// Output data to screen
		printf("Digital Value of Analog Input: %d \n", raw_adc);
	}
}
