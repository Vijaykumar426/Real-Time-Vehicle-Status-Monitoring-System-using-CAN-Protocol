/**
 * @file lcd_defines.h
 * @brief LCD cursor position command constants.
 *
 * These values are passed directly to cmdLCD() to move the cursor
 * to the start of a specific line on a 16×2 character LCD.
 *
 * The HD44780 DDRAM address command = 0x80 | address.
 * Line 1 starts at address 0x00; Line 2 starts at address 0x40.
 */

#define GOTO_LINE_1_POS_0   0x80    /* Move cursor to Line 1, Column 0 */
#define GOTO_LINE_2_POS_0   0xC0    /* Move cursor to Line 2, Column 0 */
