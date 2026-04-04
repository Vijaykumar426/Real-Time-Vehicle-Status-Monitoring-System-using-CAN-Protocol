/**
 * @file MMA7660_DEFINES.h
 * @brief Register map and I2C address constants for the MMA7660FC accelerometer.
 *
 * The MMA7660 communicates over I2C at a 7-bit address of 0x4C.
 * Write address (shifted left + W bit) = 0x98; Read address = 0x99.
 */

/* 7-bit I2C address of the MMA7660FC */
#define MMA7660_ADDR    0x4C

/* --- Internal Register Addresses --- */
#define MMA_XOUT    0x00    /* X-axis output register (6-bit signed)        */
#define MMA_YOUT    0x01    /* Y-axis output register (6-bit signed)        */
#define MMA_ZOUT    0x02    /* Z-axis output register (6-bit signed)        */
#define MMA_TILT    0x03    /* Tilt status register                         */
#define MMA_SRST    0x04    /* Sampling Rate Status register                */
#define MMA_SPCNT   0x05    /* Sleep Count register                         */
#define MMA_INTSU   0x06    /* Interrupt Setup register                     */
#define MMA_MODE    0x07    /* Mode register (0x00 = standby, 0x01 = active)*/
#define MMA_SR      0x08    /* Auto-Wake/Sleep and Portrait/Landscape Config */

/* --- 8-bit I2C addresses (address byte sent on the bus) --- */
#define MMA7660_SA    0x98  /* Write address: 0x4C << 1 | 0 (write bit)    */
#define MMA7660_SA_R  0x99  /* Read  address: 0x4C << 1 | 1 (read bit)     */
