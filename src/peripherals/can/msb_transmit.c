#include "msb_transmit.h"

// Message IDs --------------------------------------------------------------------------------------------------------------------

#define STATUS_MESSAGE_ID       0x300
#define ADC_VALUE_MESSAGE_ID    0x400

// Functions ------------------------------------------------------------------------------------------------------------------

uint8_t test_data = 100;

bool transmitADCValue(msbCan_t* can)
{
    CANTxFrame transmit = 
    {
        .DLC = 1,
        .RTR = 1,
        .IDE = CAN_IDE_STD,
        .SID = ADC_VALUE_MESSAGE_ID,
        .data8 = 
        {
            test_data
        }
    };

    msg_t result = canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &transmit, can->config->timeout);

    return result == MSG_OK;
}