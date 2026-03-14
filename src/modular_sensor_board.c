#include "modular_sensor_board.h"

#include "debug.h"

// Gloabls 
#define MAGIC_STRING "MSB_2026.02.27"

// Global MSB Drivers ---------------------------------------------------------------------------------------------------------

static max11614_t   msbADC;
static msbCan_t     msbCan;
mc24lc32_t physicalEeprom;
//static analogSensor_t msbSensor;

// Driver Configuration ---------------------------------------------------------------------------------------------------------------

/// @brief Configuration of the I2C1 bus.
static const I2CConfig I2C1_CONFIG = 
{
    .op_mode		= OPMODE_I2C,
	.clock_speed	= 100000,
	.duty_cycle		= STD_DUTY_CYCLE
}; 

/// @brief Configuration for the on-board EEPROM.
static const mc24lc32Config_t PHYSICAL_EEPROM_CONFIG = {
    .addr = 0x016,
    .i2c = &I2CD1,
    .timeout = TIME_MS2I(500),
    .magicString = MAGIC_STRING,
    .dirtyHook = NULL
};

static const max11614Config_t ADC_CONFIG =
{
    .addr = 0x33,
    .i2c = &I2CD1,
    .timeout = TIME_MS2I(20),
};

static const msbCanConfig_t CAN_CONFIG = 
{
    .driver = &CAND1,
    .timeout = TIME_MS2I(20),
};

// Functions -------------------------------------------------------------------------------------------------------------------

bool msbInit(msb_t* msb, const msbConfig_t* config) {
    
    if (msb == NULL || config == NULL) {
        return false;
    }
    
    // Store the configuration
    msb->config = config;

    // Initialize I2C Driver and EEPROM Driver
    if (!peripheralsInit(&I2C1_CONFIG, &PHYSICAL_EEPROM_CONFIG))
        return false;

    // Populate Configs from EEPROM
    msbEepromMap_t* eeprom = getEepromMap();

    // Intialize MAX11614 ADC Driver
    if (!max11614Init(&msbADC, &ADC_CONFIG))
        return false;

    // Initialize CAN Driver
    if (!msbCanInit(&msbCan, &CAN_CONFIG))
        return false;
    
    // Initialize Analog Sensor
        // TODO: That here

    // Everything Passed
    return true;
}

bool msbSample (msb_t* msb) {
    // Call I2C functions to read ADC data 
    if (!max11614ReadChannels(&msb->adc, &msb->adcResults)) return false;

    // Use sensor to interpolate sampled data

    // Call Can transmit function

    return true;
}