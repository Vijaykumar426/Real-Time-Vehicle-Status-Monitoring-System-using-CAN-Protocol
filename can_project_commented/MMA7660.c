/**
 * @file MMA7660.c
 * @brief MMA7660FC 3-axis accelerometer driver over I2C.
 *
 * Handles device initialisation, raw register read/write, signed axis
 * conversion (6-bit two's complement → s8), and airbag trigger logic.
 */

#include <LPC21XX.H>
#include "MMA7660.h"
#include "types.h"
#include "i2c.h"
#include "MMA7660_defines.h"
#include "lcd.h"
#include "delay.h"

/**
 * @brief Initialise the MMA7660 in the correct power-up sequence.
 *
 * 1. Short delay after power-on for supply to settle.
 * 2. Force standby mode (required before changing configuration).
 * 3. Set sample rate register (0x00 = default, AUTO-SLEEP disabled).
 * 4. Activate the device.
 */
void MMA7660_Init(void)
{
    delay_ms(10);                       /* Wait for power-on settle          */
    mma7660_write(MMA_MODE, 0x00);      /* Enter standby mode                */
    delay_ms(10);
    mma7660_write(MMA_SR, 0x00);        /* Set sample rate (default/off)     */
    mma7660_write(MMA_MODE, 0x01);      /* Activate device (active mode)     */
    delay_ms(10);                       /* Wait for first valid sample       */
}

/**
 * @brief Write one byte to an MMA7660 register.
 * @param reg   Target register address (see MMA7660_DEFINES.h).
 * @param data  Byte value to write.
 *
 * I2C sequence: START → write address → register → data → STOP.
 */
void mma7660_write(u8 reg, u8 data)
{
    i2c_start();
    i2c_write(MMA7660_SA);      /* Device write address (0x98)   */
    i2c_write(reg);             /* Target register               */
    i2c_write(data);            /* Value to write                */
    i2c_stop();
    delay_ms(2);                /* Allow register update to settle */
}

/**
 * @brief Read one byte from an MMA7660 register.
 * @param reg  Source register address.
 * @return     Raw 8-bit register value.
 *
 * I2C sequence: START → write address → register →
 *               REPEATED START → read address → data (NACK) → STOP.
 */
u8 mma7660_read(u8 reg)
{
    u8 data;
    i2c_start();
    i2c_write(MMA7660_SA);      /* Device write address (set register pointer) */
    i2c_write(reg);             /* Register to read from                        */
    i2c_restart();              /* Switch bus direction without releasing it     */
    i2c_write(MMA7660_SA_R);    /* Device read address (0x99)                  */
    data = i2c_nack();          /* Read single byte, reply NACK (no more)       */
    i2c_stop();
    delay_ms(2);
    return data;
}

/**
 * @brief Convert a raw 6-bit MMA7660 register value to a signed 8-bit integer.
 * @param val  Raw register byte (bits [5:0] are the signed 6-bit result).
 * @return     Signed acceleration value in the range -32 .. +31.
 *
 * The MMA7660 uses 6-bit two's complement.  Bit 5 is the sign bit.
 * Sign-extend: if bit 5 is set, OR the upper two bits with 0xC0.
 */
static s8 convert_data(u8 val)
{
    val &= 0x3F;            /* Mask to 6-bit value (bits 5:0)      */
    if (val & 0x20)
    {
        val |= 0xC0;        /* Sign-extend: set bits 7 and 6       */
    }
    return (s8)val;
}

/**
 * @brief Read and return the signed X-axis acceleration.
 * @return  X-axis value in MMA7660 g-units (-32 .. +31).
 */
s8 mma7660_get_X(void)
{
    return convert_data(mma7660_read(MMA_XOUT));
}

/**
 * @brief Read and return the signed Y-axis acceleration.
 * @return  Y-axis value in MMA7660 g-units (-32 .. +31).
 */
s8 mma7660_get_Y(void)
{
    return convert_data(mma7660_read(MMA_YOUT));
}

/**
 * @brief Read and return the signed Z-axis acceleration.
 * @return  Z-axis value in MMA7660 g-units (-32 .. +31).
 */
s8 mma7660_get_Z(void)
{
    return convert_data(mma7660_read(MMA_ZOUT));
}
