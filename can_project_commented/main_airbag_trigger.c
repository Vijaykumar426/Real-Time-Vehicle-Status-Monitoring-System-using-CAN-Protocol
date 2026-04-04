/**
 * @file main_airbag_trigger.c
 * @brief Airbag trigger logic using the MMA7660 accelerometer.
 *
 * Reads all three acceleration axes and compares them against a
 * ±30 threshold.  If any axis exceeds the threshold (indicating a
 * significant impact), "Air Bag: ON" is shown on the LCD for 1 second;
 * otherwise "Air Bag: OFF" is displayed.
 *
 * This function is called repeatedly from the dashboard main loop.
 *
 * Threshold rationale:
 *   MMA7660 full-scale = ±1.5 g mapped to ±32 counts.
 *   30 counts ≈ 1.4 g — a conservative impact detection level.
 */

#include "MMA7660.h"
#include "lcd.h"
#include "delay.h"

/* Axis reading variables (signed 8-bit, range -32 .. +31) */
s8 x, y, z;

/**
 * @brief Read accelerometer axes and update the LCD airbag status.
 *
 * Called from the main loop — non-blocking except when airbag is ON
 * (holds display for 1 second to ensure the alert is visible).
 *
 * LCD position 0xD4 = Line 4, Column 0 on a 20×4 display.
 */
void trigger_airbag(void)
{
    cmdLCD(0xD4);               /* Position cursor: Line 4, Column 0      */
    strLCD("Air Bag:");         /* Static label                            */

    x = mma7660_get_X();        /* Read X-axis acceleration                */
    y = mma7660_get_Y();        /* Read Y-axis acceleration                */
    z = mma7660_get_Z();        /* Read Z-axis acceleration                */

    /* Trigger if any axis magnitude exceeds ±30 (≈ ±1.4 g impact) */
    if ((x >= 30 || x <= -30) ||
        (y >= 30 || y <= -30) ||
        (z >= 30 || z <= -30))
    {
        strLCD("ON ");           /* Display airbag ON alert                */
        delay_s(1);             /* Hold display for 1 s so alert is visible */
    }
    else
    {
        strLCD("OFF");          /* Normal: no significant impact detected   */
    }
}
