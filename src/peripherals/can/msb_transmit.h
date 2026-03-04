#ifndef MSB_TRANSMIT_H
#define MSB_TRANSMIT_H

// Modular Sense Board Transmit -----------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.02.25
//
// Description: The Driver to handle CAN transmitting on the Modular Sense Board

// Includes -------------------------------------------------------------------------------------------------------------------

#include "msb_can.h"

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Wrapper function for canTransmit, specific to the Modular Sensor Board.
 * 
 * @param can A pointer to the can configuration to use.
 * @return True if transmit is successful, false if transmit fails.
 */
bool msbCanTransmit(msbCan_t* can);

#endif // MSB_TRANSMIT_H