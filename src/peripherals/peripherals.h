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

// Functions --------------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes peripheral devices on Modular Sensor Board
 * 
 * @return True if successful, false if hardware failure occured 
 */
bool peripheralsInit(const I2CConfig* i2cConfig, const mc24lc32Config_t* eepromConfig);


#endif // PERIPHERALS_H