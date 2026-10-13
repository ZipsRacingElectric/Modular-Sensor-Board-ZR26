// Header
#include "front_peripherals.h"

// Includes ------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"

// Global Peripherals --------------------------------------------------------------------------------------------------------

linearSensor_t damperPositionFl;
linearSensor_t damperPositionFr;

// Functions -----------------------------------------------------------------------------------------------------------------

bool frontPeripheralsInit(void)
{
    linearSensorInit (&damperPositionFl, &eepromMap->damperPositionFlConfig);
	linearSensorInit (&damperPositionFr, &eepromMap->damperPositionFrConfig);

    return true;
}

bool frontPeripheralsSample(void)
{
    max11614Results_t adcResults;

	if (!max11614ReadChannels (&adc, &adcResults, 0, 2))
		return false;

    analogSensorUpdate ((analogSensor_t*) &damperPositionFl, adcResults.channels [0], 4095);
	analogSensorUpdate ((analogSensor_t*) &damperPositionFr, adcResults.channels [1], 4095);

	return true;
}

