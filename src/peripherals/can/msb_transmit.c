#include "msb_transmit.h"

#include <string.h>

// Message IDs --------------------------------------------------------------------------------------------------------------------

#define STATUS_MESSAGE_ID           0x300

#define ADC_DIFF_MESSAGE_ID         0x400
#define ADC_SINGLE_LOW_MESSAGE_ID   0x401
#define ADC_SINGLE_HIGH_MESSAGE_ID  0x402

// Functions ------------------------------------------------------------------------------------------------------------------
bool transmitADCValue(msbCan_t* can, adcSensor_t* sensors)
{
    bool status = true;

    // Differentiable Sensors (Sensors 0 and 1)
    CANTxFrame diffFrame = 
    {
        .DLC = 8,
        .RTR = 0,   
        .IDE = CAN_IDE_STD,
        .SID = ADC_DIFF_MESSAGE_ID,
    };
    memcpy(&diffFrame.data8[0], &sensors[0].value, sizeof(float));
    memcpy(&diffFrame.data8[4], &sensors[1].value, sizeof(float));
    status &= canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &diffFrame, can->config->timeout) == MSG_OK;

    // Single Ended Sensors (Sensors 2 and 3)
    CANTxFrame singleLowFrame = 
    {
        .DLC = 8,
        .RTR = 0,
        .IDE = CAN_IDE_STD,
        .SID = ADC_SINGLE_LOW_MESSAGE_ID,
    };
    memcpy(&singleLowFrame.data8[0], &sensors[2].value, sizeof(float));
    memcpy(&singleLowFrame.data8[4], &sensors[3].value, sizeof(float));
    status &= canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &singleLowFrame, can->config->timeout) == MSG_OK;

    // Single Ended Sensors (Sensors 4 and 5)
    CANTxFrame singleHighFrame = 
    {
        .DLC = 8,
        .RTR = 0,
        .IDE = CAN_IDE_STD,
        .SID = ADC_SINGLE_HIGH_MESSAGE_ID,
    };
    memcpy(&singleHighFrame.data8[0], &sensors[4].value, sizeof(float));
    memcpy(&singleHighFrame.data8[4], &sensors[5].value, sizeof(float));
    status &= canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &singleHighFrame, can->config->timeout) == MSG_OK;

    return status;
}