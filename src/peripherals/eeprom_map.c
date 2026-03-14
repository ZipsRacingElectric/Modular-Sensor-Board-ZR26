#include "eeprom_map.h"

// Global ------------------------------------------------------------------------------------------------------------------------------

extern mc24lc32_t physicalEeprom;

// Functions ----------------------------------------------------------------------------------------------------------------------------

msbEepromMap_t* getEepromMap(void)
{
    return (msbEepromMap_t*) physicalEeprom.cache;
}