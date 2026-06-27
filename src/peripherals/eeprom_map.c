// Header
#include "eeprom_map.h"

// Includes
#include "peripherals.h"

// C Standard Library
#include <string.h>

bool writeonlyWrite (void* eeprom, uint16_t addr, const void* data, uint16_t dataCount)
{
	(void) eeprom;
	(void) addr;
	(void) data;
	(void) dataCount;

	return false;
}

bool readonlyRead (void* eeprom, uint16_t addr, void* data, uint16_t dataCount)
{
	(void) eeprom;

	switch (addr)
	{
	case 0x0000: // RL damper position sample
		if (dataCount != sizeof (damperPositionRl.sample))
			return false;
		memcpy (data, &damperPositionRl.sample, sizeof (damperPositionRl.sample));
		return true;

	case 0x0002: // RR damper position sample
		if (dataCount != sizeof (damperPositionRr.sample))
			return false;
		memcpy (data, &damperPositionRr.sample, sizeof (damperPositionRr.sample));
		return true;

	case 0x0004: // FL damper position sample
		if (dataCount != sizeof (damperPositionFl.sample))
			return false;
		memcpy (data, &damperPositionFl.sample, sizeof (damperPositionFl.sample));
		return true;

	case 0x0006: // FR damper position sample
		if (dataCount != sizeof (damperPositionFr.sample))
			return false;
		memcpy (data, &damperPositionFr.sample, sizeof (damperPositionFr.sample));
		return true;

	case 0x0008: // Thermistor 0 sample
		if (dataCount != sizeof (thermistor0.sample))
			return false;
		memcpy (data, &thermistor0.sample, sizeof (thermistor0.sample));
		return true;

	case 0x000A: // Thermistor 1 sample
		if (dataCount != sizeof (thermistor1.sample))
			return false;
		memcpy (data, &thermistor1.sample, sizeof (thermistor1.sample));
		return true;

	case 0x000C: // Thermistor 2 sample
		if (dataCount != sizeof (thermistor2.sample))
			return false;
		memcpy (data, &thermistor2.sample, sizeof (thermistor2.sample));
		return true;

	case 0x000E: // Thermistor 3 sample
		if (dataCount != sizeof (thermistor3.sample))
			return false;
		memcpy (data, &thermistor3.sample, sizeof (thermistor3.sample));
		return true;

	}

	return false;
}