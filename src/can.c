// Header
#include "can.h"

// Includes
#include "can/receive.h"
#include "can/can_thread.h"

// Configuration --------------------------------------------------------------------------------------------------------------

/// @brief The configuration of the CAN 1 bus.
static const CANConfig CAN1_CONFIG =
{
	.mcr = CAN_MCR_ABOM |
		CAN_MCR_AWUM |
		CAN_MCR_TXFP,
	.btr = CAN_BTR_SJW (0) |
		CAN_BTR_TS2 (1) |
		CAN_BTR_TS1 (10) |
		CAN_BTR_BRP (2)
};

/// @brief The configuration of the CAN 1 receive thread
static const canThreadConfig_t CAN_THREAD_CONFIG =
{
	.name			= "can1_rx",
	.driver			= &CAND1,
	.period			= TIME_MS2I (10),
	.nodes			= NULL,
	.nodeCount		= 0,
	.rxHandler		= receiveMessage,
	.bridgeDriver	= NULL
};

// Globals --------------------------------------------------------------------------------------------------------------------

static CAN_THREAD_WORKING_AREA (can1ThreadWa);

// Functions ------------------------------------------------------------------------------------------------------------------

bool canInterfaceInit (tprio_t priority)
{
    // Start the CAN 1 driver
    if (canStart(&CAND1, &CAN1_CONFIG) != MSG_OK)
		return false;
	palClearLine (LINE_CAN1_STBY);

	// Start the CAN 1 receive thread
	canThreadStart (can1ThreadWa, sizeof (can1ThreadWa), priority, &CAN_THREAD_CONFIG);

    return true;
}