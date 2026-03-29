#include "msb_can.h"


// Functions ------------------------------------------------------------------------------------------------------------------

bool msbCanInit(msbCan_t* can, const msbCanConfig_t* config)
{
    if (can == NULL || config == NULL) 
        return false;

    // Save the configuration
    can->config = config;

    // Start the CAN Driver
    canStart(&CAND1, config->canConfig);
	palClearLine (LINE_CAN1_STBY);

    return true;
}
