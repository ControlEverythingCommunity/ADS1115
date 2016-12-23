/**************************************************************************/
/*
 Distributed with a free-will license.
 Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
 ADS1115
 This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
 https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2
*/
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Wire.h>

#include "ADS1115.h"

/**************************************************************************/
/*
        Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static uint8_t i2cread(void) {
#if ARDUINO >= 100
    return Wire.read();
#else
    return Wire.receive();
#endif
}

/**************************************************************************/
/*
        Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static void i2cwrite(uint8_t x) {
#if ARDUINO >= 100
    Wire.write((uint8_t)x);
#else
    Wire.send(x);
#endif
}

/**************************************************************************/
/*
        Writes 16-bits to the specified destination register
*/
/**************************************************************************/
static void writeRegister(uint8_t i2cAddress, uint8_t reg, uint16_t value)
{
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)reg);
  i2cwrite((uint8_t)(value>>8));
  i2cwrite((uint8_t)(value & 0xFF));
  Wire.endTransmission();
}

/**************************************************************************/
/*
        Reads 16-bits to the specified destination register
*/
/**************************************************************************/
static uint16_t readRegister(uint8_t i2cAddress, uint8_t reg)
{
  Wire.beginTransmission(i2cAddress);
  i2cwrite((uint8_t)reg);
  Wire.endTransmission();
  Wire.requestFrom(i2cAddress, (uint8_t)2);
  return (int16_t)((i2cread() << 8) | i2cread());
}

/**************************************************************************/
/*
        Instantiates a new ADS1115 class with appropriate properties
*/
/**************************************************************************/
ADS1115::ADS1115(uint8_t i2cAddress) 
{
    ads_i2cAddress = i2cAddress;
    ads_conversionDelay = ADS1115_CONVERSIONDELAY;
}

/**************************************************************************/
/*
        Sets up the Hardware
*/
/**************************************************************************/
void ADS1115::begin()
{
  Wire.begin();
}

/**************************************************************************/
/*
        Sets the Operational status/single-shot conversion start
        This determines the operational status of the device
*/
/**************************************************************************/
void ADS1115::setOSMode(adsOSMode_t osmode)
{
    ads_osmode = osmode;
}

/**************************************************************************/
/*
        Gets the Operational status/single-shot conversion start
*/
/**************************************************************************/
adsOSMode_t ADS1115::getOSMode()
{
    return ads_osmode;
}

/**************************************************************************/
/*
        Sets the gain and input voltage range
        This configures the programmable gain amplifier
*/
/**************************************************************************/
void ADS1115::setGain(adsGain_t gain)
{
  ads_gain = gain;
}

/**************************************************************************/
/*
        Gets a gain and input voltage range
*/
/**************************************************************************/
adsGain_t ADS1115::getGain()
{
  return ads_gain;
}

/**************************************************************************/
/*
        Sets the Device operating mode
        This controls the current operational mode of the ADS1115
*/
/**************************************************************************/
void ADS1115::setMode(adsMode_t mode)
{
    ads_mode = mode;
}

/**************************************************************************/
/*
        Gets the Device operating mode
*/
/**************************************************************************/
adsMode_t ADS1115::getMode()
{
    return ads_mode;
}

/**************************************************************************/
/*
        Sets the Date Rate
        This controls the data rate setting
*/
/**************************************************************************/
void ADS1115::setRate(adsRate_t rate)
{
    ads_rate = rate;
}

/**************************************************************************/
/*
        Gets the Date Rate
*/
/**************************************************************************/
adsRate_t ADS1115::getRate()
{
    return ads_rate;
}

/**************************************************************************/
/*
        Sets the Comparator mode
        This controls the comparator mode of operation
*/
/**************************************************************************/
void ADS1115::setCompMode(adsCompMode_t compmode)
{
    ads_compmode = compmode;
}

/**************************************************************************/
/*
        Gets the Comparator mode
*/
/**************************************************************************/
adsCompMode_t ADS1115::getCompMode()
{
    return ads_compmode;
}

/**************************************************************************/
/*
        Sets the Comparator polarity
        This controls the polarity of the ALERT/RDY pin
*/
/**************************************************************************/
void ADS1115::setCompPol(adsCompPol_t comppol)
{
    ads_comppol = comppol;
}

/**************************************************************************/
/*
        Gets the Comparator polarity
*/
/**************************************************************************/
adsCompPol_t ADS1115::getCompPol()
{
    return ads_comppol;
}

/**************************************************************************/
/*
        Sets the Latching comparator
        This controls whether the ALERT/RDY pin latches once asserted
        or clears once conversions are within the
        margin of the upper and lower threshold values
*/
/**************************************************************************/
void ADS1115::setCompLat(adsCompLat_t complat)
{
    ads_complat = complat;
}

/**************************************************************************/
/*
        Gets the Latching comparator
*/
/**************************************************************************/
adsCompLat_t ADS1115::getCompLat()
{
    return ads_complat;
}

/**************************************************************************/
/*
        Sets the Comparator queue and disable
        This perform two functions. 
        It can disable the comparator function and put the
        ALERT/RDY pin into a high state.
        It also can control the number of successive
        conversions exceeding the upper or lower thresholds 
        required before asserting the ALERT/RDY pin
*/
/**************************************************************************/
void ADS1115::setCompQue(adsCompQue_t compque)
{
    ads_compque = compque;
}

/**************************************************************************/
/*
        Gets the Comparator queue and disable
*/
/**************************************************************************/
adsCompQue_t ADS1115::getCompQue()
{
    return ads_compque;
}

/**************************************************************************/
/*
        Sets the low threshold value
*/
/**************************************************************************/
void ADS1115::setLowThreshold(int16_t threshold)
{
    ads_lowthreshold = threshold;
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_LOWTHRESH, ads_lowthreshold);
}

/**************************************************************************/
/*
        Gets the low threshold value
*/
/**************************************************************************/
int16_t ADS1115::getLowThreshold()
{
    return ads_lowthreshold;
}

/**************************************************************************/
/*
        Sets the high threshold value
*/
/**************************************************************************/
void ADS1115::setHighThreshold(int16_t threshold)
{
    ads_highthreshold = threshold;
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_HITHRESH, ads_highthreshold);
}

/**************************************************************************/
/*
        Gets the high threshold value
*/
/**************************************************************************/
int16_t ADS1115::getHighThreshold()
{
    return ads_highthreshold;
}

/**************************************************************************/
/*
        Reads the conversion results, measuring the voltage
        for a single-ended ADC reading from the specified channel
        Negative voltages cannot be applied to this circuit because the
        ADS1115 can only accept positive voltages
*/
/**************************************************************************/
uint16_t ADS1115::Measure_SingleEnded(uint8_t channel)
{
    if (channel > 3)
    {
        return 0;
    }
  
    // Start with default values
    uint16_t config =   ADS1115_REG_CONFIG_CQUE_NONE    |   // Disable the comparator (default val)
                        ADS1115_REG_CONFIG_CLAT_NONLAT  |   // Non-latching (default val)
                        ADS1115_REG_CONFIG_CPOL_ACTVLOW |   // Alert/Rdy active low   (default val)
                        ADS1115_REG_CONFIG_CMODE_TRAD;      // Traditional comparator (default val)
    
    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    
    // Set PGA/voltage range
    config |= ads_gain;
    
    // Set Device operating mode
    config |= ads_mode;
    
    // Set Data rate
    config |= ads_rate;

    // Set single-ended input channel
    switch (channel)
    {
        case (0):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_0;
            break;
        case (1):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_1;
            break;
        case (2):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_2;
            break;
        case (3):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_3;
            break;
    }

    // Write config register to the ADC
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONFIG, config);

    // Wait for the conversion to complete
    delay(ads_conversionDelay);

    // Read the conversion results
    // 16-bit unsigned results for the ADS1115
    return readRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONVERT);
}

/**************************************************************************/
/* 
        Reads the conversion results, measuring the voltage
        difference between the P (AIN#) and N (AIN#) input
        Generates a signed value since the difference can be either
        positive or negative
*/
/**************************************************************************/
int16_t ADS1115::Measure_Differential(uint8_t channel)
{
    // Start with default values
    uint16_t config =   ADS1115_REG_CONFIG_CQUE_NONE    |   // Disable the comparator (default val)
                        ADS1115_REG_CONFIG_CLAT_NONLAT  |   // Non-latching (default val)
                        ADS1115_REG_CONFIG_CPOL_ACTVLOW |   // Alert/Rdy active low   (default val)
                        ADS1115_REG_CONFIG_CMODE_TRAD;      // Traditional comparator (default val)
    
    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    
    // Set PGA/voltage range
    config |= ads_gain;
    
    // Set Device operating mode
    config |= ads_mode;
    
    // Set Data rate
    config |= ads_rate;
    
    // Set Differential input channel
    switch (channel)
    {
        case (01):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_0_1;  // AIN0 = P, AIN1 = N
            break;
        case (03):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_0_3;  // AIN0 = P, AIN3 = N
            break;
        case (13):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_1_3;  // AIN1 = P, AIN3 = N
            break;
        case (23):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_2_3;  // AIN2 = P, AIN3 = N
            break;
    }

    // Write config register to the ADC
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONFIG, config);

    // Wait for the conversion to complete
    delay(ads_conversionDelay);

    // Read the conversion results
    uint16_t raw_adc = readRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONVERT);
    return (int16_t)raw_adc;
}

/**************************************************************************/
/*
        Sets up the comparator causing the ALERT/RDY pin to assert
        (go from high to low) when the ADC value exceeds the 
        specified  upper or lower threshold
        ADC is single-ended input channel
*/
/**************************************************************************/
int16_t ADS1115::Comparator_SingleEnded(uint8_t channel)
{
    // Start with default values
    uint16_t config;

    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    
    // Set PGA/voltage range
    config |= ads_gain;
    
    // Set Device operating mode
    config |= ads_mode;
    
    // Set Data rate
    config |= ads_rate;
    
    // Set Comparator mode
    config |= ads_compmode;
    
    // Set Comparator polarity
    config |= ads_comppol;
    
    // Set Latching comparator
    config |= ads_complat;
    
    // Set Comparator queue and disable
    config |= ads_compque;
    
    // Set single-ended input channel
    switch (channel)
    {
        case (0):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_0;
            break;
        case (1):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_1;
            break;
        case (2):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_2;
            break;
        case (3):
            config |= ADS1115_REG_CONFIG_MUX_SINGLE_3;
            break;
    }

    // Write config register to the ADC
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONFIG, config);
                
    // Wait for the conversion to complete
    delay(ads_conversionDelay);
                
    // Read the conversion results
    uint16_t raw_adc = readRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONVERT);
    return (int16_t)raw_adc;
}

/**************************************************************************/
/*
        Sets up the comparator causing the ALERT/RDY pin to assert 
        (go from high to low) when the ADC value exceeds the 
        specified  upper or lower threshold
        ADC is Differential input channel
*/
/**************************************************************************/
int16_t ADS1115::Comparator_Differential(uint8_t channel)
{
    // Start with default values
    uint16_t config;
    
    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    
    // Set PGA/voltage range
    config |= ads_gain;
    
    // Set Device operating mode
    config |= ads_mode;
    
    // Set Data rate
    config |= ads_rate;
    
    // Set Comparator mode
    config |= ads_compmode;
    
    // Set Comparator polarity
    config |= ads_comppol;
    
    // Set Latching comparator
    config |= ads_complat;
    
    // Set Comparator queue and disable
    config |= ads_compque;
    
    // Set Differential input channel
    switch (channel)
    {
        case (01):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_0_1;  // AIN0 = P, AIN1 = N
            break;
        case (03):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_0_3;  // AIN0 = P, AIN3 = N
            break;
        case (13):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_1_3;  // AIN1 = P, AIN3 = N
            break;
        case (23):
            config |= ADS1115_REG_CONFIG_MUX_DIFF_2_3;  // AIN2 = P, AIN3 = N
            break;
    }
    
    // Write config register to the ADC
    writeRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONFIG, config);
    
    // Wait for the conversion to complete
    delay(ads_conversionDelay);
    
    // Read the conversion results
    uint16_t raw_adc = readRegister(ads_i2cAddress, ADS1115_REG_POINTER_CONVERT);
    return (int16_t)raw_adc;
}
