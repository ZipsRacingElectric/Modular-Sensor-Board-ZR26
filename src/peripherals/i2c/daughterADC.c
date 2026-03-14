#include "daughterADC.h"
#include "modular_sensor_board.h"

// Init Function ------------------------------------------------------------------------------------------------------------------

bool daughterADCInit(daughterADC_t *dADC, const daughterADCConfig_t *config) 
{
    if (dADC == NULL || config == NULL) {
        return false;
    }

    // Store the configuration 
    dADC->config = config;

    return true;
}

// Helper Functions ------------------------------------------------------------------------------------------------------------

bool write8bit(daughterADC_t* dADC, uint8_t data)
{
    msg_t status;
    uint8_t txbuf[1] = { data};

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, txbuf, sizeof txbuf, NULL, 0, dADC->config->timeout);

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

bool read8bit(daughterADC_t* dADC, uint8_t* value) 
{
    msg_t status;
    uint8_t rxbuf;

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, NULL, 0, &rxbuf, sizeof rxbuf, dADC->config->timeout);

    if (status == MSG_OK) {
        *value = rxbuf;
    }

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

bool write12bit(daughterADC_t* dADC, uint16_t data) 
{
    msg_t status;
    uint8_t txbuf[2];

    txbuf[0] = (data >> 8) & 0xFF;
    txbuf[1] = data & 0xFF;

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, txbuf, sizeof txbuf, NULL, 0, dADC->config->timeout);

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}

bool read12bit(daughterADC_t* dADC, uint16_t* value)
{
    msg_t status;
    uint8_t rxbuf[2];

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cAcquireBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION
    
    status = i2cMasterTransmitTimeout(dADC->config->i2c, dADC->config->addr, NULL, 0, rxbuf, sizeof rxbuf, dADC->config->timeout);
    
    if (status == MSG_OK) {
        *value = ((uint16_t)rxbuf[0] << 8) | rxbuf[1];
        *value &= 0x0FFF;
    }

    #if I2C_USE_MUTUAL_EXCLUSION
    i2cReleaseBus(dADC->config->i2c);
    #endif // I2C_USE_MUTUAL_EXCLUSION

    return status == MSG_OK;
}



