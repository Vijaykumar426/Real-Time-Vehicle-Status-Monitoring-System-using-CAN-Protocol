/**
 * @file can.h
 * @brief CAN frame structure and CAN1 driver function declarations.
 *
 * Defines the CANF frame type used for both transmit and receive,
 * and exposes init / TX / RX functions implemented in can.c.
 */

#include "types.h"

/**
 * @brief CAN frame descriptor.
 *
 * Holds the message ID, control bit-fields, and up to 8 bytes of payload
 * split across two 32-bit words (DATA1, DATA2).
 */
typedef struct can_frame
{
    u32 ID;             /* 11-bit standard CAN message identifier          */

    struct bitfield
    {
        u32 RTR : 1;    /* Remote Transmission Request (1 = RTR frame)     */
        u32 DLC : 4;    /* Data Length Code: number of payload bytes (0-8) */
        u32 FF  : 1;    /* Frame Format (0 = standard, 1 = extended)       */
    } bfv;

    u32 DATA1;          /* First  4 payload bytes (bytes 0-3)              */
    u32 DATA2;          /* Second 4 payload bytes (bytes 4-7)              */

} CANF;

/* Initialise CAN1 peripheral and configure baud rate */
void can1_init(void);

/* Transmit a CAN frame on CAN1; blocks until TX buffer is free */
void can1_tx(CANF txF);

/* Non-blocking receive; returns 1 if a frame was read, 0 if buffer empty */
u8   can1_rx(CANF *rxF);
