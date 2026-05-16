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

#include "peripherals/peripherals.h"
#include "peripherals/eeprom_map.h"

#include "peripherals/i2c/max11614.h"
#include "peripherals/i2c/daughterADC.h"
#include "peripherals/adc_sensor.h"
#include "peripherals/interface/analog_sensor.h"

#include "peripherals/can/msb_can.h"
#include "peripherals/can/msb_transmit.h"
#include "peripherals/can/msb_receive.h"

// Globals --------------------------------------------------------------------------------------------------------------------

// Configs --------------------------------------------------------------------------------------------------------------------
typedef struct 
{
    

} msbConfig_t;

typedef struct 
{

    const msbConfig_t* config;

    /// @brief Actual sensor count for this board (Read from EEPROM)
    uint8_t sensorCount;

    /// @brief How many sensors are differentiable
    uint8_t differentiableCount;

    max11614_t adc;

    max11614Results_t adcResults;

    msbCan_t can;

    adcSensor_t sensors[MAX_SENSOR_COUNT];

    /// @brief The configuration to use on the sensors, gotten from EEPROM
    adcSensorConfig_t sensorConfigs[MAX_SENSOR_COUNT];

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