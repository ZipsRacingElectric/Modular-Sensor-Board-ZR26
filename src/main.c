// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "modular_sensor_board.h"

#include "debug.h"

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
		debugPrintf("msbInitFailed");
		while (true);
	}

	// Main Loop ----------------------------------------------------------------------------------------------------------------
	while (true) 
	{
		if (!msbSample(&msb)) 
		{
			debugPrintf("msbSample Failed\r\n");
		}
		chThdSleepMilliseconds(200);
	}
}