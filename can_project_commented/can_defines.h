/**
 * @file can_defines.h
 * @brief CAN1 peripheral register bit definitions and baud-rate constants.
 *
 * Calculates BTR (Bus Timing Register) value for 125 kbps using a
 * 15 MHz PCLK and 15 time quanta per bit.
 */

#include "types.h"

/* --- Pin Function --- */
#define RD1_PIN_0_25    0x15440000  /* PINSEL1 mask: P0.25 = RD1 (CAN1 receive) */

/* --- Clock & Baud Rate --- */
#define PCLK            15000000    /* Peripheral clock frequency: 15 MHz        */
#define BIT_RATE        125000      /* CAN bus bit rate: 125 kbps                */
#define QUANTA          15          /* Time quanta per CAN bit period             */

/* Baud Rate Prescaler: divides PCLK down to the quantum clock */
#define BRP             (PCLK / (BIT_RATE * QUANTA))

/* Sample point target: 70% of the bit time */
#define SAMPLE_POINT    (0.7 * QUANTA)

/* Propagation + phase segment 1 (before sample point) */
#define TSEG1           ((u32)SAMPLE_POINT - 1)

/* Phase segment 2 (after sample point) */
#define TSEG2           (QUANTA - (1 + TSEG1))

/* Synchronisation Jump Width: capped at 4 quanta */
#define SJW             ((TSEG2 >= 5) ? 4 : (TSEG2 - 1))

/* SAM bit: 0 = single sample per bit */
#define SAM_BIT         0

/* Composed BTR register load value */
#define BTR_LVAL  ((SAM_BIT << 23) | ((TSEG2 - 1) << 20) | \
                   ((TSEG1 - 1) << 16) | ((SJW - 1) << 14) | (BRP - 1))

/* --- C1MOD register --- */
#define RM_BIT      0   /* Reset Mode bit: 1 = enter reset, 0 = normal operation */

/* --- C1CMR register --- */
#define TR_BIT      0   /* Transmission Request bit                               */
#define RRB_BIT     2   /* Release Receive Buffer bit                             */
#define STB1_BIT    5   /* Select TX Buffer 1 bit                                 */

/* --- C1GSR register (Global Status) --- */
#define RBS_BIT     0   /* Receive Buffer Status: 1 = message available           */
#define TBS1_BIT    2   /* TX Buffer 1 Status: 1 = buffer empty (ready to send)   */
#define TCS1_BIT    3   /* TX Complete Status 1: 1 = transmission complete         */

/* --- C1RFS register (Receive Frame Status) --- */
#define FF_BIT      31  /* Frame Format: 0 = standard (11-bit ID)                 */
#define RTR_BIT     30  /* Remote Transmission Request bit                        */
#define DLC_BIT     16  /* Data Length Code start bit (bits 19:16)                */

/* --- AFMR register (Acceptance Filter Mode) --- */
#define ACCOFF_BIT  0   /* Acceptance Filter Off bit                              */
#define ACCBP_BIT   1   /* Acceptance Filter Bypass bit: 1 = accept all messages  */
