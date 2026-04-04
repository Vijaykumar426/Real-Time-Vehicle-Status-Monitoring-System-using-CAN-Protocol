/**
 * @file lcd.c
 * @brief HD44780-compatible 16×2 LCD driver for LPC21xx (8-bit mode).
 *
 * Pin mapping (all on GPIO Port 0):
 *   P0.10–P0.17 → DB0–DB7  (8-bit data bus, LCD_data = 10)
 *   P0.18       → RS       (Register Select: 0 = command, 1 = data)
 *   P0.20       → RW       (Read/Write: always driven low → write only)
 *   P0.19       → EN       (Enable pulse triggers LCD latch)
 *
 * Supports: commands, single characters, strings, signed integers,
 *           floats, hex, octal, and custom CGRAM characters.
 */

#include <LPC21XX.h>
#include "delay.h"
#include "types.h"
#include "defines.h"
#include "lcd.h"

/* --- Pin assignments on IOPIN0 --- */
#define LCD_data    10      /* Data bus LSB starts at P0.10                  */
#define RS          18      /* Register Select pin (P0.18)                   */
#define RW          20      /* Read/Write pin (P0.20) — always written LOW   */
#define EN          19      /* Enable pin (P0.19) — high pulse latches data  */

/**
 * @brief Initialise the LCD in 8-bit mode with cursor blink.
 *
 * Follows the HD44780 power-on reset procedure:
 *  - Configure GPIO output pins.
 *  - Issue three Function Set commands with required delays.
 *  - Set 8-bit / 2-line / 5×8 mode, entry mode, and display on.
 */
void initLCD(void)
{
    /* Configure data bus + RS, RW, EN as outputs */
    IODIR0 |= 0xFF << LCD_data | (1 << RS) | (1 << RW) | (1 << EN);

    delay_ms(20);           /* Power-on delay: LCD needs >15 ms              */

    /* HD44780 initialisation sequence (three Function Set retries) */
    cmdLCD(0x30);  delay_ms(8);
    cmdLCD(0x30);  delay_ms(1);
    cmdLCD(0x30);  delay_ms(1);

    cmdLCD(0x38);           /* Function Set: 8-bit, 2 lines, 5×8 font       */
    cmdLCD(0x10);           /* Cursor/Display Shift: cursor move             */
    cmdLCD(0x01);           /* Clear Display                                 */
    cmdLCD(0x06);           /* Entry Mode: increment cursor, no display shift*/
    cmdLCD(0x0F);           /* Display ON, cursor ON, cursor blink ON        */
}

/**
 * @brief Low-level helper: write one byte to the LCD (command or data).
 * @param val  Byte to send; RS must already be set by the caller.
 *
 * Always drives RW LOW (write only). Pulses EN to latch the byte.
 */
void dispLCD(u8 val)
{
    IOCLR0 = 1 << RW;                   /* Drive RW LOW (write operation)    */
    WRITEBYTE(IOPIN0, LCD_data, val);    /* Place byte on data bus pins       */
    IOSET0 = 1 << EN;                   /* EN HIGH — start enable pulse      */
    delay_us(2);                         /* EN pulse width ≥450 ns            */
    IOCLR0 = 1 << EN;                   /* EN LOW  — LCD latches on falling  */
    delay_ms(2);                         /* Execution time for most commands  */
}

/**
 * @brief Send a command byte to the LCD (RS = 0).
 * @param cmd  HD44780 command (e.g. 0x01 = clear, 0x80|addr = set cursor).
 */
void cmdLCD(u8 cmd)
{
    IOCLR0 = 1 << RS;   /* RS = 0 → command register */
    dispLCD(cmd);
}

/**
 * @brief Display a single ASCII character on the LCD (RS = 1).
 * @param data  Character to display.
 */
void charLCD(s8 data)
{
    IOSET0 = 1 << RS;   /* RS = 1 → data register    */
    dispLCD(data);
}

/**
 * @brief Display a null-terminated string on the LCD.
 * @param ptr  Pointer to the string to display.
 *
 * Advances the cursor automatically as each character is written.
 */
void strLCD(s8 *ptr)
{
    while (*ptr != '\0')    /* Loop until end of string  */
    {
        charLCD(*ptr);      /* Write current character   */
        ptr++;              /* Advance to next character */
    }
}

/**
 * @brief Display a signed 32-bit integer in decimal on the LCD.
 * @param num  Integer to display (handles 0, positive, and negative).
 *
 * Digits are extracted in reverse order into a buffer, then displayed
 * forwards.  A leading '-' is shown for negative values.
 */
void intLCD(s32 num)
{
    s8  a[10];      /* Digit buffer (enough for 32-bit int) */
    s32 i = 0;

    if (num == 0)
    {
        charLCD('0');   /* Special case: output single '0' */
        return;
    }

    if (num < 0)
    {
        charLCD('-');   /* Output negative sign then negate */
        num = -num;
    }

    while (num)
    {
        a[i++] = num % 10 + '0';   /* Extract digit, convert to ASCII  */
        num /= 10;
    }

    for (--i; i >= 0; i--)
    {
        charLCD(a[i]);              /* Output digits most-significant first */
    }
}

/**
 * @brief Display a 32-bit float to 3 decimal places on the LCD.
 * @param num  Float value to display.
 *
 * Outputs the integer part via intLCD(), then a '.', then 3 fractional digits.
 */
void floatLCD(f32 num)
{
    u32 n;
    s32 i;

    if (num < 0)
    {
        charLCD('-');   /* Negative sign                  */
        num = -num;
    }

    n = (u32)num;       /* Truncate to integer part       */
    intLCD(n);          /* Display integer part           */
    charLCD('.');       /* Decimal separator              */

    for (i = 0; i < 3; i++)
    {
        num = (num - n) * 10;   /* Shift one fractional digit left */
        n   = (u32)num;
        charLCD(n + '0');       /* Display fractional digit        */
    }
}

/**
 * @brief Write a custom 5×8 character pattern to CGRAM slot 0.
 *
 * The pattern array defines 8 rows of 5 pixels (right-aligned in 8 bits).
 * After writing, display the custom char with charLCD(0x00).
 */
void writetoCGRAM(void)
{
    /* 8-row bitmap for a custom character (example: fuel-pump icon) */
    s8 i;
    s8 a[] = {0x17, 0x14, 0x14, 0x1F, 0x05, 0x05, 0x1D, 0x00};

    cmdLCD(0x60);               /* Set CGRAM address to slot 0 (0x40 | 0×20) */
    for (i = 0; i < 8; i++)
    {
        charLCD(a[i]);          /* Write each row of the character bitmap     */
    }
}

/**
 * @brief Display an unsigned 32-bit integer in hexadecimal on the LCD.
 * @param num  Value to display (e.g. 255 → "FF").
 */
void hexLCD(u32 num)
{
    u8  a[10];
    s32 i = 0, nibble;

    if (num == 0) { charLCD('0'); return; }

    while (num != 0)
    {
        nibble = num % 16;
        /* Convert nibble: 0-9 → '0'-'9', 10-15 → 'A'-'F' */
        a[i++] = (nibble > 9) ? (nibble - 10) + 'A' : nibble + '0';
        num   /= 16;
    }

    for (--i; i >= 0; i--)
    {
        charLCD(a[i]);  /* Output most-significant nibble first */
    }
}

/**
 * @brief Display an unsigned 32-bit integer in octal on the LCD.
 * @param num  Value to display (e.g. 8 → "10").
 */
void octLCD(u32 num)
{
    s32 i = 0;
    u8  a[10];

    if (num == 0) { charLCD('0'); return; }

    while (num != 0)
    {
        a[i++] = num % 8 + '0';    /* Extract octal digit, convert to ASCII */
        num   /= 8;
    }

    for (--i; i >= 0; i--)
    {
        charLCD(a[i]);  /* Output most-significant digit first */
    }
}
