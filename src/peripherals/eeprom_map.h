#ifndef EEPROM_MAP_H
#define EEPROM_MAP_H

// EEPROM Map --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.11
//
// Description: EEPROM Map for the Modular Sensor Board

// Includes --------------------------------------------------------------------------------------------------------------------------------

#include "peripherals/i2c/mc24lc32.h"
#include "adc_sensor.h"

//#include "peripherals/i2c/max11614.h"

// Config ----------------------------------------------------------------------------------------------------------------------------------

typedef struct  
{
    /// @brief First 16 bytes on EEPROM reserved for magic string  
    uint8_t pad0 [16]; // Address 0x0000

    uint8_t sensorCount; // Address 0x0010

    uint8_t differentiableCount; // Address 0x0011

    /// @brief Pad 2 bytes to align sensor configs to 0x0014
    uint8_t pad1 [2]; // Address 0x0012

    adcSensorConfig_t sensorConfigs[MAX_SENSOR_COUNT]; // Address 0x0014

} msbEepromMap_t;

// Functions ----------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Get the Eeprom Map object
 * 
 * @return Casted pointer to EEPROM Map
 */
msbEepromMap_t* getEepromMap(void);

#endif // EEPROM_MAP_H