#include "modular_sensor_board.h"

#include "debug.h"

// Gloabls 
#define MAGIC_STRING "MSB_2026.02.27"
#define ADC_SENSORS 6
#define SINGLE_ENDED_SENSORS 4

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
    .sampleVdd = 0,     // Using internal reference voltage 4.096V
};

/// @brief Configuration of the Can Driver
static const CANConfig CAN_DRIVER_CONFIG =
	{
	.mcr = CAN_MCR_ABOM |
		CAN_MCR_AWUM |
		CAN_MCR_TXFP,
	.btr = CAN_BTR_SJW (0) |
		CAN_BTR_TS2 (1) |
		CAN_BTR_TS1 (10) |
		CAN_BTR_BRP (2)
	};

/// @brief COnfiguration of the Modular Sensor Board Can Bus
static const msbCanConfig_t CAN_CONFIG = 
{
    .driver = &CAND1,
    .canConfig = &CAN_DRIVER_CONFIG,
    .timeout = TIME_MS2I(20),
};

// Functions -------------------------------------------------------------------------------------------------------------------

bool msbInit(msb_t* msb, const msbConfig_t* config) {
    
    if (msb == NULL || config == NULL) {
        debugPrintf("Null Ptr to MSB\r\n");
        return false;
    }
    
    // Store the configuration
    msb->config = config;

    // Initialize I2C Driver and EEPROM Driver
    if (!peripheralsInit(&I2C1_CONFIG, &PHYSICAL_EEPROM_CONFIG))
    {
        debugPrintf("Peripherals Init Failed\r\n");
        return false;
    }

    // Populate "on the fly" Configs from EEPROM
    msbEepromMap_t* eeprom = getEepromMap();

    // Intialize MAX11614 ADC Driver
    if (!max11614Init(&msbADC, &ADC_CONFIG))
    {
        debugPrintf("max11614Init Failed\r\n");
        return false;
    }

    // Initialize CAN Driver
    if (!msbCanInit(&msbCan, &CAN_CONFIG))
    {
        debugPrintf("canInit Failed\r\n");
        return false;
    }
    
    // Initialize ADC Analog Sensors
    for (int i = 0; i < ADC_SENSORS; i++) 
    {
        if (!adcSensorInit(&msb->sensors[i], msb->sensorConfigs[i]))
        {
            debugPrintf("adcSensorInit failed on channel %d\r\n", i);
            return false;
        }
    }
        
    // Everything Passed
    debugPrintf("msbInit Sucessful\r\n");
    return true;
}

bool msbSample (msb_t* msb) {
    // Call I2C functions to read ADC data 
    if (!max11614ReadChannels(&msb->adc, &msb->adcResults)) return false;

    // Push differntiable sample data into sensors 
    analogSensorUpdate((analogSensor_t*) &msb->sensors[0], msb->adcResults.differentiable[0], ADC_CONFIG.sampleVdd);
    analogSensorUpdate((analogSensor_t*) &msb->sensors[1], msb->adcResults.differentiable[1], ADC_CONFIG.sampleVdd);

    // Push single ended sample data into sensors
    for (int i = 0; i < SINGLE_ENDED_SENSORS; i++) 
    {   
        // Offset i by 2 to not overwrite differentiable sensors
        analogSensorUpdate((analogSensor_t*) &msb->sensors[i + 2], msb->adcResults.singleEnded[i], ADC_CONFIG.sampleVdd);
    }

    // Use sensor to interpolate sampled data

    // Call Can transmit function

    return true;
}