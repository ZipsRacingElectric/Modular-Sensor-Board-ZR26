#ifndef MSB_CAN_H
#define MSB_CAN_H

// Modular Sensor Board --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.3.30
//
// Description: Initialized the can bus for the Modular Sensor Board

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"

// Configs ---------------------------------------------------------------------------------------------------------------------

typedef struct 
{
    CANDriver* driver;
    sysinterval_t timeout;

} msbCanConfig_t;

typedef struct 
{
    const msbCanConfig_t* config;
} msbCan_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initialize the Modular Sensor Board CAN with the correct configuration
 * 
 * @param can The device to initialize.
 * @param config The configuraton to use.
 * @return True if successful, false if hardware failure occured.
 */
bool msbCanInit(msbCan_t* can, const msbCanConfig_t* config);

#endif // MSB_CAN_H