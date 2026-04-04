/**
 * @file lcd.h
 * @brief 16×2 LCD driver function declarations.
 *
 * Supports 8-bit parallel interface to an HD44780-compatible LCD
 * connected to the LPC21xx GPIO port.  See lcd.c for pin assignments.
 */

#include "types.h"

void initLCD(void);         /* Initialise LCD in 8-bit mode; clear display       */
void cmdLCD(u8);            /* Send a command byte (RS = 0)                      */
void charLCD(s8);           /* Display a single ASCII character (RS = 1)         */
void strLCD(s8 *);          /* Display a null-terminated string                  */
void intLCD(s32);           /* Display a signed decimal integer                  */
void floatLCD(f32);         /* Display a float to 3 decimal places               */
void writetoCGRAM(void);    /* Write custom character pattern to CGRAM slot 0    */
void hexLCD(u32);           /* Display an unsigned integer in hexadecimal        */
void octLCD(u32);           /* Display an unsigned integer in octal              */
