// Includes --------------------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"
#include "eeprom_map.h"

#include "debug.h"

// Global Peripherals -----------------------------------------------------------------------------------------------------------------------

virtualEeprom_t virtualEeprom;

// Functions --------------------------------------------------------------------------------------------------------------------------------

bool peripheralsInit(const I2CConfig* i2cConfig, const mc24lc32Config_t* eepromConfig) 
{
    // I2C 1 Driver Initialization.
    i2cStart(&I2CD1, i2cConfig);
    if (I2CD1.state !=I2C_READY)
    {
        debugPrintf("I2C1 Init Failed\r\n");
        return false;
    }

    // I2C 2 Driver Initialization.
    i2cStart(&I2CD2, i2cConfig);
    if (I2CD2.state !=I2C_READY)
    {
        debugPrintf("I2C2 Init Failed\r\n");
        return false;
    }

    // Physical EEPROM initialization (only exit early if a failure occurred).
	if (!mc24lc32Init (&physicalEeprom, eepromConfig) && physicalEeprom.state == MC24LC32_STATE_FAILED) 
    {
        debugPrintf("Pysical EEPROM Init Failed\r\n");
        return false;
    }
    if (physicalEeprom.state == MC24LC32_STATE_INVALID) 
    {
        debugPrintf("EEPROM invalid - must configure correctly before use.\r\n");
        
        // TODO (Nowak):
            // Flash fault LED
            // Transmit CAN Error to dashboard

    }

    return true;
}   
