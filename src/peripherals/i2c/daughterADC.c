#include "daughterADC.h"
#include "modular_sensor_board.h"

// TODO:
// Be able to handle multiple daughter ADC's

// Create I2C transmit and receive functions to handle sampling

// Function Prototypes --------------------------------------------------------------------------------------------------------
static bool write8bit(daughterADC_t* dADC, uint8_t reg, uint8_t data);
static bool read8bit(daughterADC_t* dADC, uint8_t reg, uint8_t* value);
static bool write12bit(daughterADC_t* dADC, uint8_t reg, uint16_t data);
static bool read12bit(daughterADC_t* dADC, uint8_t reg, uint16_t* value);

// Functions ------------------------------------------------------------------------------------------------------------------

bool daughterADCInit(daughterADC_t *dADC, const daughterADCConfig_t *config) 
{
    if (dADC == NULL || config == NULL) {
        return false;
    }

    // Store the configuration 
    dADC->config = config;

    return true;
}

bool getRawADC(daughterADC_t* dADC, uint8_t reg, uint16_t* rawValue) 
{
    return read12bit(dADC, reg, rawValue);
}

// Helper Functions ------------------------------------------------------------------------------------------------------------

static bool write8bit(daughterADC_t* dADC, uint8_t reg, uint8_t data)
{
    msg_t status;
    uint8_t txbuf[2] = {reg, data};

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, txbuf, sizeof txbuf, NULL, 0, dADC->config->timeout);

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

static bool read8bit(daughterADC_t* dADC, uint8_t reg, uint8_t* value) 
{
    msg_t status;
    uint8_t txbuf = reg;
    uint8_t rxbuf;

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, &txbuf, sizeof txbuf, &rxbuf, sizeof rxbuf, dADC->config->timeout);

    if (status == MSG_OK) {
        *value = rxbuf;
    }

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

static bool write12bit(daughterADC_t* dADC, uint8_t reg, uint16_t data) 
{
    msg_t status;
    uint8_t txbuf[3];

    txbuf[0] = reg;
    txbuf[1] = (data >> 8) & 0xFF;
    txbuf[2] = data & 0xFF;

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, txbuf, sizeof txbuf, NULL, 0, dADC->config->timeout);

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

static bool read12bit(daughterADC_t* dADC, uint8_t reg, uint16_t* value)
{
    msg_t status;
    uint8_t txbuf = reg;
    uint8_t rxbuf[2];

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION
    
    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, &txbuf, sizeof txbuf, rxbuf, sizeof rxbuf, dADC->config->timeout);
    
    if (status == MSG_OK) {
        *value = ((uint16_t)rxbuf[0] << 8) | rxbuf[1];
        *value &= 0x0FFF;
    }

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}



