/**
 * @file interrupt.c
 * @brief External interrupt driver for left/right indicator buttons.
 *
 * EINT0 (P0.1) = Left  indicator button.
 * EINT2 (P0.7) = Right indicator button.
 *
 * Each button press toggles the indicator state and immediately
 * broadcasts the new state over CAN1 so the receiver node can
 * update its LED animation.
 *
 * indicator_state values:
 *   0 = OFF
 *   1 = LEFT
 *   2 = RIGHT
 */

#include <LPC21XX.H>
#include "types.h"
#include "ext_interrupt_defines.h"
#include "interrupt.h"
#include "can.h"

extern CANF txf;            /* CAN TX frame shared with main (main_tx_rx.c)  */

s32 indicator_state = 0;    /* Current indicator state: 0=OFF, 1=LEFT, 2=RIGHT */

/**
 * @brief Initialise EINT0 and EINT2 as falling-edge vectored IRQs.
 *
 * Steps:
 *  1. Route P0.1 → EINT0 and P0.7 → EINT2 via PINSEL0.
 *  2. Enable both channels in the VIC (VICIntEnable).
 *  3. Register ISR addresses in VIC vector slots 0 and 1.
 *  4. Configure both interrupts as edge-triggered (EXTMODE).
 *     EXTPOLAR defaults to 0 → falling edge.
 */
void init_ext_interrupt(void)
{
    /* Select EINT0 on P0.1 and EINT2 on P0.7 */
    PINSEL0 |= EINT0_0_1 | EINT2_0_7;

    /* Enable EINT0 and EINT2 interrupt channels in the VIC */
    VICIntEnable = (1 << EINT0_VIC_CHNO) | (1 << EINT2_VIC_CHNO);

    /* Assign EINT0 to VIC vectored slot 0 (highest priority) */
    VICVectCntl0 = (1 << 5) | EINT0_VIC_CHNO;  /* Enable slot + channel no. */
    VICVectAddr0 = (u32)eint0_isr;              /* Load ISR address          */

    /* Assign EINT2 to VIC vectored slot 1 (next priority) */
    VICVectCntl1 = (1 << 5) | EINT2_VIC_CHNO;
    VICVectAddr1 = (u32)eint2_isr;

    /* Configure EINT0 (bit 0) and EINT2 (bit 2) as edge-triggered */
    EXTMODE = (1 << 2) | (1 << 0);
    /* EXTPOLAR left at reset value (0) → falling edge triggers both */
}

/**
 * @brief EINT0 ISR — handles the Left indicator button press.
 *
 * Toggles indicator_state:
 *   If already LEFT (1) → turn OFF (0).
 *   Otherwise           → turn LEFT ON (1), cancel any RIGHT.
 *
 * Sends the new state via CAN, then clears the interrupt flags.
 */
void eint0_isr(void) __irq
{
    if (indicator_state == 1)
    {
        indicator_state = 0;    /* Second press: turn indicator OFF          */
    }
    else
    {
        indicator_state = 1;    /* First press: activate LEFT indicator      */
    }

    txf.DATA1 = indicator_state;
    can1_tx(txf);               /* Broadcast new state to receiver node      */

    EXTINT = 1 << 0;            /* Clear EINT0 flag in External Interrupt reg */
    VICVectAddr = 0;            /* Signal end-of-interrupt to VIC            */
}

/**
 * @brief EINT2 ISR — handles the Right indicator button press.
 *
 * Toggles indicator_state:
 *   If already RIGHT (2) → turn OFF (0).
 *   Otherwise            → turn RIGHT ON (2), cancel any LEFT.
 *
 * Sends the new state via CAN, then clears the interrupt flags.
 */
void eint2_isr(void) __irq
{
    if (indicator_state == 2)
    {
        indicator_state = 0;    /* Second press: turn indicator OFF          */
    }
    else
    {
        indicator_state = 2;    /* First press: activate RIGHT indicator     */
    }

    txf.DATA1 = indicator_state;
    can1_tx(txf);               /* Broadcast new state to receiver node      */

    EXTINT = 1 << 2;            /* Clear EINT2 flag in External Interrupt reg */
    VICVectAddr = 0;            /* Signal end-of-interrupt to VIC            */
}
