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
 * @brief Helper function to sample from ADC on MSB, without interacting with static I2C functions directly.
 * 
 * @param dADC The device to get raw value from.
 * @param reg The register being read from.
 * @param rawValue The raw value being sampled.
 * @return True if I2C transmit sucessful, false if I2C transmit failed. 
 */
bool getRawADC(daughterADC_t* dADC, uint8_t reg, uint16_t* rawValue);

#endif