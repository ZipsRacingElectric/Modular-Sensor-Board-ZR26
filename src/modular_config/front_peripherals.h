#ifndef FRONT_PERIPHERALS_H
#define FRONT_PERIPHERALS_H

// Includes ------------------------------------------------------------------------------------------------------------------

#include "peripherals/adc/analog_linear.h"
#include "peripherals/adc/thermistor_pulldown.h"

// Globals ------------------------------------------------------------------------------------------------------------------

/// @brief The FL damper position sensor. Installed on ADC channel 0.
extern linearSensor_t damperPositionFl;

/// @brief The FR damper position sensor. Installed on ADC channel 1.
extern linearSensor_t damperPositionFr;

// Functions ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the Modular Sensor Board's peripherals.
 * @return true if successful, false if a hardware error occurred.
 */
bool frontPeripheralsInit (void);

/**
 * @brief Samples the latest value of the MSB's peripherals.
 * @return True if successful, false if a hardware error occurred.
 */
bool frontPeripheralsSample (void);

#endif // FRONT_PERIPHERALS_H