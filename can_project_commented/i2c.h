/**
 * @file i2c.h
 * @brief I2C0 driver function declarations.
 *
 * Exposes low-level I2C primitives for initialisation, bus conditions,
 * single-byte write, and single-byte read with ACK or NACK.
 */

#ifndef I2C_H
#define I2C_H

#include "types.h"

void init_i2c(void);    /* Initialise I2C0 peripheral (100 kHz)          */
void i2c_start(void);   /* Generate START condition; wait for SI          */
void i2c_restart(void); /* Generate REPEATED START condition; wait for SI */
void i2c_stop(void);    /* Generate STOP condition; release bus           */
void i2c_write(u8 dat); /* Transmit one byte; wait for ACK                */
u8   i2c_nack(void);    /* Receive one byte and send NACK (last byte)     */
u8   i2c_mack(void);    /* Receive one byte and send ACK (more to follow) */

#endif /* I2C_H */
