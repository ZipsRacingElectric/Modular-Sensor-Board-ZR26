#include "modular_sensor_board.h"
#include "peripherals/i2c/daughterADC.h"
#include "peripherals/can/msb_can.h"
#include "peripherals/peripherals.h"

// Functions -------------------------------------------------------------------------------------------------------------------

bool msbInit(msb_t* msb, const msbConfig_t* config) {
    
    if ( msb == NULL || config == NULL) {
        return false;
    }
    
    // Store the configuration
    msb->config = config;

    // Populate Configs from EEPROM
    msbEepromMap_t* eeprom = getEepromMap();

    daughterADCConfig_t adcConfig = {
        .addr = eeprom->i2cAddr,
        .i2c = &I2CD1,
        .timeout = TIME_MS2I(20),
    };

    // Populate Analog Sensor configs from EEPROM ie min and maxes
    if (!peripheralsInit())
        return false;

    // Initialize Daughter ADC
    if (!daughterADCInit(msb->config->adc, &adcConfig)) 
        return false;
    
    // Initialize Analog Sensor
        // TODO: That here

    // Initialize CAN driver
    //if (!msbCanInit(can_t *can, const canConfig_t *config))
    //    return false;

    // Everything Passed
    return true;
}

bool msbSample (msb_t* msb) {
    // Call I2C functions to read ADC data 

    // Use sensor to interpolate sampled data

    // Call Can transmit function
}

