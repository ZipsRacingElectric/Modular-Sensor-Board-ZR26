// Includes --------------------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"
#include "eeprom_map.h"

// Global Peripherals -----------------------------------------------------------------------------------------------------------------------

virtualEeprom_t virtualEeprom;

// Functions --------------------------------------------------------------------------------------------------------------------------------

bool peripheralsInit(const I2CConfig* i2cConfig, const mc24lc32Config_t* eepromConfig) 
{
    // I2C 1 Driver Initialization.
    if (i2cStart(&I2CD1, i2cConfig) != MSG_OK ) {
        return false;
    }

    // Physical EEPROM initialization (only exit early if a failure occurred).
	if (!mc24lc32Init (&physicalEeprom, eepromConfig) && physicalEeprom.state == MC24LC32_STATE_FAILED) {
        return false;
    }
    if (physicalEeprom.state == MC24LC32_STATE_INVALID) {
        // Write default values, but do not validate EEPROM state, so someone has to manually validate
        float defaultRawMin = 0.0f;
        float defaultRawMax = 4095.0f;
        float defaultUnitMin = 0.0f;
        float defaultUnitMax = 100.0f;

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
