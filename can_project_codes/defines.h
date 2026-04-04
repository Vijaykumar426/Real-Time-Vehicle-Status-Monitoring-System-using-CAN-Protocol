/**
 * @file defines.h
 * @brief Bit and byte manipulation macros used across the project.
 *
 * All macros operate on a WORD (typically a 32-bit I/O register),
 * a Bit Position (BP / SBP), and an optional value.
 */

/* Set the bit at position BP in WORD to 1 */
#define SETBIT(WORD, BP)            WORD |= (1 << BP)

/* Clear the bit at position BP in WORD to 0 */
#define CLRBIT(WORD, BP)            WORD &= ~(1 << BP)

/* Toggle the bit at position BP in WORD */
#define CPLBIT(WORD, BP)            WORD ^= (1 << BP)

/* Write a single bit value BIT at position BP in WORD */
#define WRITEBIT(WORD, BP, BIT)     WORD = (WORD & (~(1 << BP))) | (BIT << BP)

/* Write a 4-bit NIBBLE starting at bit position SBP in WORD */
#define WRITENIBBLE(WORD, SBP, NIBBLE) \
    WORD = (WORD & ~(0xf << SBP)) | (NIBBLE << SBP)

/* Write an 8-bit BYTE starting at bit position SBP in WORD */
#define WRITEBYTE(WORD, SBP, BYTE) \
    WORD = (WORD & ~(0xff << SBP)) | (BYTE << SBP)
