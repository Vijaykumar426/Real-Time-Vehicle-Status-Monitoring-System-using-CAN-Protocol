/**
 * @file ext_interrupt_defines.h
 * @brief External interrupt pin-select masks and VIC channel numbers.
 *
 * Maps physical GPIO pins to LPC21xx external interrupt lines (EINT)
 * and their corresponding VIC (Vectored Interrupt Controller) channels.
 *
 * Used by interrupt.c to configure the pin-select register and VIC.
 */

/* --- EINT0 on P0.1 --- */
#define EINT0_0_1       0x0000000C  /* PINSEL0 mask: P0.1 → EINT0 function  */
#define EINT0_VIC_CHNO  14          /* VIC channel number for EINT0          */

/* --- EINT1 on P0.3 (defined but not used in this project) --- */
#define EINT1_0_3       0x000000C0  /* PINSEL0 mask: P0.3 → EINT1 function  */
#define EINT1_VIC_CHNO  15          /* VIC channel number for EINT1          */

/* --- EINT2 on P0.7 --- */
#define EINT2_0_7       0x0000C000  /* PINSEL0 mask: P0.7 → EINT2 function  */
#define EINT2_VIC_CHNO  16          /* VIC channel number for EINT2          */
