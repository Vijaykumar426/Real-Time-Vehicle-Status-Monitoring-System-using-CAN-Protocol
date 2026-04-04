/**
 * @file MMA7660.h
 * @brief MMA7660FC accelerometer driver function declarations.
 *
 * Provides initialisation, raw register read/write, axis data
 * retrieval, and the airbag trigger logic that uses the axis values.
 */

#include "types.h"

void MMA7660_Init(void);        /* Initialise accelerometer (standby → active)    */
void mma7660_write(u8, u8);     /* Write one byte to a register: (reg, data)      */
u8   mma7660_read(u8);          /* Read  one byte from a register: (reg) → value  */
s8   mma7660_get_X(void);       /* Get signed X-axis acceleration value           */
s8   mma7660_get_Y(void);       /* Get signed Y-axis acceleration value           */
s8   mma7660_get_Z(void);       /* Get signed Z-axis acceleration value           */
void trigger_airbag(void);      /* Check axes and update LCD "Air Bag: ON/OFF"    */
