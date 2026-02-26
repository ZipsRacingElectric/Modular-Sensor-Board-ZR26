#include "modular_sensor_board.h"

// Functions -------------------------------------------------------------------------------------------------------------------

bool msbInit(msb_t* msb, const msbConfig_t* config) {
    // Store the configuration
    msb->config = config;

    return true;
}

