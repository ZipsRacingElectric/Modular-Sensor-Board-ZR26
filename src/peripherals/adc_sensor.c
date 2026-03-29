#include "adc_sensor.h"

#include "controls/lerp.h"

// Function Prototyeps -----------------------------------------------------------------------------------------------------------------

/**
 * @brief Updates the value of the sensor.
 * @note This function uses a @c void* for the object reference as to make the signature usable by callbacks.
 * @param object The sensor to update (must be a @c adcSensor_t* ).
 * @param sample The read sample.
 * @param sampleVdd Depends on reference voltage of daughter ADC.
 */
static void callback( void* object, uint16_t sample, uint16_t sampleVdd);

// Functions ----------------------------------------------------------------------------------------------------------------------------

bool adcSensorInit(adcSensor_t *sensor, const adcSensorConfig_t *config)
{
    // Store the configuration
    sensor->config = config;
    sensor->callback = callback;

    // Set values to their defaults
    sensor->sample = 0;
    sensor->value = 0.0f;

    // Validate the configuration
    if (config->adcSampleMin >= config->adcSampleMax) 
        sensor->state = ANALOG_SENSOR_CONFIG_INVALID;
    else 
        sensor->state = ANALOG_SENSOR_SAMPLE_INVALID;
    
    return sensor->state != ANALOG_SENSOR_CONFIG_INVALID;
}

void callback(void* object, uint16_t sample, uint16_t sampleVdd) 
{
    (void) sampleVdd;

    adcSensor_t* sensor = (adcSensor_t*) object;

    // Store the sample
    sensor->sample = sample;

    // If the configuration is invalid, don't check anything else.
    if (sensor->state == ANALOG_SENSOR_CONFIG_INVALID) 
        return;

    // Check if the sample is in valid range.
    if (sample < sensor->config->adcSampleMin || sample > sensor->config->adcSampleMax)
    {
        sensor->state = ANALOG_SENSOR_SAMPLE_INVALID;
        sensor->value = 0.0f;
        return;
    }

    sensor->state = ANALOG_SENSOR_VALID;

    // Map sample range to value
    sensor->value = lerp2d
    (
        sample,
        sensor->config->adcSampleMin,
        sensor->config->adcValueMin,
        sensor->config->adcSampleMax,
        sensor->config->adcValueMax

    );
}