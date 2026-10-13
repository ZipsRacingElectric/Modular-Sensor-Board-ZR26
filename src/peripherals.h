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

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the Modular Sensor Board's peripherals.
 * @return true if successful, false if a hardware error occurred.
 */
bool peripheralsInit (void);

#endif // PERIPHERALS_H