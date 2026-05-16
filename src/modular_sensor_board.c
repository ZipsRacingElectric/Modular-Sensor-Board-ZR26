#include "modular_sensor_board.h"

#include "debug.h"

// Gloabls 
#define MAGIC_STRING "MSB_2026.02.27" 
// Global MSB Objects ----------------------------------------------------------------------------------------------------------------

static max11614_t   msbADC;
static msbCan_t     msbCan;
mc24lc32_t physicalEeprom;

// Driver Configuration ---------------------------------------------------------------------------------------------------------------

/// @brief Configuration of the I2C1 bus.
static const I2CConfig I2C1_CONFIG = 
{
    .op_mode		= OPMODE_I2C,
	.clock_speed	= 100000,
	.duty_cycle		= STD_DUTY_CYCLE
}; 

/// @brief Configuration for the on-board EEPROM.
const mc24lc32Config_t PHYSICAL_EEPROM_CONFIG = {
    .addr = 0x50,
    .i2c = &I2CD1,
    .timeout = TIME_MS2I(500),
    .magicString = MAGIC_STRING,
    .dirtyHook = NULL
};

static const max11614Config_t ADC_CONFIG =
{
    .addr = 0x33,
    .i2c = &I2CD2,
    .timeout = TIME_MS2I(20),
    .sampleVdd = MAX11614_REF_MV
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

    // Initialize CAN Driver
    if (!msbCanInit(&msbCan, &CAN_CONFIG))
    {
        debugPrintf("canInit Failed\r\n");
        return false;
    }

    // Start CAN Thread
    msbReceiveStart();
    debugPrintf("Successfully started recieve can thread\r\n");

    // Initialize I2C Driver and EEPROM Driver
    if (!peripheralsInit(&I2C1_CONFIG, &PHYSICAL_EEPROM_CONFIG))
    {
        debugPrintf("Peripherals Init Failed\r\n");
        return false;
    }

    if (physicalEeprom.state == MC24LC32_STATE_INVALID)
    {
        debugPrintf("EEPROM State invalid, use CAN EEPROM cli to write valid configurations to board.");
        return true;
    }
    
    // Populate "on the fly" Configs from EEPROM
    msbEepromMap_t* eeprom = getEepromMap();

    // Read actual board config from EEPROM
    msb->sensorCount       = eeprom->sensorCount;
    msb->differentiableCount = eeprom->differentiableCount;

    debugPrintf("sensorCount = %d, differentiableCount = %d\r\n", 
    msb->sensorCount, msb->differentiableCount);

    // Validate sensor count from EEPROM is not greater than the max sensor count of the ADC
    if (msb->sensorCount == 0 || msb->sensorCount > MAX_SENSOR_COUNT) 
    {
        debugPrintf("Invalid sensorCount in EEPROM: %d\r\n", msb->sensorCount);
        return true;
    }

    // Validate the differentiable sensor count is not larger than is allowed by ADC
    if (!SENSOR_LAYOUT_VALID(msb->sensorCount, msb->differentiableCount)) 
    {
        debugPrintf("Sensor Layout exceeds physical channel count\r\n");
        return true;
    }

    // Intialize MAX11614 ADC Driver
    if (!max11614Init(&msbADC, &ADC_CONFIG))
    {
        debugPrintf("max11614Init Failed\r\n");
        return false;
    }

    // Initialize ADC Analog Sensors
    for (int i = 0; i < msb->sensorCount; i++) 
    {
        // Copy the EEPROM values to the sensor configs
        msb->sensorConfigs[i] = eeprom->sensorConfigs[i];

        if (!adcSensorInit(&msb->sensors[i], &msb->sensorConfigs[i]))
        {
            debugPrintf("adcSensorInit failed on channel %d\r\n", i);
            return true;
        }
    }
        
    // Everything Passed
    debugPrintf("msbInit Sucessful\r\n");
    return true;
}

bool msbSample (msb_t* msb) {

    if (!max11614ReadChannels(&msbADC, &msb->adcResults, msb->differentiableCount, msb->sensorCount)) return false;

    for (int i = 0; i < msb->sensorCount; ++i)
    {
        analogSensorUpdate((analogSensor_t*)&msb->sensors[i], msb->adcResults.channels[i], ADC_CONFIG.sampleVdd);
    }

    transmitADCValue(&msbCan, msb->sensors, msb->sensorCount);
    return true;
}