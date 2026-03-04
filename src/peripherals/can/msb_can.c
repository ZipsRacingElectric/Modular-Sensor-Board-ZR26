#include "msb_can.h"

// Configuration --------------------------------------------------------------------------------------------------------------

static const msbCanConfig_t msbCanConfig = 
{
    .driver = &CAND1,
    .timeout = TIME_MS2I(100),
};

static msbCan_t msbCan = { &msbCanConfig };

// Functions ------------------------------------------------------------------------------------------------------------------

bool msbCanInit(msbCan_t* can, const msbCanConfig_t* config)
{
    if (can == NULL || config == NULL) {
        return false;
    }

    // Store the configuration
    msbCan.config = &msbCanConfig;

    return true;
}