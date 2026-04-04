/*
 * File: adc.c
 * Description: ADC driver implementation for LPC21XX microcontroller.
 *              Provides initialization and reading of analog inputs (AIN0–AIN3)
 */

#include "types.h"
#include <LPC21XX.h>
#include "adc_defines.h"
#include "delay.h"

/*
 * Function: init_ADC
 * ------------------
 * Initializes ADC module.
 * Configures GPIO pins as analog inputs
 * and sets ADC clock & power.
 */
void init_ADC(void)
{
    // Configure P0.27–P0.30 as ADC input pins (AIN0–AIN3)
    //PINSEL1 &= ~(0xFF << 22);   // Optional: clear bits before setting
    PINSEL1 |= (AIN0_0_27) | (AIN1_0_28) | (AIN2_0_29) | (AIN3_0_30);

    // Configure ADC Control Register:
    // - Set clock divider
    // - Enable ADC (PDN bit)
    ADCR |= (CLKDIV << CLKDIV_BITS_START) | (1 << PDN_BIT);
}

/*
 * Function: read_ADC
 * ------------------
 * Reads ADC value from selected channel.
 *
 * Parameters:
 * chno  -> ADC channel number (0–3)
 * dval  -> Pointer to store digital value (0–1023)
 * eAR   -> Pointer to store equivalent analog voltage
 */
void read_ADC(u32 chno, u32 *dval, f32 *eAR)
{
    // Clear previously selected channel
    ADCR &= 0xFFFFFF00;

    // Select new channel and start conversion
    ADCR |= (1 << chno) | (1 << CONV_START_BIT);

    // Wait for minimum conversion time
    delay_us(3);

    // Wait until conversion is complete (DONE bit = 1)
    while (((ADDR >> DONE_BIT) & 1) == 0);

    // Stop ADC conversion
    ADCR &= ~(1 << CONV_START_BIT);

    // Extract 10-bit digital result
    *dval = (ADDR >> RESULT_BITS_START) & 1023;

    // Convert digital value to analog voltage (0–3.3V)
    *eAR = (*dval * (3.3 / 1023));
}
