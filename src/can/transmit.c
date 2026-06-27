#include "transmit.h"

// Includes -------------------------------------------------------------------------------------------------------------------

#include "can.h"
#include "peripherals.h"

// Conversions ----------------------------------------------------------------------------------------------------------------

#define DISPLACEMENT_TO_WORD(disp)	((uint16_t) ((disp) / 0.001953125f))

#define TEMPERATURE_TO_WORD(temp)	((uint16_t) (((temp) + 28.0f) / 0.03125f))

// Functions ------------------------------------------------------------------------------------------------------------------

msg_t transmitRearDamperPositionMessage (CANDriver* driver, sysinterval_t timeout)
{
	CANTxFrame damperRearMessage =
	{
		.DLC = 8,
		.IDE = CAN_IDE_STD,
		.SID = DAMPER_REAR_CAN_ID,
		.data16 =
		{
			DISPLACEMENT_TO_WORD (damperPositionRl.value),
			DISPLACEMENT_TO_WORD (damperPositionRr.value)
		}
	};

	return canTransmitTimeout (driver, CAN_ANY_MAILBOX, &damperRearMessage, timeout);
}

msg_t transmitFrontDamperPositionMessage (CANDriver* driver, sysinterval_t timeout)
{
	CANTxFrame damperFrontMessage =
	{
		.DLC = 8,
		.IDE = CAN_IDE_STD,
		.SID = DAMPER_FRONT_CAN_ID,
		.data16 =
		{
			DISPLACEMENT_TO_WORD (damperPositionFl.value),
			DISPLACEMENT_TO_WORD (damperPositionFr.value)
		}
	};

	return canTransmitTimeout (driver, CAN_ANY_MAILBOX, &damperFrontMessage, timeout);
}

msg_t transmitCoolingTempMessage (CANDriver* driver, sysinterval_t timeout)
{
	uint16_t temps [4] =
	{
		TEMPERATURE_TO_WORD (thermistor0.temperature),
		TEMPERATURE_TO_WORD (thermistor1.temperature),
		TEMPERATURE_TO_WORD (thermistor2.temperature),
		TEMPERATURE_TO_WORD (thermistor3.temperature)
	};

	CANTxFrame tempMessage =
	{
		.DLC = 6,
		.IDE = CAN_IDE_STD,
		.SID = TEMPERATURE_CAN_ID,
		.data8 =
		{
			temps [0],
			(temps [1] << 4) | (temps [0] >> 8),
			temps [1] >> 4,
			temps [2],
			(temps [3] << 4) | (temps [2] >> 8),
			temps [3] >> 4,
		}
	};

	return canTransmitTimeout (driver, CAN_ANY_MAILBOX, &tempMessage, timeout);
}