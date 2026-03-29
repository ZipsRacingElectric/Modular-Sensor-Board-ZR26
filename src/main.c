// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "debug.h"

// ChibiOS
#include "ch.h"
#include "hal.h"
#include "modular_sensor_board.h"

// Interrupts -----------------------------------------------------------------------------------------------------------------

void hardFaultCallback (void)
{
	//while (true)
	//{
	//	palToggleLine (LINE_LED_FAULT);
	//	for (uint16_t index = 0; index < 32768; ++index);
	//}
}

// Entrypoint -----------------------------------------------------------------------------------------------------------------

int main (void)
{
	// ChibiOS Initialization
	halInit ();
	chSysInit ();

	// Debug Initialization
	ioline_t ledLine = LINE_LED_HEARTBEAT;
	debugHeartbeatStart (&ledLine, LOWPRIO);
	debugSerialInit (&SD1, NULL);

	// Set configs and initalize ----------------------------------------------------------------------------------------------

	static msb_t msb;
	static msbConfig_t msbConfig = { }; 

	if (!msbInit(&msb, &msbConfig)) 
	{
		hardFaultCallback();
		while (true);
	}

	// Main Loop ----------------------------------------------------------------------------------------------------------------
	while (true) 
	{
		if (!transmitADCValue(&msb.can, msb.sensors))
		{
			debugPrintf("Failed to transmit\r\n");
		}
		else 
		{
			debugPrintf("Can Transmit Successful\r\n");
		}
		chThdSleepMilliseconds (500);
	}
}