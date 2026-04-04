/**
 * @file main_functions.c
 * @brief LCD display helpers for the dashboard (receiver) node.
 *
 * Each function positions the cursor to a fixed LCD region and
 * overwrites it with fresh data, keeping the display layout stable.
 */

#include "lcd.h"
#include "types.h"

/**
 * @brief Show fuel level percentage on the LCD.
 * @param fuel  Fuel percentage (0–100) received via CAN from the ADC node.
 *
 * Moves cursor to Line 2, Column 0 (0xC0) and writes "Fuel: XX%".
 * Trailing spaces overwrite any leftover digits from a previous value.
 */
void display_fuel(s32 fuel)
{
    cmdLCD(0xC0);           /* Cursor → Line 2, Column 0             */
    strLCD("Fuel:");        /* Label                                  */
    intLCD(fuel);           /* Numeric value (0–100)                  */
    strLCD("%  ");          /* Unit + spaces to clear trailing digits */
}

/**
 * @brief Show indicator direction on the LCD.
 * @param state  Indicator state: 0 = OFF, 1 = LEFT, 2 = RIGHT.
 *
 * Moves cursor to Line 3 (0x94 on a 20×4 LCD) and writes the state string.
 * Fixed-width strings keep column alignment consistent.
 */
void display_indicator(s32 state)
{
    cmdLCD(0x94);               /* Cursor → Line 3, Column 0          */
    strLCD("INDICATOR:");       /* Label                               */

    if (state == 1)
    {
        strLCD("<-LEFT  ");     /* Left indicator active               */
    }
    else if (state == 2)
    {
        strLCD("RIGHT->  ");    /* Right indicator active              */
    }
    else
    {
        strLCD("OFF      ");    /* Both indicators off                 */
    }
}
