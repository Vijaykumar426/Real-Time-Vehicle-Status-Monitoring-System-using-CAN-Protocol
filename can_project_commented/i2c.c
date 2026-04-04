/**
 * @file i2c.c
 * @brief LPC21xx I2C0 peripheral driver.
 *
 * Provides bare-metal I2C primitives (start, stop, write, read).
 * Clock speed and pin assignments are defined in i2c_defines.h.
 * All functions poll the SI (Serial Interrupt) flag — no interrupts used.
 */

#include "types.h"
#include "i2c_defines.h"
#include <LPC21xx.h>

/**
 * @brief Initialise the I2C0 peripheral at 100 kHz.
 *
 * 1. Selects alternate function for P0.2 (SCL) and P0.3 (SDA).
 * 2. Sets clock high/low half-periods for the target bit rate.
 * 3. Enables the I2C module.
 */
void init_i2c(void)
{
    /* Route P0.2 → SCL and P0.3 → SDA via PINSEL0 */
    PINSEL0 |= SCL_0_2 | SDA_0_3;

    I2SCLH = I2C_DIVIDER;   /* SCL high period = PCLK / (2 × I2C_SPEED) */
    I2SCLL = I2C_DIVIDER;   /* SCL low  period = same (50 % duty cycle)  */

    I2CONSET = 1 << I2EN_BIT; /* Enable I2C hardware */
}

/**
 * @brief Generate an I2C START condition.
 *
 * Sets the STA bit, waits for the hardware to assert SI (condition sent),
 * then clears STA so it is not repeated automatically.
 */
void i2c_start(void)
{
    I2CONSET = 1 << STA_BIT;             /* Request START condition        */
    while (((I2CONSET >> SI_BIT) & 1) == 0); /* Wait — START transmitted  */
    I2CONCLR = 1 << STAC_BIT;           /* Clear STA to avoid extra starts */
}

/**
 * @brief Generate an I2C REPEATED START condition.
 *
 * Used during a read transaction to switch from write to read mode without
 * releasing the bus.  Clears SI first to let the hardware continue, then
 * waits for the new START to complete.
 */
void i2c_restart(void)
{
    I2CONSET = 1 << STA_BIT;             /* Request repeated START         */
    I2CONCLR = 1 << SIC_BIT;            /* Clear SI → hardware proceeds   */
    while (((I2CONSET >> SI_BIT) & 1) == 0); /* Wait — repeated START done */
    I2CONCLR = 1 << STAC_BIT;           /* Clear STA                       */
}

/**
 * @brief Generate an I2C STOP condition and release the bus.
 */
void i2c_stop(void)
{
    I2CONSET = 1 << STO_BIT;    /* Request STOP condition  */
    I2CONCLR = 1 << SIC_BIT;   /* Clear SI → hardware sends STOP */
}

/**
 * @brief Transmit one byte on the I2C bus.
 * @param dat  Byte to send (device address + R/W, register address, or data).
 *
 * Loads the byte into I2DAT, clears SI to start shifting, then polls until
 * the byte has been sent and an ACK/NACK has been received.
 */
void i2c_write(u8 dat)
{
    I2DAT = dat;                             /* Load byte into shift register */
    I2CONCLR = 1 << SIC_BIT;               /* Clear SI → begin transmission */
    while (((I2CONSET >> SI_BIT) & 1) == 0); /* Wait — byte sent + ACK done */
}

/**
 * @brief Receive one byte and respond with NACK (no further bytes wanted).
 * @return  The received byte.
 *
 * Used when reading the last (or only) byte from a device.
 * AA is not set, so the hardware automatically sends NACK after reception.
 */
u8 i2c_nack(void)
{
    I2CONCLR = 1 << SIC_BIT;               /* Clear SI → begin reception    */
    while (((I2CONSET >> SI_BIT) & 1) == 0); /* Wait — byte received         */
    return I2DAT;                            /* Return received byte          */
}

/**
 * @brief Receive one byte and respond with ACK (more bytes expected).
 * @return  The received byte.
 *
 * Sets the AA bit so the hardware sends ACK after the byte, signalling
 * to the slave that the master wants to continue reading.
 */
u8 i2c_mack(void)
{
    I2CONSET = 1 << AA_BIT;                 /* Assert ACK after reception    */
    I2CONCLR = 1 << SIC_BIT;               /* Clear SI → begin reception    */
    while (((I2CONSET >> SI_BIT) & 1) == 0); /* Wait — byte received         */
    I2CONCLR = 1 << AA_BIT;                 /* Clear AA for next operation   */
    return I2DAT;                            /* Return received byte          */
}
