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

	// Start Can Driver
	static const CANConfig CAN_DRIVER_CONFIG =
	{
	.mcr = CAN_MCR_ABOM |
		CAN_MCR_AWUM |
		CAN_MCR_TXFP,
	.btr = CAN_BTR_SJW (0) |
		CAN_BTR_TS2 (1) |
		CAN_BTR_TS1 (10) |
		CAN_BTR_BRP (2)
	};
    
	canStart(&CAND1, &CAN_DRIVER_CONFIG);
	palClearLine (LINE_CAN1_STBY);

	// Initailize Modular Sensor Board 

	static msbConfig_t msbConfig = 
	{
		.sensor = NULL
	};

	static msb_t msb;

	if (!msbInit(&msb, &msbConfig)) 
	{
		hardFaultCallback();
		while (true);
	}

	// Main Loop ----------------------------------------------------------------------------------------------------------------
	while (true)
		chThdSleepMilliseconds (500);
}