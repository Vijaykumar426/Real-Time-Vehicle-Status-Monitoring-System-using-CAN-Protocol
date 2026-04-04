/**
 * @file adc_defines.h
 * @brief LPC21xx ADC peripheral register bit definitions and clock configuration.
 *
 * Configures the ADC for a ≤4 MHz ADC clock derived from PCLK.
 * Pins P0.27–P0.30 are mapped to AIN0–AIN3 via PINSEL1.
 */

/* --- System clock chain (12 MHz crystal, PLL ×5, PCLK /4) --- */
#define FOSC    12000000            /* Crystal oscillator frequency: 12 MHz  */
#define CCLK    (FOSC * 5)          /* Core clock after PLL: 60 MHz          */
#define PCLK    (CCLK / 4)          /* Peripheral clock: 15 MHz              */
#define ADCCLK  3000000             /* Target ADC clock: 3 MHz (must be ≤4 MHz) */

/* Clock divider written to ADCR bits [15:8]: divides PCLK to get ADCCLK */
#define CLKDIV  ((PCLK / ADCCLK) - 1)

/* --- ADCR (ADC Control Register) bit positions --- */
#define CLKDIV_BITS_START   8   /* CLKDIV field starts at bit 8              */
#define PDN_BIT             21  /* Power-Down bit: 1 = ADC powered on        */
#define CONV_START_BIT      24  /* Start conversion bit: 1 = start now       */

/* --- ADDR (ADC Data Register) bit positions --- */
#define RESULT_BITS_START   6   /* 10-bit result occupies bits [15:6]        */
#define DONE_BIT            31  /* Conversion Done flag: 1 = result ready    */

/* --- PINSEL1 masks: configure GPIO pins as analog inputs --- */
#define AIN0_0_27   0x00400000  /* P0.27 → AIN0 */
#define AIN1_0_28   0x01000000  /* P0.28 → AIN1 */
#define AIN2_0_29   0x04000000  /* P0.29 → AIN2 */
#define AIN3_0_30   0x10000000  /* P0.30 → AIN3 */
