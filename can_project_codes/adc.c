/**
 * @file adc.c
 * @brief LPC21xx on-chip 10-bit ADC driver — init and single-shot conversion.
 *
 * Supports channels AIN0–AIN3 on pins P0.27–P0.30.
 * ADC clock is derived from PCLK and must be ≤4 MHz (see adc_defines.h).
 */

#include "types.h"
#include <LPC21XX.h>
#include "adc_defines.h"
#include "delay.h"

/**
 * @brief Initialise the ADC peripheral.
 *
 * 1. Configures P0.27–P0.30 as AIN0–AIN3 via PINSEL1.
 * 2. Sets the ADC clock divider (CLKDIV) in ADCR.
 * 3. Powers on the ADC (PDN bit).
 */
void init_ADC(void)
{
    /* Select AIN0–AIN3 alternate functions on P0.27–P0.30 */
    PINSEL1 |= (AIN0_0_27) | (AIN1_0_28) | (AIN2_0_29) | (AIN3_0_30);

    /* Set clock divider and power on the ADC */
    ADCR |= (CLKDIV << CLKDIV_BITS_START) | (1 << PDN_BIT);
}

/**
 * @brief Perform a single-shot ADC conversion on the specified channel.
 * @param chno  Channel number to sample (0 = AIN0 … 3 = AIN3).
 * @param dval  Output: raw 10-bit digital result (0–1023).
 * @param eAR   Output: equivalent analog voltage in volts (0.0–3.3 V).
 *
 * Steps:
 *  1. Clear the channel-select bits from any previous conversion.
 *  2. Select the new channel and start conversion.
 *  3. Wait ≥2.44 µs for the sample-and-hold to complete.
 *  4. Poll DONE bit until conversion finishes.
 *  5. Stop conversion, read 10-bit result, convert to voltage.
 */
void read_ADC(u32 chno, u32 *dval, f32 *eAR)
{
    ADCR &= 0xFFFFFF00;                         /* Clear previous channel selection    */

    /* Select channel and start conversion (START bit = 1 → start immediately) */
    ADCR |= (1 << chno) | (1 << CONV_START_BIT);

    delay_us(3);                                 /* Wait ≥2.44 µs sample time          */

    while (((ADDR >> DONE_BIT) & 1) == 0);       /* Poll: wait until DONE = 1          */

    ADCR &= ~(1 << CONV_START_BIT);             /* Stop conversion                    */

    *dval = (ADDR >> RESULT_BITS_START) & 1023;  /* Extract 10-bit result (bits 15:6)  */

    *eAR  = (*dval * (3.3f / 1023));             /* Convert count → voltage (0–3.3 V)  */
}
