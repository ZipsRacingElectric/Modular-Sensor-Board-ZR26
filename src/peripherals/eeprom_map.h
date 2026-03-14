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

//#include "peripherals/i2c/max11614.h"

// Config ----------------------------------------------------------------------------------------------------------------------------------

typedef struct  
{
    /// @brief First 16 bytes on EEPROM reserved for magic string  
    uint8_t pad0 [16]; // Address 0x0000

    /// @brief Can Status Message, should be different for different MSBs in car
    uint8_t CAN_STATUS; // Address 0x0010

    // 3 bytes of padding due to float datatype alignment 
    uint8_t pad1 [3]; // Address 0x0011

    /// @brief Min range of daughter ADC sample
    uint16_t sampleMin; // Address  0x0014

    /// @brief Max range of daughter ADC sample
    uint16_t sampleMax; // Address 0x0018

    /// @brief Min range of daughter ADC value
    float valueMin; // Address 0x0020

    /// @brief Max range of daughter ADC value
    float valueMax; // Address 0x0022

    ///// @brief Is the ADC channel unipolar or bipolar
    //max11614Polarity_t polarity; // Address 0x0024
//
    ///// @brief Is the ADC channel single-ended or differentbiable
    //max11614Mode_t mode; // Address 0x0038

} msbEepromMap_t;


// Functions ----------------------------------------------------------------------------------------------------------------------------

/**
 * @brief Get the Eeprom Map object
 * 
 * @return Casted pointer to EEPROM Map
 */
msbEepromMap_t* getEepromMap(void);

#endif // EEPROM_MAP_H