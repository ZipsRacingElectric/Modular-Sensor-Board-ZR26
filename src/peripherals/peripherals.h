#ifndef PERIPHERALS_H
#define PERIPHERALS_H

// Modular Sensor Board Peripherals --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.27
//
// Description: Defines and initializes the peripherals that exist on the Modular Sensor Board

// Includes --------------------------------------------------------------------------------------------------------------------------------

#include "peripherals/i2c/mc24lc32.h"

// Global Peripherals -----------------------------------------------------------------------------------------------------------------------

extern mc24lc32_t physicalEeprom;

extern virtualEeprom_t virtualEeprom;

// Config ----------------------------------------------------------------------------------------------------------------------------------

typedef struct  
{
    /// @brief First 16 bytes on EEPROM reserved for magic string  
    uint8_t pad0 [16]; // Address 0x0000

    /// @brief I2C address of daughter ADC
    uint8_t i2cAddr; // Address 0x0010

    uint8_t pad1 [3]; // 3 bytes of padding Address 0x0013

    /// @brief Min range of daughter ADC sample
    float sampleMin;

    /// @brief Max range of daughter ADC sample
    float sampleMax;

    /// @brief Min range of daughter ADC value
    float valueMin;

    /// @brief Max range of daughter ADC value
    float valueMax;


} msbEepromMap_t;

// Functions --------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes peripheral devices on Modular Sensor Board
 * 
 * @return True if successful, false if hardware failure occured 
 */
bool peripheralsInit(void);

/**
 * @brief Get the Eeprom Map object
 * 
 * @return Casted pointer to EEPROM Map
 */
msbEepromMap_t* getEepromMap(void);

#endif // PERIPHERALS_H