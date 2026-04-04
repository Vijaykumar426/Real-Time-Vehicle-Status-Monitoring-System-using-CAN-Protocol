/**
 * @file main_tx_rx.c
 * @brief Dashboard Node main — receives fuel level over CAN and drives the LCD.
 *
 * This is the central dashboard controller node.  It:
 *   1. Initialises all peripherals (CAN, LCD, external interrupts, I2C, MMA7660).
 *   2. Loops forever:
 *        a. Receives CAN frames and dispatches on message ID.
 *        b. Displays fuel level (ID=1) on the LCD.
 *        c. Displays indicator direction (updated by ISR via indicator_state).
 *        d. Reads the accelerometer and shows airbag ON/OFF status.
 *
 * CAN messages consumed:
 *   ID=1  DATA1 = fuel percentage (0–100), sent by the ADC node.
 *
 * CAN messages produced (via interrupt.c ISRs):
 *   ID=2  DATA1 = indicator_state (0=OFF, 1=LEFT, 2=RIGHT), sent on button press.
 *
 * LCD layout (20×4):
 *   Line 1 (0x84): "Dash Board"
 *   Line 2 (0xC0): "Fuel: XX%"
 *   Line 3 (0x94): "INDICATOR: <-LEFT / RIGHT-> / OFF"
 *   Line 4 (0xD4): "Air Bag: ON / OFF"
 */

#include <LPC21XX.H>
#include "can.h"
#include "lcd.h"
#include "i2c.h"
#include "MMA7660.h"
#include "MMA7660_defines.h"
#include "types.h"
#include "delay.h"
#include "interrupt.h"
#include "main_functions.h"

#define LED 21          /* Activity LED on P0.21 — toggles when fuel frame received */

CANF txf;               /* TX frame for indicator state (populated by ISRs)         */
CANF rxf;               /* RX frame buffer for incoming CAN messages                */

extern s32 indicator_state; /* Set by eint0_isr / eint2_isr in interrupt.c         */

/**
 * @brief Dashboard node entry point.
 *
 * Initialises all hardware, then enters a non-blocking polling loop
 * that updates each LCD section whenever new data arrives.
 */
int main(void)
{
    IODIR0 |= 1 << LED;    /* Configure activity LED pin as output             */

    can1_init();            /* Initialise CAN1 (125 kbps)                      */
    initLCD();              /* Initialise 16×2 / 20×4 LCD                      */
    init_ext_interrupt();   /* Configure EINT0 (left) and EINT2 (right) buttons */
    init_i2c();             /* Initialise I2C0 at 100 kHz                      */
    MMA7660_Init();         /* Initialise accelerometer (standby → active)      */

    /* Configure indicator TX frame header (payload set in ISRs) */
    txf.ID      = 2;        /* Message ID 2 = Indicator state                  */
    txf.bfv.RTR = 0;        /* Data frame                                      */
    txf.bfv.DLC = 1;        /* 1 byte payload                                  */

    /* Static LCD header on Line 1 */
    cmdLCD(0x84);            /* Cursor → Line 1, Column 4                      */
    strLCD("Dash Board");

    while (1)
    {
        can1_rx(&rxf);                      /* Non-blocking: check CAN RX buffer */

        if (rxf.ID == 1)
        {
            display_fuel(rxf.DATA1);        /* Update fuel level on LCD          */
            IOPIN0 ^= 1 << LED;            /* Toggle LED on each fuel update    */
        }

        display_indicator(indicator_state); /* Update indicator status on LCD    */
        trigger_airbag();                   /* Read accelerometer; update airbag */
    }
}
