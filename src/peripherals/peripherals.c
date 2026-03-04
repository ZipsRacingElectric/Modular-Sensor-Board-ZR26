// Includes --------------------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"

// Globals ---------------------------------------------------------------------------------------------------------------------------------

#define MAGIC_STRING "MSB_2026.02.27"

// Global Peripherals -----------------------------------------------------------------------------------------------------------------------

// Public
mc24lc32_t physicalEeprom;

// Configuration ----------------------------------------------------------------------------------------------------------------------------

/// @brief Configuration of the I2C1 bus.
static const I2CConfig I2C1_CONFIG = 
{
    .op_mode		= OPMODE_I2C,
	.clock_speed	= 100000,
	.duty_cycle		= STD_DUTY_CYCLE
}; 

/// @brief Configuration for the on-board EEPROM.
static const mc24lc32Config_t PHYSICAL_EEPROM_CONFIG = {
    .addr = 0x50,
    .i2c = &I2CD1,
    .timeout = TIME_MS2I(500),
    .magicString = MAGIC_STRING,
    .dirtyHook = NULL
};

// Functions --------------------------------------------------------------------------------------------------------------------------------

bool peripheralsInit() 
{
    // I2C 1 Driver Initialization.
    if (i2cStart(&I2CD1, &I2C1_CONFIG) != MSG_OK ) {
        return false;
    }

    // Physical EEPROM initialization (only exit early if a failure occurred).
	if (!mc24lc32Init (&physicalEeprom, &PHYSICAL_EEPROM_CONFIG) && physicalEeprom.state == MC24LC32_STATE_FAILED) {
        return false;
        // Instead of return false, should actually do something to fix hardware issue
    }
    if (physicalEeprom.state == MC24LC32_STATE_INVALID) {
        uint8_t defaultAddr = 0x48;
        float defaultRawMin = 0.0f;
        float defaultRawMax = 4095.0f;
        float defaultUnitMin = 0.0f;
        float defaultUnitMax = 100.0f;

        mc24lc32Write(&physicalEeprom, offsetof(msbEepromMap_t, i2cAddr), 
            &defaultAddr, sizeof(uint8_t));
        mc24lc32Write(&physicalEeprom, offsetof(msbEepromMap_t, sampleMin), 
            &defaultRawMin, sizeof(float));
        mc24lc32Write(&physicalEeprom, offsetof(msbEepromMap_t, sampleMax), 
            &defaultRawMax, sizeof(float));
        mc24lc32Write(&physicalEeprom, offsetof(msbEepromMap_t, valueMin), 
            &defaultUnitMin, sizeof(float));
        mc24lc32Write(&physicalEeprom, offsetof(msbEepromMap_t, valueMax), 
            &defaultUnitMax, sizeof(float));
    }

    return true;
}   

msbEepromMap_t* getEepromMap(void)
{
    return (msbEepromMap_t*) physicalEeprom.cache;
}