/**
 * @file delay.h
 * @brief Busy-wait delay function declarations.
 *
 * All delays are software loops calibrated for a 12 MHz crystal.
 */

#include "types.h"

void delay_s(u32);    /* Blocking delay — full seconds              */
void delay_ms(u32);   /* Blocking delay — milliseconds              */
void delay_us(u32);   /* Blocking delay — microseconds              */
