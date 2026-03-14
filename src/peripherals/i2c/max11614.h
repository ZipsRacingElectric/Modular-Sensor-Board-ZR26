#ifndef MAX11614_H
#define MAX11614_H

// ADC max11614 ------------------------------------------------------------------------------------------------------------
//
// Author: Jake Nowak
// Date Created: 2026.03.04
//
// Description: A Daughter ADC connected to the Modular Sensor Board

// Includes -----------------------------------------------------------------------------------------------------------------

#include "hal.h"
#include "daughterADC.h"

// Bit Position Macros Setup Byte --------------------------------------------------------------------------------------------

#define MAX11614_SETUP_REG_BIT      7
#define MAX11614_SEL2_BIT           6
#define MAX11614_SEL1_BIT           5
#define MAX11614_SEL0_BIT           4
#define MAX11614_CLK_BIT            3
#define MAX11614_BIPUNI_BIT         2
#define MAX11614_RST_BIT            1
#define MAX_DONT_CARE_BIT           0 // This bit doesn't influence setup byte, doesn't need to be built

// Bit Position Marcos Config Byte -------------------------------------------------------------------------------------------

#define MAX11614_CONFIG_REG_BIT     7
#define MAX11614_SCAN1_BIT          6
#define MAX11614_SCAN0_BIT          5
#define MAX11614_CS_SHIFT_BIT       1 // CS0 - CS3 Take up bits 1 - 4
#define MAX11614_SGLDIF_BIT         0

// Channel Select Converstions ------------------------------------------------------------------------------------------------

// Used for Config Byte CS_SHIFT_BIT
#define MAX11614_CS_CHANNEL(ch)         (((ch) & 0x0F) << MAX11614_CS_SHIFT_BIT)
#define MAX11614_CS_AIN0                MAX11614_CS_CHANNEL(0)
#define MAX11614_CS_AIN1                MAX11614_CS_CHANNEL(1)
#define MAX11614_CS_AIN2                MAX11614_CS_CHANNEL(2)
#define MAX11614_CS_AIN3                MAX11614_CS_CHANNEL(3)
#define MAX11614_CS_AIN4                MAX11614_CS_CHANNEL(4)
#define MAX11614_CS_AIN5                MAX11614_CS_CHANNEL(5)
#define MAX11614_CS_AIN6                MAX11614_CS_CHANNEL(6)
#define MAX11614_CS_AIN7                MAX11614_CS_CHANNEL(7)

// Enums ---------------------------------------------------------------------------------------------------------------------

/// @brief Bit Determining Setup or Config Byte of MAX11614
typedef enum 
{
    MAX11614_REG_CONFIG = 0,
    MAX11614_REG_SETUP = 1
} max11614RegSelect_t;

/// @brief Reference Voltage of MAX11614 ADC
typedef enum 
{
    // INPUTS
    MAX11614_REF_VDD            = 0b000,      
    MAX11614_REF_EXTERNAL       = 0b010,
    MAX11614_REF_INTERNAL_OFF   = 0b100,
    MAX11614_REF_INTERNAL_ON    = 0b101,
    // OUTPUTS
    MAX11614_REF_INTERNAL_OUT_OFF = 0b110,
    MAX11614_REF_INTERNAL_OUT_ON = 0b111,

} max11614RefSelect_t;

/// @brief Clock of MAX11614 ADC
typedef enum 
{
    MAX11614_CLK_INTERNAL   = 0,
    MAX11614_CLK_EXTERNAL   = 1,
} max11614Clock_t;

/// @brief MAX11614 ADC Channel Unipolar or Bipolar
typedef enum 
{
    MAX11614_UNIPOLAR   = 0,
    MAX11614_BIPOLAR    = 1,
} max11614Polarity_t;

/// @brief Only if 0 (reset state) reset the configuration register to default state
typedef enum 
{
    MAX11614_RST_RESET  = 0,
    MAX11614_RST_NORMAL = 1,
} max11614Reset_t;

/// @brief Scan options of max11614 ADC, ranges from AIN0 - AIN7, based on CS configuration
typedef enum 
{
    MAX11614_SCAN_AIN0_TO_CS    = 0b00,
    MAX11614_SCAN_CS_8TIMES     = 0b01,
    MAX11614_SCAN_AIN6_TO_CS    = 0b10,
    MAX11614_SCAN_SINGLE        = 0b11,
} max11614ScanMode_t;

 /// @brief MAX11614 ADC Channel Single Ended or Differentiable
typedef enum 
{
    MAX11614_DIFFERENTIABLE = 0,
    MAX11614_SINGLE_ENDED   = 1,
} max11614InputMode_t;

// Result Struct -----------------------------------------------------------------------------------------------------------

typedef struct 
{
    uint16_t differentiable[2]; // 2 Differentiable Sensors AIN0/1 and AIN2/3
    uint16_t singleEnded[4];    // 4 Single Ended Sensors AIN4 through AIN7

} max11614Results_t;

// ADC Config --------------------------------------------------------------------------------------------------------------
typedef struct 
{
    i2caddr_t         addr;
    I2CDriver*        i2c;
    sysinterval_t     timeout;

} max11614Config_t;

typedef struct 
{
    const max11614Config_t* config;
    daughterADC_t dADC;

    uint8_t setupByte;
    uint8_t configDiff;

} max11614_t;

// Functions ------------------------------------------------------------------------------------------------------------------

/**
 * @brief Initialized the device, with the specilized configuration.
 * 
 * @param max11614 The device to initialize.
 * @param config The configuration to use.
 * @return True if successful, false if hardware error occured.
 */
bool max11614Init(max11614_t* max11614, const max11614Config_t* config);

/**
 * @brief Build the Setup Byte of the max11614 based on configuration
 * 
 * @param ref 
 * @param clk 
 * @param polarity 
 * @param rst 
 * @return uint8_t 
 */
uint8_t max11614BuildSetupByte(max11614RefSelect_t ref, max11614Clock_t clk, max11614Polarity_t polarity, max11614Reset_t rst);

/**
 * @brief  Build the Config Byte of the max11614 based on configuration
 * 
 * @param scan 
 * @param channelSelect 
 * @param inputMode 
 * @return uint8_t 
 */
uint8_t max11614BuildConfigByte(max11614ScanMode_t scan, uint8_t channelSelect, max11614InputMode_t inputMode);

/**
 * @brief Reads the max11614 ADC channels using daughterADC I2C helper functions.
 * 
 * @param max11614 Pointer to the object being sampled.
 * @return True if successful, False if I2C transmission failed.
 */
bool max11614ReadChannels(max11614_t* max11614, max11614Results_t* results);

#endif 