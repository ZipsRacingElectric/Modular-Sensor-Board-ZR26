#ifndef MODULAR_SENSOR_BOARD_H
#define MODULAR_SENSOR_BOARD_H

// Modular Sensor Board --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.25
//
// Description: Modular sense board that can handle different daughter ADC inputs.

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"
 
#include "peripherals/interface/analog_sensor.h"
#include "peripherals/i2c/daughterADC.h"

// Configs --------------------------------------------------------------------------------------------------------------------
typedef struct {
    
    /// @brief The daughter ADC board being sampled.
    daughterADC_t* adc;

    /// @brief The sensor to call after sampling successfully.
	analogSensor_t* sensor;

} msbConfig_t;

typedef struct {

    const msbConfig_t* config;

} msb_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the device using the specialized configuration.
 * 
 * @param msb The device to initialize.
 * @param config The configuration to use.
 * @return True if successful, false if hardware failure occured.
 */
bool msbInit(msb_t* msb, const msbConfig_t* config);

/**
 * @brief Sample the daughter board connected.
 * 
 * @param msb The device to sample.
 * @return True if successful, false otherwise. 
 */
bool msbSample (msb_t* msb);


#endif // MODULAR_SENSOR_BOARD_H