// Includes -------------------------------------------------------------------------------------------------------------------

#include "peripherals.h"
#include "can.h"
#include "debug.h"

// Config ---------------------------------------------------------------------------------------------------------------------

/// @brief The period to sample/transmit data at.
#define THREAD_PERIOD TIME_MS2I (1)

// Interrupts -----------------------------------------------------------------------------------------------------------------

void hardFaultCallback (void)
{

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

	// Init peripherals
	if (!peripheralsInit ())
	{
		debugPrintf ("Failed to init peripherals.\r\n");
		hardFaultCallback ();
		while (true);
	}

	// Init CAN bus
	if (!canInterfaceInit (NORMALPRIO))
	{
		debugPrintf ("Failed to init CAN interface.\r\n");
		hardFaultCallback ();
		while (true);
	}

	uint16_t index = 0;
	systime_t timeCurrent = chVTGetSystemTimeX ();
	while (true)
	{
		// Sample the latest sensor values
		peripheralsSample ();

		// Transmit said value to the CAN bus
		transmitRearDamperPositionMessage (&CAND1, THREAD_PERIOD);
		transmitFrontDamperPositionMessage (&CAND1, THREAD_PERIOD);

		// Only transmit the temp message at 1/10th the frequency, as it does not require high speeds.
		// TODO(Barach): Since the temperature data is still available at 1kHz, we use an average to downsample more
		// accurately. That is, the value transmitted is the average of the last 10 measurements.
		if (index >= 10)
		{
			transmitCoolingTempMessage (&CAND1, THREAD_PERIOD);
			index = 0;
		}
		else
			++index;

		// Sleep until the next loop
		chThdSleepUntilWindowed (timeCurrent, chTimeAddX (timeCurrent, THREAD_PERIOD));
		timeCurrent = chVTGetSystemTimeX ();
	}
}