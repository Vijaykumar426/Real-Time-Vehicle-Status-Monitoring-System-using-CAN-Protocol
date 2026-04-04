/**
 * @file indicator_node_rx.c
 * @brief Indicator receiver node — animates LEDs based on CAN indicator state.
 *
 * This is the main entry point for the Indicator LED Node (CAN RX node).
 *
 * Hardware:
 *   - 8 LEDs on P0.0–P0.7 (active-LOW — IOCLR turns an LED on).
 *   - Activity LED on P0.21.
 *   - CAN1 bus receiving from the Dashboard Node.
 *
 * CAN message consumed:
 *   ID    = 2   (Indicator state message)
 *   DATA1 = indicator_state  (0=OFF, 1=LEFT, 2=RIGHT)
 *
 * LED animation:
 *   LEFT  (1): LEDs light up left-to-right (P0.0 → P0.7) then reset.
 *   RIGHT (2): LEDs light up right-to-left (P0.7 → P0.0) then reset.
 *   OFF   (0): All 8 LEDs turned off.
 *
 * State change detection resets the animation position so direction
 * switches are immediately reflected without visual glitches.
 */

#include <LPC21XX.H>
#include "types.h"
#include "can.h"
#include "delay.h"
#include "defines.h"

#define LED     0       /* First LED bit position on Port 0 (P0.0)        */
#define RX_LED  21      /* Activity LED pin (P0.21)                        */

CANF rxf;               /* Received CAN frame                              */

s32 indicator_state = 0;    /* Current indicator command: 0=OFF, 1=LEFT, 2=RIGHT */
s32 prev_state      = 0;    /* Previous state — used to detect state changes    */
s32 pos             = 0;    /* Current LED position in the animation sequence   */

/**
 * @brief Indicator node main: receive CAN frames and drive LED animations.
 */
int main(void)
{
    can1_init();                            /* Initialise CAN1 peripheral          */

    /* Configure LED pins P0.0–P0.7 and activity LED P0.21 as outputs */
    IODIR0 |= (0xFF << LED) | (1 << RX_LED);

    IOSET0 = 0xFF << LED;                   /* All 8 indicator LEDs OFF at startup */

    while (1)
    {
        /* Non-blocking CAN receive — updates rxf if a frame is waiting */
        can1_rx(&rxf);
        if (rxf.ID == 2)
        {
            indicator_state = rxf.DATA1;    /* Extract indicator command from payload */
        }

        /* On state change: reset all LEDs and set animation start position */
        if (prev_state != indicator_state)
        {
            IOSET0 = 0xFF << LED;           /* Turn all indicator LEDs off            */

            if (indicator_state == 1)
            {
                pos = 0;                    /* LEFT animation starts at P0.0          */
            }
            else if (indicator_state == 2)
            {
                pos = 7;                    /* RIGHT animation starts at P0.7         */
            }

            prev_state = indicator_state;
        }

        /* --- LEFT Indicator: sweep P0.0 → P0.7, then reset --- */
        if (indicator_state == 1)
        {
            IOCLR0 = 1 << pos;             /* Turn on LED at current position (active-LOW) */
            delay_ms(200);                 /* Hold for 200 ms per step                     */

            if (pos == 7)
            {
                IOSET0 = 0xFF << LED;      /* End of sweep: turn all off and restart       */
                pos = 0;
            }
            else
            {
                pos++;                     /* Advance to next LED                          */
            }
        }
        /* --- RIGHT Indicator: sweep P0.7 → P0.0, then reset --- */
        else if (indicator_state == 2)
        {
            IOCLR0 = 1 << pos;            /* Turn on LED at current position (active-LOW)  */
            delay_ms(200);

            if (pos == 0)
            {
                IOSET0 = 0xFF << LED;     /* End of sweep: turn all off and restart        */
                pos = 7;
            }
            else
            {
                pos--;                    /* Step backwards toward P0.0                    */
            }
        }
        /* --- OFF: keep all LEDs off --- */
        else
        {
            IOSET0 = 0xFF << LED;         /* Ensure all indicator LEDs remain off          */
        }
    }
}
