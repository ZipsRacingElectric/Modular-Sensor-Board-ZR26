// Header
#include "rear_peripherals.h"

// Includes ------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"

// Global Peripherals ---------------------------------------------------------------------------------------------------------

linearSensor_t damperPositionRl;
linearSensor_t damperPositionRr;

thermistorBetaPulldown_t thermistor0;
thermistorBetaPulldown_t thermistor1;
thermistorBetaPulldown_t thermistor2;
thermistorBetaPulldown_t thermistor3;

// Functions -------------------------------------------------------------------------------------------------------------------

bool rearPeripheralsInit(void)
{ 
    linearSensorInit (&damperPositionRl, &eepromMap->damperPositionRlConfig);
    linearSensorInit (&damperPositionRr, &eepromMap->damperPositionRrConfig);
    thermistorBetaPulldownInit (&thermistor0, &eepromMap->thermistorConfig);
    thermistorBetaPulldownInit (&thermistor1, &eepromMap->thermistorConfig);
    thermistorBetaPulldownInit (&thermistor2, &eepromMap->thermistorConfig);
    thermistorBetaPulldownInit (&thermistor3, &eepromMap->thermistorConfig);

    return true;
}

bool rearPeripheralsSample(void)
{
    max11614Results_t adcResults;

	if (!max11614ReadChannels (&adc, &adcResults, 0, 6))
		return false;

	analogSensorUpdate ((analogSensor_t*) &damperPositionRl, adcResults.channels [0], 4095);
	analogSensorUpdate ((analogSensor_t*) &damperPositionRr, adcResults.channels [1], 4095);
	analogSensorUpdate ((analogSensor_t*) &thermistor0, adcResults.channels [2], 4095);
	analogSensorUpdate ((analogSensor_t*) &thermistor1, adcResults.channels [3], 4095);
	analogSensorUpdate ((analogSensor_t*) &thermistor2, adcResults.channels [4], 4095);
	analogSensorUpdate ((analogSensor_t*) &thermistor3, adcResults.channels [5], 4095);

	return true;
}