#ifndef EEPROM_MAP_H
#define EEPROM_MAP_H

// EEPROM Map -----------------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.11
//
// Description: EEPROM Map for the Modular Sensor Board

// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "peripherals/adc/analog_linear.h"
#include "peripherals/adc/thermistor_pulldown.h"

// Datatypes ------------------------------------------------------------------------------------------------------------------

typedef struct
{
	/// @brief First 16 bytes on EEPROM reserved for magic string
	uint8_t pad0 [16];

	/// @brief Configuration of the RL damper position sensor. Address 0x0010
	linearSensorConfig_t damperPositionRlConfig;

	/// @brief Configuration of the RR damper position sensor. Address 0x001C
	linearSensorConfig_t damperPositionRrConfig;

	/// @brief Configuration of the cooling temp sensors. Address 0x0028
	thermistorBetaPulldownConfig_t thermistorConfig;

	/// @brief Configuration of the FL damper position sensor. Address 0x0040
	linearSensorConfig_t damperPositionFlConfig;

	/// @brief Configuration of the FR damper position sensor. Address 0x004C
	linearSensorConfig_t damperPositionFrConfig;
} eepromMap_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/// @brief Handles a write to the 'write-only' section of the device's virtual EEPROM.
/// @note Currently is not implemented.
bool writeonlyWrite (void* eeprom, uint16_t addr, const void* data, uint16_t dataCount);

/// @brief Handles a read from the 'read-only' section of the device's virtual EEPROM.
/// @note Used for reading temporary data.
bool readonlyRead (void* eeprom, uint16_t addr, void* data, uint16_t dataCount);

#endif // EEPROM_MAP_H