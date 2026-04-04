/**
 * @file types.h
 * @brief Project-wide type aliases for fixed-width integer and float types.
 *
 * Wraps standard C types in short, readable names used throughout
 * the CAN dashboard project (LPC21xx ARM7 target).
 */

typedef unsigned char       u8;   /* Unsigned  8-bit integer  (0 .. 255)            */
typedef signed char         s8;   /* Signed    8-bit integer  (-128 .. 127)          */
typedef unsigned short int  u16;  /* Unsigned 16-bit integer  (0 .. 65535)           */
typedef signed int          s32;  /* Signed   32-bit integer  (-2^31 .. 2^31-1)      */
typedef unsigned int        u32;  /* Unsigned 32-bit integer  (0 .. 2^32-1)          */
typedef float               f32;  /* 32-bit single-precision floating point          */
typedef double              f64;  /* 64-bit double-precision floating point          */
