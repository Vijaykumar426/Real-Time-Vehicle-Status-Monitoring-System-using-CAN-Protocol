/**
 * @file adc_node_tx.c
 * @brief ADC transmitter node — reads fuel level and broadcasts it over CAN.
 *
 * This is the main entry point for the Fuel Sensor Node (CAN TX node).
 *
 * Hardware:
 *   - Potentiometer (simulating fuel sensor) connected to AIN0 (P0.27).
 *   - CAN1 bus connected to the Dashboard Node.
 *   - LED on P0.21 toggles each transmission cycle for visual confirmation.
 *
 * CAN message:
 *   ID    = 1   (Fuel level message)
 *   DLC   = 1   (1 byte payload)
 *   DATA1 = fuel_per  (fuel percentage 0–100)
 *
 * ADC raw range: 80 (empty) – 950 (full), mapped linearly to 0–100%.
 */

#include <LPC21XX.H>
#include "can.h"
#include "adc.h"
#include "lcd.h"
#include "types.h"
#include "delay.h"

/* --- Globals --- */
CANF txf;               /* CAN frame used for all transmissions           */
u32  dval;              /* Raw 10-bit ADC result (0–1023)                 */
f32  eAR;               /* Equivalent analog voltage (0.0–3.3 V)         */
u32  fuel_per;          /* Calculated fuel percentage (0–100)             */
u32  min_val = 80;      /* ADC count corresponding to empty tank          */
u32  max_val = 950;     /* ADC count corresponding to full tank           */

#define LED 21          /* Activity LED on P0.21                          */

/**
 * @brief ADC node main: sample fuel sensor and transmit over CAN every 500 ms.
 */
int main(void)
{
    can1_init();            /* Initialise CAN1 peripheral                 */
    init_ADC();             /* Initialise ADC peripheral                  */

    /* Configure CAN frame header (constant for all transmissions) */
    txf.ID       = 1;       /* Message ID 1 = Fuel Level                  */
    txf.bfv.RTR  = 0;       /* Data frame (not a remote frame)            */
    txf.bfv.DLC  = 1;       /* 1 byte of payload                          */

    IODIR0 |= 1 << LED;     /* Configure LED pin as output                */

    while (1)
    {
        read_ADC(0, &dval, &eAR);   /* Sample AIN0 (fuel sensor)          */

        /* Map raw ADC value to 0–100% fuel level */
        if (dval <= min_val)
        {
            fuel_per = 0;           /* Below minimum → empty              */
        }
        else if (dval >= max_val)
        {
            fuel_per = 100;         /* Above maximum → full               */
        }
        else
        {
            /* Linear interpolation between min and max */
            fuel_per = ((dval - min_val) * 100) / (max_val - min_val);
        }

        txf.DATA1 = fuel_per;       /* Load fuel % into CAN payload       */
        can1_tx(txf);               /* Transmit frame on CAN1             */

        IOPIN0 ^= 1 << LED;         /* Toggle LED (activity indicator)    */
        delay_ms(500);              /* Wait 500 ms before next sample      */
    }
}
