/**
 * @file delay.c
 * @brief Busy-wait delay routines calibrated for a 12 MHz oscillator.
 *
 * Each function converts the requested time unit into raw clock cycles
 * and decrements a counter until it reaches zero.  These are blocking
 * delays — the CPU does no other work while waiting.
 */

#include "types.h"

/**
 * @brief Block for approximately `tdly` seconds.
 * @param tdly  Number of seconds to wait.
 *
 * Multiplies by 12,000,000 (cycles per second at 12 MHz).
 */
void delay_s(u32 tdly)
{
    tdly *= 12000000;   /* Convert seconds → clock cycles at 12 MHz */
    while (tdly--);     /* Decrement until zero (busy wait)          */
}

/**
 * @brief Block for approximately `tdly` milliseconds.
 * @param tdly  Number of milliseconds to wait.
 *
 * Multiplies by 12,000 (cycles per millisecond at 12 MHz).
 */
void delay_ms(u32 tdly)
{
    tdly *= 12000;      /* Convert milliseconds → clock cycles       */
    while (tdly--);     /* Decrement until zero (busy wait)          */
}

/**
 * @brief Block for approximately `tdly` microseconds.
 * @param tdly  Number of microseconds to wait.
 *
 * Multiplies by 12 (cycles per microsecond at 12 MHz).
 */
void delay_us(u32 tdly)
{
    tdly *= 12;         /* Convert microseconds → clock cycles       */
    while (tdly--);     /* Decrement until zero (busy wait)          */
}
