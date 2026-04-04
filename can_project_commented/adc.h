/**
 * @file adc.h
 * @brief LPC21xx ADC driver function declarations.
 *
 * Provides initialisation and single-channel conversion for the
 * on-chip 10-bit ADC.  Results are returned as both a raw count
 * and a voltage in the range 0.0 – 3.3 V.
 */

#include "types.h"

/* Initialise ADC peripheral: configure pins and power on the ADC */
void init_ADC(void);

/**
 * Read one ADC channel.
 * @param chno   Channel number (0–3 for AIN0–AIN3).
 * @param dval   Output: 10-bit digital result (0–1023).
 * @param eAR    Output: equivalent voltage in volts (0.0–3.3 V).
 */
void read_ADC(u32 chno, u32 *dval, f32 *eAR);
