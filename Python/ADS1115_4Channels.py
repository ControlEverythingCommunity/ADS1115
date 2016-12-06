# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# ADS1115
# This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# ADS1115 address, 0x48(72)
# Select configuration register, 0x01(01)
#		0xC483(50307)	AINP = AIN0 and AINN = GND, +/- 2.048V
#				Continuous conversion mode, 128SPS
data = [0xC4,0x83]
bus.write_i2c_block_data(0x48, 0x01, data)

time.sleep(0.5)

# ADS1115 address, 0x48(72)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data
raw_adc = data[0] * 256 + data[1]

if raw_adc > 32767:
	raw_adc -= 65535

# Output data to screen
print "Digital Value of Analog Input on Channel-0: %d" %raw_adc

# ADS1115 address, 0x48(72)
# Select configuration register, 0x01(01)
#		0xD483(54403)	AINP = AIN1 and AINN = GND, +/- 2.048V
#				Continuous conversion mode, 128SPS
data = [0xD4,0x83]
bus.write_i2c_block_data(0x48, 0x01, data)

time.sleep(0.5)

# ADS1115 address, 0x48(72)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data
raw_adc = data[0] * 256 + data[1]

if raw_adc > 32767:
	raw_adc -= 65535

# Output data to screen
print "Digital Value of Analog Input on Channel-1: %d" %raw_adc

# ADS1115 address, 0x48(72)
# Select configuration register, 0x01(01)
#		0xE483(58499)	AINP = AIN2 and AINN = GND, +/- 2.048V
#				Continuous conversion mode, 128SPS
data = [0xE4,0x83]
bus.write_i2c_block_data(0x48, 0x01, data)

time.sleep(0.5)

# ADS1115 address, 0x48(72)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data
raw_adc = data[0] * 256 + data[1]

if raw_adc > 32767:
	raw_adc -= 65535

# Output data to screen
print "Digital Value of Analog Input on Channel-2: %d" %raw_adc

# ADS1115 address, 0x48(72)
# Select configuration register, 0x01(01)
#		0xF483(62595)	AINP = AIN3 and AINN = GND, +/- 2.048V
#				Continuous conversion mode, 128SPS
data = [0xF4,0x83]
bus.write_i2c_block_data(0x48, 0x01, data)

time.sleep(0.5)

# ADS1115 address, 0x48(72)
# Read data back from 0x00(00), 2 bytes
# raw_adc MSB, raw_adc LSB
data = bus.read_i2c_block_data(0x48, 0x00, 2)

# Convert the data
raw_adc = data[0] * 256 + data[1]

if raw_adc > 32767:
	raw_adc -= 65535

# Output data to screen
print "Digital Value of Analog Input on Channel-3: %d" %raw_adc
