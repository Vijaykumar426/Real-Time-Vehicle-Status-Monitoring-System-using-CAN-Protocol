/**
 * @file can.c
 * @brief LPC21xx CAN1 peripheral driver — init, transmit, and receive.
 *
 * Uses CAN1 in bypass acceptance-filter mode so all message IDs are
 * accepted.  Baud rate is defined in can_defines.h (default: 125 kbps).
 */

#include <LPC21XX.h>
#include "types.h"
#include "delay.h"
#include "can_defines.h"
#include "can.h"

/**
 * @brief Initialise CAN1 at the baud rate defined in can_defines.h.
 *
 * Steps:
 *  1. Route P0.25 to RD1 (CAN1 RX) via PINSEL1.
 *  2. Enter Reset Mode so BTR can be written.
 *  3. Enable Acceptance Filter bypass (accept all message IDs).
 *  4. Write Bus Timing Register.
 *  5. Leave Reset Mode → CAN1 becomes active.
 */
void can1_init(void)
{
    PINSEL1 |= (RD1_PIN_0_25);         /* P0.25 → RD1 alternate function        */

    C1MOD |= 1 << RM_BIT;              /* Enter Reset Mode (required before BTR) */

    AFMR &= ~(1 << ACCOFF_BIT);        /* Enable Acceptance Filter               */
    AFMR |=  1 << ACCBP_BIT;           /* Bypass filter — accept all IDs         */

    C1BTR = BTR_LVAL;                  /* Load pre-calculated bus timing value   */

    C1MOD &= ~(1 << RM_BIT);           /* Leave Reset Mode → CAN1 is now active  */
}

/**
 * @brief Transmit a CAN frame on CAN1.
 * @param txF  Frame to send (ID, RTR, DLC, DATA1, DATA2 must be set by caller).
 *
 * Blocks until TX buffer 1 is free, loads the frame, and waits for
 * transmission to complete before returning.
 */
void can1_tx(CANF txF)
{
    /* Wait until TX buffer 1 is free (TBS1 = 1 means buffer available) */
    while (((C1GSR >> TBS1_BIT) & 1) == 0);

    C1TID1 = txF.ID;                               /* Set message ID              */

    /* Build Frame Info: RTR flag and Data Length Code */
    C1TFI1 = ((txF.bfv.RTR << RTR_BIT) | (txF.bfv.DLC << DLC_BIT));

    if (txF.bfv.RTR != 1)
    {
        C1TDA1 = txF.DATA1;                        /* Load payload bytes 0-3      */
        C1TDB1 = txF.DATA2;                        /* Load payload bytes 4-7      */
    }

    /* Select TX buffer 1 and issue Transmission Request */
    C1CMR |= ((1 << STB1_BIT) | (1 << TR_BIT));

    /* Wait until transmission is complete */
    while (((C1GSR >> TCS1_BIT) & 1) == 0);
}

/**
 * @brief Non-blocking CAN1 receive.
 * @param rxF  Pointer to frame struct that will be filled on success.
 * @return     1 if a frame was available and copied; 0 if RX buffer was empty.
 *
 * Checks the Receive Buffer Status bit; if a frame is waiting it reads
 * the ID, control bits, and payload, then releases the buffer.
 */
u8 can1_rx(CANF *rxF)
{
    /* Return immediately if no frame is waiting */
    if (((C1GSR >> RBS_BIT) & 1) == 0)
    {
        return 0;
    }

    rxF->ID = C1RID;                               /* Read message ID             */

    rxF->bfv.RTR = ((C1RFS >> RTR_BIT) & 1);      /* Extract RTR flag            */
    rxF->bfv.DLC = ((C1RFS >> DLC_BIT) & 15);     /* Extract Data Length Code    */

    if (rxF->bfv.RTR == 0)
    {
        rxF->DATA1 = C1RDA;                        /* Read payload bytes 0-3      */
        rxF->DATA2 = C1RDB;                        /* Read payload bytes 4-7      */
    }

    C1CMR |= (1 << RRB_BIT);                       /* Release RX buffer for reuse */

    return 1;
}
