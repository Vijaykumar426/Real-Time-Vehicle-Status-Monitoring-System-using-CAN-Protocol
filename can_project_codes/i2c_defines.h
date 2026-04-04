/**
 * @file i2c_defines.h
 * @brief I2C peripheral pin, clock, and register bit definitions.
 *
 * Configures I2C0 for 100 kHz (standard mode) on P0.2 (SCL) and P0.3 (SDA).
 * Clock divider is derived from PCLK so the resulting SCL = I2C_SPEED.
 */

#ifndef I2C_DEFINES_H
#define I2C_DEFINES_H

/* --- Pin Function Select values for PINSEL0 --- */
#define SCL_0_2     0x00000010  /* P0.2 → SCL (I2C clock)    */
#define SDA_0_3     0x00000040  /* P0.3 → SDA (I2C data)     */

/* --- Clock configuration --- */
#define FOSC        12000000            /* Crystal oscillator: 12 MHz   */
#define CCLK        (5 * FOSC)          /* Core clock: PLL × 5 = 60 MHz */
#define PCLK        (CCLK / 4)          /* Peripheral clock: 15 MHz     */
#define I2C_SPEED   100000              /* Target I2C bit rate: 100 kHz */

/* Half-period for SCL — written to both I2SCLH and I2SCLL */
#define I2C_DIVIDER ((PCLK / I2C_SPEED) / 2)

/* --- I2CONSET register bit positions --- */
#define AA_BIT      2   /* Assert Acknowledge: 1 = send ACK on next receive */
#define SI_BIT      3   /* Serial Interrupt flag: set when state changes     */
#define STO_BIT     4   /* STOP condition bit                                */
#define STA_BIT     5   /* START condition bit                               */
#define I2EN_BIT    6   /* I2C Enable bit                                    */

/* --- I2CONCLR register bit positions (write 1 to clear) --- */
#define AAC_BIT     2   /* Clear AA bit   */
#define SIC_BIT     3   /* Clear SI flag  */
#define STAC_BIT    5   /* Clear STA bit  */
#define I2ENC_BIT   6   /* Clear I2EN bit */

#endif /* I2C_DEFINES_H */
