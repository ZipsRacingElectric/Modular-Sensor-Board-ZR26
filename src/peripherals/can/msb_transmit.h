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
 * @brief Transmits the MSB's current status based on what stat it is in.
 * 
 * @param can Pointer to the can configuration to use.
 * @return True if transmit is successful, false if transmit fails.
 */
bool transmitStatusMessage(msbCan_t* can);

/**
 * @brief Transmit Sampled value from daughterADC onto the CAN bus.
 * 
 * @param can A pointer to the can configuration to use.
 * @return True if transmit is successful, false if transmit fails.
 */
bool transmitADCValue(msbCan_t* can, msbCanConfig_t* config);

#endif // MSB_TRANSMIT_H