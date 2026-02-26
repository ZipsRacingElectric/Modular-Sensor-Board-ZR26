#ifndef MODULAR_SENSOR_BOARD_H
#define MODULAR_SENSOR_BOARD_H

// Modular Sense Board --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.25
//
// Description: Modular sense board that can handle different daughter ADC inputs

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"

#include "peripherals/interface/analog_sensor.h"

// Configs --------------------------------------------------------------------------------------------------------------------
typedef struct {

    /// @brief the 7-bit I2C address of the device
    i2caddr_t addr;

    /// @brief The I2C bus of the device.
    I2CDriver* i2c;
    
    /// @brief The timeout interval of a transaction. Note that if this is less than 20ms, transactions occurring after a write
	/// operation may fail.
	sysinterval_t timeout;

    /// @brief The sensor to call after sampling successfully.
	analogSensor_t* sensor;

} msbConfig_t;

typedef struct {

    const msbConfig_t* config;

} msb_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief 
 * 
 * @return true 
 * @return false 
 */
bool msbInit(msb_t* msb, const msbConfig_t* config);

/**
 * @brief 
 * 
 * @param msb 
 * @return true 
 * @return false 
 */
bool msbSample (msb_t* msb);


#endif // MODULAR_SENSOR_BOARD_H