#include "msb_can.h"


// Functions ------------------------------------------------------------------------------------------------------------------

bool msbCanInit(msbCan_t* can, const msbCanConfig_t* config)
{
    if (can == NULL || config == NULL) 
        return false;

    can->config = config;

    return true;
}
