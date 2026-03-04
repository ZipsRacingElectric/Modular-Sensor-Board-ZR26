#include "msb_transmit.h"

// Globals --------------------------------------------------------------------------------------------------------------------

#define TRANSMIT_BASE_ID 0x400

// Functions ------------------------------------------------------------------------------------------------------------------


bool msbCanTransmit(msbCan_t* can)
{
    CANTxFrame transmit = 
    {
        .DLC = 1,
        .RTR = 1,
        .IDE = CAN_IDE_STD,
        .SID = TRANSMIT_BASE_ID,
        .data8 = 
        {
            // Some data 8 channels on each ADC board
        }
    };

    msg_t result = canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &transmit, can->config->timeout);

    return result == MSG_OK;
}