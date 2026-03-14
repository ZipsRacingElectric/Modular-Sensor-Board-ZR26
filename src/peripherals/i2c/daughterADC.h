#ifndef DAUGHTERADC_H
#define DAUGHTERADC_H

// Modular Sense Board --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.25
//
// Description: I2C driver for Modular Sense Board Daughter ADC's

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"

// Configs -------------------------------------------------------------------------------------------------------------------

typedef struct {
    /// @brief the 7-bit I2C address of the device
    i2caddr_t addr;

    /// @brief The I2C bus of the device.
    I2CDriver* i2c;
    
    /// @brief The timeout interval of a transaction. Note that if this is less than 20ms, transactions occurring after a write
	/// operation may fail.
	sysinterval_t timeout;

} daughterADCConfig_t;

typedef struct {

    const daughterADCConfig_t* config;

} daughterADC_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the device using the specialized configuration.
 * 
 * @param dADC The device to initalize.
 * @param config The configuration to use.
 * @return True if successful, false if hardware failure occured.
 */
bool daughterADCInit(daughterADC_t* dADC, const daughterADCConfig_t* config);

/**
 * @brief Helper I2C functions allows the Modular Sensor Board to interact with any daughter ADC, reduces boilerplate when changing daughter ADCs.
 * 
 * @param dADC The device that the I2C functions will interact with.
 * @param data The bits / byte of data being written to the ADC.
 * @param value The bits / byte being read from the ADC.
 * @return True if I2C transmit is successful, False if otherwise. 
 */
bool write8bit(daughterADC_t* dADC, uint8_t data);
bool read8bit(daughterADC_t* dADC, uint8_t* value);
bool write12bit(daughterADC_t* dADC, uint16_t data);
bool read12bit(daughterADC_t* dADC, uint16_t* value);

#endif