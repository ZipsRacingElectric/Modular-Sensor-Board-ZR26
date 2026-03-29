#ifndef ADC_SENSOR_H
#define ADC_SENSOR_H

// Modular Sensor Board ADC Sensors ----------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.14
//
// Description: Handles sensor linear interpolation of daughter ADCs on Modular Sensor Board
// Is a generic ADC callback handler, can handle all channels of the daughter ADC.

// Includes -----------------------------------------------------------------------------------------------------------------

#include "hal.h"

#include "peripherals/interface/analog_sensor.h"

// Configs -----------------------------------------------------------------------------------------------------------------

typedef struct
{
    /// @brief The aboslute minimum sample that can be taken from a daughter ADC.
    uint16_t adcSampleMin;

    /// @brief The aboslute maximum sample that can be taken from a daughter ADC.
    uint16_t adcSampleMax;

    /// @brief The absolute minimum value that can be given by the daughter ADC.
    float adcValueMin;

    /// @brief The absoulte maximum value that can be given by the daughter ADC.
    float adcValueMax;

} adcSensorConfig_t;

typedef struct 
{
    ANALOG_SENSOR_FIELDS;
    const adcSensorConfig_t* config;
    uint16_t sample;
    float value;

} adcSensor_t;

// Functions ----------------------------------------------------------------------------------------------------------------

/**
 * @brief Initialize the daughter ADC sensor minimums and maximums, given by the EEPROM.  
 * 
 * @param sensor The sensor to initialize.
 * @param config The configuration being used.
 * @return True if successful, false if values from EEPROM not read correctly.
 */
bool adcSensorInit(adcSensor_t* sensor, const adcSensorConfig_t* config);

#endif // ADC_SENSOR_H