#ifndef MSB_RECEIVE_H
#define MSB_RECEIVE_H

// CAN Message Receive Handler ------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.30
//
// Description: Function for handling received CAN messages.

// Includes -------------------------------------------------------------------------------------------------------------------

#include "hal.h"

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Handles a received CAN message.
 * @param node Dummy variable used for matching the required function signature. Ignored.
 * @param frame The received CAN frame to handle.
 * @return 0 if recognized and handled, -1 if the message is unrecognized.
 */
int8_t receiveMessage (void* node, CANRxFrame* frame);

#endif // MSB_RECEIVE_H
