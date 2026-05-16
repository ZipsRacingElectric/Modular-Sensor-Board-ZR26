#include "msb_transmit.h"

#include <string.h>

// Message IDs --------------------------------------------------------------------------------------------------------------------

// 5V Scaling Factor of 16 bit ADC 
#define VOLTAGE_FACTOR          0.000076295109f
#define VOLTAGE_INV_FACTOR      13107.0000831f

#define VOLTAGE_TO_WORD(value) ((int16_t)((value) * VOLTAGE_INV_FACTOR))

// TODO NOWAK: Implement TEMP and STRAIN_GAUGE macros to use more sensors
//#define TEMP_TO_WORD
//#define DISPLACEMENT_TO_WORD

#define ADC_BASE_MESSAGE_ID     0x100

#define SENSORS_PER_FRAME       4

// Handle an odd number of frames, by bumping up to the next whole number and padding unused bytes
#define NUM_ADC_FRAMES(sensorCount) (((sensorCount) + SENSORS_PER_FRAME - 1) / SENSORS_PER_FRAME)

// Functions ------------------------------------------------------------------------------------------------------------------
bool transmitADCValue(msbCan_t* can, adcSensor_t* sensors, uint8_t sensorCount)
{
   bool status = true;

   msbCanSignal_t msbSignals[sensorCount];
   
   for (int frame = 0; frame < NUM_ADC_FRAMES(sensorCount); frame++)
   {
        CANTxFrame txFrame =
        {
            .DLC = 8,
            .RTR = 0,
            .IDE = CAN_IDE_STD,
            .SID = ADC_BASE_MESSAGE_ID + frame,
        };

        for (int i = 0; i < SENSORS_PER_FRAME; i++) 
        {
            int sensorIndex = (frame * SENSORS_PER_FRAME) + i;

            if (sensorIndex < sensorCount)
            {   
                msbSignals[sensorIndex].id = sensorIndex;

                switch (sensors[sensorIndex].type)
                {
                    case VOLTAGE_SENSOR:
                        msbSignals[sensorIndex].word = VOLTAGE_TO_WORD(sensors[sensorIndex].value);
                        break;
                    // TODO NOWAK: Implement functionality for more sensor types
                    //case TERMISTOR:
                    //    msbSignals[sensorIndex].word = TEMP_TO_WORD(sensors[sensorIndex].value);
                    //    break;
                    //case STRAIN_GAUGE:
                    //    msbSignals[sensorIndex].word = DISPLACEMENT_TO_WORD(sensors[sensorIndex].value);
                    //    break;
                    default:
                        msbSignals[sensorIndex].word = 0;
                        break;
                }
                txFrame.data16[i] = msbSignals[sensorIndex].word;  
            }
        }

        msg_t result = canTransmitTimeout(can->config->driver, CAN_ANY_MAILBOX, &txFrame, can->config->timeout);
        #include "debug.h"
        debugPrintf("CAN result: %d\n", result);
        status &= result == MSG_OK;
   }

   return status;
}