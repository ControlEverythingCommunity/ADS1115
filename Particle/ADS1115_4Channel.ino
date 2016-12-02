// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// ADS1115
// This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// ADS1115 I2C address is 0x48(72)
#define Addr 0x48

int raw_adc = 0;
void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "ADS1115");
  Particle.variable("raw_adc", raw_adc);

  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);
}

void loop()
{
  unsigned int data[2];

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN0 and AINN = AIN1, +/- 2.048V
  Wire.write(0x84);
  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  float raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65535;
  }

  // Output data to dashboard
  Particle.publish("Digital value on AIN0 & AIN1:", String(raw_adc));
  delay(1000);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN0 and AINN = AIN3, +/- 2.048V
  Wire.write(0x94);
  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65535;
  }

  // Output data to dashboard
  Particle.publish("Digital value on AIN0 & AIN3:", String(raw_adc));
  delay(1000);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN1 and AINN = AIN3, +/- 2.048V
  Wire.write(0xA4);
  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65535;
  }

  // Output data to dashboard
  Particle.publish("Digital value on AIN1 & AIN3:", String(raw_adc));
  delay(1000);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select configuration register
  Wire.write(0x01);
  // AINP = AIN2 and AINN = AIN3, +/- 2.048V
  Wire.write(0xB4);
  // Continuous conversion mode, 128 SPS
  Wire.write(0x83);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();

  // Request 2 bytes of data
  Wire.requestFrom(Addr, 2);

  // Read 2 bytes of data
  // raw_adc msb, raw_adc lsb
  if (Wire.available() == 2)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
  }

  // Convert the data
  raw_adc = (data[0] * 256.0) + data[1];
  if (raw_adc > 32767)
  {
    raw_adc -= 65535;
  }

  // Output data to dashboard
  Particle.publish("Digital value on AIN2 & AIN3:", String(raw_adc));
  delay(1000);
}
