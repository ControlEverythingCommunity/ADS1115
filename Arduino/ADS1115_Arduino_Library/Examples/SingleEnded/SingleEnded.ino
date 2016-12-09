/**************************************************************************/
/*
Distributed with a free-will license.
Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
ADS1115
This code is designed to work with the ADS1115_I2CADC I2C Mini Module available from ControlEverything.com.
https://www.controleverything.com/content/Analog-Digital-Converters?sku=ADS1115_I2CADC#tabs-0-product_tabset-2
*/
/**************************************************************************/

#include <Wire.h>
#include <ADS1115.h>

ADS1115 ads;

void setup(void) 
{
    Serial.begin(9600);

    // The ADC gain (PGA), Device operating mode, Data rate
    // can be changed via the following functions

    ads.setGain(GAIN_TWO);          // 2x gain   +/- 2.048V  1 bit = 0.0625mV (default)
    //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 0.1875mV
    // ads.setGain(GAIN_ONE);       // 1x gain   +/- 4.096V  1 bit = 0.125mV
    // ads.setGain(GAIN_FOUR);      // 4x gain   +/- 1.024V  1 bit = 0.03125mV
    // ads.setGain(GAIN_EIGHT);     // 8x gain   +/- 0.512V  1 bit = 0.015625mV
    // ads.setGain(GAIN_SIXTEEN);   // 16x gain  +/- 0.256V  1 bit = 0.0078125mV

    ads.setMode(MODE_CONTIN);       // Continuous conversion mode
    // ads.setMode(MODE_SINGLE);    // Power-down single-shot mode (default)

    ads.setRate(RATE_128);          // 128SPS (default)
    // ads.setRate(RATE_8);         // 8SPS
    // ads.setRate(RATE_16);        // 16SPS
    // ads.setRate(RATE_32);        // 32SPS
    // ads.setRate(RATE_64);        // 64SPS
    // ads.setRate(RATE_250);       // 250SPS
    // ads.setRate(RATE_475);       // 475SPS
    // ads.setRate(RATE_860);       // 860SPS

    ads.setOSMode(OSMODE_SINGLE);   // Set to start a single-conversion

    ads.begin();
}

void loop(void) 
{
    int16_t adc0, adc1, adc2, adc3;

    Serial.println("Getting single-ended readings from AIN0..3");
    adc0 = ads.Measure_SingleEnded(0);
    Serial.print("Digital Value of Analog Input at Channel 1: ");
    Serial.println(adc0);
    adc1 = ads.Measure_SingleEnded(1);
    Serial.print("Digital Value of Analog Input at Channel 2: ");
    Serial.println(adc1);
    adc2 = ads.Measure_SingleEnded(2);
    Serial.print("Digital Value of Analog Input at Channel 3: ");
    Serial.println(adc2);
    adc3 = ads.Measure_SingleEnded(3);
    Serial.print("Digital Value of Analog Input at Channel 4: ");
    Serial.println(adc3);

    Serial.println("        ****************************************        ");
    Serial.println(" ");

    delay(1000);
}
