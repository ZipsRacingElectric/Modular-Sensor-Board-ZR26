// Includes -------------------------------------------------------------------------------------------------------------------

#include "msb_receive.h"

// Gloabals ------------------------------------------------------------------------------------------------------------------

#define EEPROM_COMMAND_MESSAGE_ID 0x016

extern mc24lc32_t physicalEeprom;

// Initialize CAN Thread
static CAN_THREAD_WORKING_AREA(msbCanThreadWA);

static const canThreadConfig_t MSB_CAN_THREAD_CONFIG =
{
    .name = "MSB CAN Rx",
    .driver = &CAND1,
    .period = TIME_MS2I(20),
    .nodes = NULL,
    .nodeCount = 0,
    .rxHandler = msbCanReceiveMessage,
    .bridgeDriver = NULL,
};

// Functions ------------------------------------------------------------------------------------------------------------------

void msbReceiveStart()
{
    canThreadStart(&msbCanThreadWA, sizeof(msbCanThreadWA), NORMALPRIO, &MSB_CAN_THREAD_CONFIG);
}

int8_t msbCanReceiveMessage (void* config, CANRxFrame* frame) 
{
    (void) config;

    // Check can ID
    if (frame->SID == EEPROM_COMMAND_MESSAGE_ID) 
    {
        // If the command message was received, call the handler.
		eepromHandleCanCommand (frame, MSB_CAN_THREAD_CONFIG.driver, (eeprom_t*) &physicalEeprom);
		return 0;
    }

    return -1;
}
