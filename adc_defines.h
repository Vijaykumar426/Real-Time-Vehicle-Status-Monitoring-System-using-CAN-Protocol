/*
 * File: adc_defines.h
 * Description: Contains macro definitions for ADC configuration
 *              including clock settings, register bit positions,
 *              and pin configuration for LPC21XX.
 */

// Available crystal frequency (12 MHz)
#define FOSC    12000000

// CPU clock (CCLK = FOSC × PLL multiplier)
#define CCLK    (FOSC * 5)

// Peripheral clock (PCLK = CCLK / 4)
#define PCLK    (CCLK / 4)

// ADC clock (must be ≤ 4 MHz as per datasheet)
#define ADCCLK  3000000

// Clock divider value for ADC
#define CLKDIV  ((PCLK / ADCCLK) - 1)


// -------- ADCR Register Bit Definitions --------

// Starting bit position for clock divider
#define CLKDIV_BITS_START 8 

// Power-down bit (1 = ADC enabled)
#define PDN_BIT           21

// Start conversion bit
#define CONV_START_BIT    24


// -------- ADDR Register Bit Definitions --------

// Starting bit position of ADC result (10-bit result)
#define RESULT_BITS_START 6

// Conversion done status bit
#define DONE_BIT          31


// -------- PINSEL1 Register Definitions --------
// Configure P0.27–P0.30 as ADC inputs (AIN0–AIN3)

#define AIN0_0_27 0x00400000  // P0.27 → AIN0
#define AIN1_0_28 0x01000000  // P0.28 → AIN1
#define AIN2_0_29 0x04000000  // P0.29 → AIN2
#define AIN3_0_30 0x10000000  // P0.30 → AIN3
