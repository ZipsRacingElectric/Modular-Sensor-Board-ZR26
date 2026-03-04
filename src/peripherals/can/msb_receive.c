// Includes -------------------------------------------------------------------------------------------------------------------

#include "msb_receive.h"

// Gloabals ------------------------------------------------------------------------------------------------------------------

#define EEPROM_COMMAND_MESSAGE_ID 0x700

// Functions ------------------------------------------------------------------------------------------------------------------


int8_t msbCanReceiveMessage (void* config, CANRxFrame* frame) 
{
    msbCan_t* can = (msbCan_t*) config;

    // Check can ID
    if (frame->SID == EEPROM_COMMAND_MESSAGE_ID) 
    {
        // If the command message was received, call the handler.
		eepromHandleCanCommand (frame, can->config->driver, (eeprom_t*) &physicalEeprom);
		return 0;
    }

    return -1;
}
