/*
 * File: adc.h
 * Description: Header file for ADC driver.
 *              Contains function declarations for ADC initialization
 *              and reading analog values.
 */

#include "types.h"

/*
 * Function: init_ADC
 * ------------------
 * Initializes ADC module.
 */
void init_ADC(void);

/*
 * Function: read_ADC
 * ------------------
 * Reads ADC value from selected channel.
 *
 * Parameters:
 * chno  -> ADC channel number
 * dval  -> Pointer to store digital value
 * eAR   -> Pointer to store analog voltage
 */
void read_ADC(u32 chno, u32 *dval, f32 *eAR);
