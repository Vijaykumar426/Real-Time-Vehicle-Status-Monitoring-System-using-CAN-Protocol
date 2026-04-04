/**
 * @file main_functions.h
 * @brief Dashboard LCD display helper function declarations.
 *
 * These helpers are called from the dashboard main loop to update
 * specific regions of the 20×4 (or 16×2) LCD with live data.
 */

#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "types.h"

/* Display fuel level as a percentage on LCD Line 2 ("Fuel: XX%") */
void display_fuel(u8 fuel);

/* Display indicator state on LCD Line 3 ("INDICATOR: <-LEFT / RIGHT-> / OFF") */
void display_indicator(u8 state);

/* Display accelerometer value on LCD (reserved for future use) */
void display_accel(u16 val);

#endif /* _DISPLAY_H_ */
