#ifndef MSB_RECEIVE_H
#define MSB_RECEIVE_H

// Modular Sensor Board --------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.3.30
//
// Description: Receive Frame handler, on Modular Sensor Board will be used to write to EEPROM

// Includes -------------------------------------------------------------------------------------------------------------------

#include "msb_can.h"
#include "can/eeprom_can.h"
#include "peripherals/peripherals.h"

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief 
 * 
 * @param config Void config signifying callback function, must cast to type used in file.
 * @param Frame The received CAN frame. 
 * @return 0 if successful, -1 if CAN SID's do not match
 */
int8_t msbCanReceiveMessage (void* config, CANRxFrame* Frame);

#endif // MSB_RECEIVE_H
