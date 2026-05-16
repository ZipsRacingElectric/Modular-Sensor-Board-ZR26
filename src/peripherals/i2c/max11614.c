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
    max11614->dADCConfig = (daughterADCConfig_t) 
    {
        .addr = config->addr,
        .i2c = config->i2c,
        .timeout = config->timeout,
    };
    if (!daughterADCInit(&max11614->dADC, &max11614->dADCConfig)) return false;

    // Create Setup Byte
    max11614->setupByte = max11614BuildSetupByte(
        MAX11614_REF_SEL,           // Configured based on macro in .h file
        MAX11614_CLK_INTERNAL,      // Internal clock
        MAX11614_UNIPOLAR,     // 0 to VREF
        MAX11614_RST_NORMAL         // No reset
    );

    // Write Setup Byte 
    write8bit(&max11614->dADC, max11614->setupByte);
    #if MAX11614_USE_INTERNAL_REF
        chThdSleepMilliseconds(10);     // Allow Internal Refernce Voltage to wake up
    #endif 
    return true;
}

bool max11614ReadChannels(max11614_t* max11614, max11614Results_t *results, uint8_t diffCount, uint8_t totalSensors)
{
    if (max11614 == NULL || results == NULL) return false;

    bool status = true;

    // Each differential sensor occupies two channels
    uint8_t diffChannelCount = diffCount * 2;

    // Read Differentiable Channels
    if (diffCount > 0) 
    {
        uint8_t configDiff = max11614BuildConfigByte(
            MAX11614_SCAN_AIN0_TO_CS,
            MAX11614_CS_CHANNEL(diffChannelCount - 1), // Scan starts at AIN0, must offset by 1
            MAX11614_DIFFERENTIABLE 
        );
        status &= write8bit(&max11614->dADC, configDiff);

        for (int i = 0; i < diffCount; i++)
        {
            status &= read12bit(&max11614->dADC, &results->channels[i]);
        }
    }

    uint8_t singleEndedCount = totalSensors - diffCount;

     // Read Single Ended Sensors
    if (singleEndedCount > 0)
    {
        for (int i = 0; i < singleEndedCount; i++)
        {
            uint8_t physicalChannel = diffChannelCount + i;
            uint8_t configSingle = max11614BuildConfigByte(
                MAX11614_SCAN_SINGLE,
                MAX11614_CS_CHANNEL(physicalChannel),
                MAX11614_SINGLE_ENDED
            );

            status &= write8bit(&max11614->dADC, configSingle);
            // Single ended results are stored after the differentiable sensors results
            status &= read12bit(&max11614->dADC, &results->channels[diffCount + i]);
        }
    }
    return status;
}
