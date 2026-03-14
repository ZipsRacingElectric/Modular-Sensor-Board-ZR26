#include "max11614.h"

// Functions ------------------------------------------------------------------------------------------------------------------

uint8_t max11614BuildSetupByte(max11614RefSelect_t ref, max11614Clock_t clk, max11614Polarity_t polarity, max11614Reset_t rst)
{
    return (1                  << MAX11614_SETUP_REG_BIT) // Shift in 1 for Setup Byte
        | (((ref >> 2) & 0x01) << MAX11614_SEL2_BIT)
        | (((ref >> 1) & 0x01) << MAX11614_SEL1_BIT)
        | (((ref >> 0) & 0x01) << MAX11614_SEL0_BIT)
        | (clk                 << MAX11614_CLK_BIT)
        | (polarity            << MAX11614_BIPUNI_BIT)
        | (rst                 << MAX11614_RST_BIT);
}

uint8_t max11614BuildConfigByte(max11614ScanMode_t scan, uint8_t channelSelect, max11614InputMode_t inputMode)
{
    return (0                   << MAX11614_CONFIG_REG_BIT) // Shift in 0 for Config Byte
        | (((scan >> 1) & 0x01) << MAX11614_SCAN1_BIT)
        | (((scan >> 0) & 0x01) << MAX11614_SCAN0_BIT)
        | channelSelect                                     // Channel select already pre shifted using conversion macro
        | (inputMode            << MAX11614_SGLDIF_BIT);
}

bool max11614Init(max11614_t* max11614, const max11614Config_t* config)
{
    // Save configuration 
    if (max11614 == NULL || config == NULL) return false;
    
    max11614->config = config;

    // Configure and intialize daughterADC I2C helper functions
    daughterADCConfig_t dADCConfig = 
    {
        .addr = config->addr,
        .i2c = config->i2c,
        .timeout = config->timeout,
    };

    if (!daughterADCInit(&max11614->dADC, &dADCConfig)) return false;

    // Create Setup Byte
    max11614->setupByte = max11614BuildSetupByte(
        MAX11614_REF_INTERNAL_ON,   // Internal 4.096V, always on
        MAX11614_CLK_INTERNAL,      // Internal clock
        MAX11614_UNIPOLAR,     // 0 to VREF
        MAX11614_RST_NORMAL         // No reset
    );

    // Create Differentiable Channels Config Byte
    max11614->configDiff = max11614BuildConfigByte(
        MAX11614_SCAN_AIN0_TO_CS,    // Scan from channel 0 - 3
        MAX11614_CS_AIN3,   // CS = Channel 3 
        MAX11614_DIFFERENTIABLE
    );

    // Single Ended Channels Config Byte not built in init, as it changes per channel
    // Is built inside of max11614ReadChannel

    // Write setupByte 
    write8bit(&max11614->dADC, max11614->setupByte);
    chThdSleepMilliseconds(10);     // Allow Internal Refernce Voltage to wake up

    return true;
}

bool max11614ReadChannels(max11614_t* max11614, max11614Results_t *results)
{
    bool status = true;

    // Read differential channels AIN0/1 and AIN2/3
    status &= write8bit(&max11614->dADC, max11614->configDiff);
    status &= read12bit(&max11614->dADC, &results->differentiable[0]);
    status &= read12bit(&max11614->dADC, &results->differentiable[1]);

    // Build Single Ended Channels Config Byte inside of for loop.
    // MAX11614 Cannot Scan Upper Half of channels, must scan each chanel one at a time. 
    for (int i = 0; i < 4; i++)
    {
        uint8_t configSingle = max11614BuildConfigByte(
            MAX11614_SCAN_SINGLE,
            MAX11614_CS_CHANNEL(i + 4),     // Scan Channels AIN4 - AIN7, shift for loop up by 4 
            MAX11614_SINGLE_ENDED
        );
        status &= write8bit(&max11614->dADC, configSingle);
        status &= read12bit((daughterADC_t*)max11614, &results->singleEnded[i]);
    }
    return status;
}
