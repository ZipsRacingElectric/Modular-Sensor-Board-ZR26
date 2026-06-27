// Header
#include "receive.h"

// Includes
#include "can.h"
#include "peripherals.h"
#include "can/eeprom_can.h"

// Functions ------------------------------------------------------------------------------------------------------------------

int8_t receiveMessage (void* node, CANRxFrame* frame)
{
	(void) node;

	// Check for recognized IDs
	switch (frame->SID)
	{

	case EEPROM_CAN_ID:
		eepromHandleCanCommand (frame, &CAND1, (eeprom_t*) &virtualEeprom);
		return 0;

	}

	return -1;
}