#ifndef MSB_TRANSMIT_H
#define MSB_TRANSMIT_H

// CAN Message Transmitting ---------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.25
//
// Description: Functions for transmitting CAN messages.

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Transmits the rear damper position CAN message.
 * @param driver The CAN driver to transmit using.
 * @param timeout The interval to timeout after.
 * @return The result of the operation.
 */
msg_t transmitRearDamperPositionMessage (CANDriver* driver, sysinterval_t timeout);

/**
 * @brief Transmits the front damper position CAN message.
 * @param driver The CAN driver to transmit using.
 * @param timeout The interval to timeout after.
 * @return The result of the operation.
 */
msg_t transmitFrontDamperPositionMessage (CANDriver* driver, sysinterval_t timeout);

/**
 * @brief Transmits the cooling temperature CAN message.
 * @param driver The CAN driver to transmit using.
 * @param timeout The interval to timeout after.
 * @return The result of the operation.
 */
msg_t transmitCoolingTempMessage (CANDriver* driver, sysinterval_t timeout);

#endif // MSB_TRANSMIT_H