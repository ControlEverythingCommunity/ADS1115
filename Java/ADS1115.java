// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1115
// This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class ADS1115
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, ADS1115 I2C address is 0x48(72)
		I2CDevice device = bus.getDevice(0x48);
		
		byte[] config = {(byte)0x84, (byte)0x83};
		// Select configuration register
		// AINP = AIN0 and AINN = AIN1, +/- 2.048V, Continuous conversion mode, 128 SPS
		device.write(0x01, config, 0, 2);
		Thread.sleep(500);
		
		// Read 2 bytes of data
		// raw_adc msb, raw_adc lsb
		byte[] data = new byte[2];
		device.read(0x00, data, 0, 2);
		
		// Convert the data
		int raw_adc = ((data[0] & 0xFF) * 256) + (data[1] & 0xFF);
		if (raw_adc > 32767)
		{
			raw_adc -= 65535;
		}

		// Output data to screen
		System.out.printf("Digital Value of Analog Input : %d %n", raw_adc);
	}
}
