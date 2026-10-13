// Header
#include "peripherals.h"

// Includes -------------------------------------------------------------------------------------------------------------------

// Includes
#include "debug.h"

// Global Peripherals ---------------------------------------------------------------------------------------------------------

virtualEeprom_t virtualEeprom;
mc24lc32_t physicalEeprom;
eeprom_t readonlyWriteonlyEeprom;
eepromMap_t* eepromMap;

max11614_t adc;

// Configuration --------------------------------------------------------------------------------------------------------------

/// @brief Configuration of the I2C 1 bus.
static const I2CConfig I2C1_CONFIG =
{
    .op_mode		= OPMODE_I2C,
	.clock_speed	= 100000,
	.duty_cycle		= STD_DUTY_CYCLE
};

/// @brief Configuration of the I2C 2 bus.
/// @note This uses fast mode I2C for getting faster ADC results.
static const I2CConfig I2C2_CONFIG =
{
    .op_mode		= OPMODE_I2C,
	.clock_speed	= 400000,
	.duty_cycle		= FAST_DUTY_CYCLE_2
};

static const mc24lc32Config_t PHYSICAL_EEPROM_CONFIG =
{
	.addr			= 0x50,
	.i2c			= &I2CD1,
	.timeout		= TIME_MS2I (500),
	.magicString	= "MSB_2026.06.13",
	.dirtyHook		= NULL,
};

/// @brief Configuration of the device's 'virtual' eeprom.
static const virtualEepromConfig_t VIRTUAL_EEPROM_CONFIG =
{
	.count = 2,
	.entries =
	{
		{
			.eeprom	= (eeprom_t*) &physicalEeprom,
			.addr	= 0x0000,
			.size	= MC24LC32_SIZE
		},
		{
			.eeprom	= &readonlyWriteonlyEeprom,
			.addr	= 0x1000,
			.size	= 0x1000
		}
	}
};

static const max11614Config_t ADC_CONFIG =
{
	.addr			= 0x33,
	.i2c			= &I2CD2,
	.timeout		= TIME_MS2I (1),
	.sampleVdd		= 4095
};

// Functions ------------------------------------------------------------------------------------------------------------------

bool peripheralsInit ()
{
	// I2C 1 driver initialization.
	i2cStart (&I2CD1, &I2C1_CONFIG);
	if (I2CD1.state != I2C_READY)
	{
		debugPrintf ("I2C1 init failed. Try power cycling the device.\r\n");
		return false;
	}

	// I2C 2 driver initialization.
	i2cStart (&I2CD2, &I2C2_CONFIG);
	if (I2CD2.state != I2C_READY)
	{
		debugPrintf ("I2C2 init failed. Try power cycling the device.\r\n");
		return false;
	}

	// Physical EEPROM initialization (only exit early if a failure occurred).
	if (!mc24lc32Init (&physicalEeprom, &PHYSICAL_EEPROM_CONFIG) && physicalEeprom.state == MC24LC32_STATE_FAILED)
	{
		debugPrintf ("Physical EEPROM init failed.\r\n");
		return false;
	}
	if (physicalEeprom.state == MC24LC32_STATE_INVALID)
	{
		debugPrintf ("EEPROM invalid - Must by configured via can-eeprom-cli.\r\n");

		// TODO (Nowak):
			// Flash fault LED
			// Transmit CAN Error to dashboard
	}

	virtualEepromInit (&virtualEeprom, &VIRTUAL_EEPROM_CONFIG);
	eepromInit (&readonlyWriteonlyEeprom, writeonlyWrite, readonlyRead);
	mc24lc32Init (&physicalEeprom, &PHYSICAL_EEPROM_CONFIG);
	eepromMap = (eepromMap_t*) physicalEeprom.cache;

	if (!max11614Init (&adc, &ADC_CONFIG))
	{
		debugPrintf ("I2C ADC init failed.\r\n");
		return false;
	}

	return true;
}