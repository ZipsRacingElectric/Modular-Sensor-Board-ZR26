#include "msb_transmit.h"

#include <string.h>

// Message IDs --------------------------------------------------------------------------------------------------------------------

#define STATUS_MESSAGE_ID           0x300
#define ADC_BASE_MESSAGE_ID         0x100

#define SENSORS_PER_FRAME           2

// Handle an odd number of frames, by bumping up to the ne`xt whole number and padding unused bytes
#define NUM_ADC_FRAMES(sensorCount) (((sensorCount) + SENSORS_PER_FRAME - 1) / SENSORS_PER_FRAME)

// Functions ------------------------------------------------------------------------------------------------------------------
bool transmitADCValue(msbCan_t* can, adcSensor_t* sensors, uint8_t sensorCount)
{
   bool status = true;
   
   for (int frame = 0; frame < NUM_ADC_FRAMES(sensorCount); frame++)
   {
        CANTxFrame txFrame =
        {
            .DLC = 8,
            .RTR = 0,
            .IDE = CAN_IDE_STD,
            .SID = ADC_BASE_MESSAGE_ID + frame,
        };

        memset(txFrame.data8, 0, 8);

        for (int i = 0; i < SENSORS_PER_FRAME; i++) 
        {
            int sensorIndex = (frame * SENSORS_PER_FRAME) + i;

            if (sensorIndex < sensorCount)
            {
                memcpy(&txFrame.data8[i * sizeof(float)],
                      &sensors[sensorIndex].value,  
                      sizeof(float));
            }
        }

        status &= canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &txFrame, can->config->timeout) == MSG_OK;
   }

   return status;
}