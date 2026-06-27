#ifndef PERIPHERALS_H
#define PERIPHERALS_H

// Modular Sensor Board Peripherals -------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.27
//
// Description: Code representing on-board hardware and sensors wired into the modular sensor board.

// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "peripherals/eeprom_map.h"
#include "peripherals/interface/eeprom.h"
#include "peripherals/i2c/mc24lc32.h"
#include "peripherals/i2c/max11614.h"
#include "peripherals/adc/analog_linear.h"
#include "peripherals/adc/thermistor_pulldown.h"

// Globals --------------------------------------------------------------------------------------------------------------------

/// @brief The device's 'virtual' EEPROM. This aggregates the physical EEPROM's memory with readonly / writeonly EEPROM's
/// memory.
extern virtualEeprom_t virtualEeprom;

/// @brief The actual EEPROM installed on the device. This is used for storing permanent data.
extern mc24lc32_t physicalEeprom;

/// @brief A 'virtual' EEPROM used for reading temporary data or executing commands.
extern eeprom_t readonlyWriteonlyEeprom;

/// @brief A 'map' of the physical EEPROM's memory. Used for reading data from its cache.
extern eepromMap_t* eepromMap;

/// @brief The I2C ADC installed on the ADC daughter board.
extern max11614_t adc;

/// @brief The RL damper position sensor. Installed on ADC channel 0.
extern linearSensor_t damperPositionRl;

/// @brief The RR damper position sensor. Installed on ADC channel 1.
extern linearSensor_t damperPositionRr;

/// @brief The FL damper position sensor. Installed on ADC channel 6.
extern linearSensor_t damperPositionFl;

/// @brief The FR damper position sensor. Installed on ADC channel 7.
extern linearSensor_t damperPositionFr;

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
bool peripheralsInit (void);

/**
 * @brief Samples the latest value of the MSB's peripherals.
 * @return True if successful, false if a hardware error occurred.
 */
bool peripheralsSample (void);

#endif // PERIPHERALS_H