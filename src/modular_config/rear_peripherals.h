#ifndef REAR_PERIPHERALS_H
#define REAR_PERIPHERALS_H

// Includes ------------------------------------------------------------------------------------------------------------------

#include "peripherals/adc/analog_linear.h"
#include "peripherals/adc/thermistor_pulldown.h"

// Globals --------------------------------------------------------------------------------------------------------------------

/// @brief The RL damper position sensor. Installed on ADC channel 0.
extern linearSensor_t damperPositionRl;

/// @brief The RR damper position sensor. Installed on ADC channel 1.
extern linearSensor_t damperPositionRr;

/// @brief The 0th cooling temperature sensor. Installed on ADC channel 2.
extern thermistorBetaPulldown_t thermistor0;

/// @brief The 1st cooling temperature sensor. Installed on ADC channel 3.
extern thermistorBetaPulldown_t thermistor1;

/// @brief The 2nd cooling temperature sensor. Installed on ADC channel 4.
extern thermistorBetaPulldown_t thermistor2;

/// @brief The 3rd cooling temperature sensor. Installed on ADC channel 5.
extern thermistorBetaPulldown_t thermistor3;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the Modular Sensor Board's peripherals.
 * @return true if successful, false if a hardware error occurred.
 */
bool rearPeripheralsInit (void);

/**
 * @brief Samples the latest value of the MSB's peripherals.
 * @return True if successful, false if a hardware error occurred.
 */
bool rearPeripheralsSample (void);
#endif // REAR_PERIPHERALS_H