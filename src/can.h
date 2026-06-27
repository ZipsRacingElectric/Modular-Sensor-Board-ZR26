#ifndef MSB_CAN_H
#define MSB_CAN_H

// Modular Sensor Board CAN Interface -----------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.30
//
// Description: Initializes the CAN interface of the Modular Sensor Board

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"
#include "can/receive.h"
#include "can/transmit.h"

// CAN IDs --------------------------------------------------------------------------------------------------------------------

/// @brief The CAN ID of the EEPROM command message.
#define EEPROM_CAN_ID 0x016

/// @brief The CAN ID of the rear damper position message.
#define DAMPER_REAR_CAN_ID	0x150

/// @brief The CAN ID of the front damper position message.
#define DAMPER_FRONT_CAN_ID	0x151

/// @brief The CAN ID of the cooling temperature message.
#define TEMPERATURE_CAN_ID	0x152

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initializes the Modular Sensor Board's CAN interface.
 * @param priority The priority to start the CAN receive thread at.
 * @return true if successful, false if a hardware failure occured.
 */
bool canInterfaceInit (tprio_t priority);

#endif // MSB_CAN_H