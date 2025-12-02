/*******************************************************************************
 * @file project.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250804 2053
 * @note Para pic12f, pic16f y pic18f.
 * 
 * En este archivo:
 * -- Include de htc.h para que por defecto esté incluido en todos los fuentes p
 *    orque contiene definiciones del hardware del uc.
 * -- Macros de manejo de bits.
 ******************************************************************************/


#ifndef __PROJECT_H
#define __PROJECT_H


#include <htc.h> // Debe ser incluido en todos los archivos fuente del proyecto.


/*******************************************************************************
 * Macros
 ******************************************************************************/


/*******************************************************************************
 * @brief  A macro to get byte <n> from number <x>.
 *
 * @param n: byte to pick [byte3 | byte2 | byte1 | byte0 ].
 * @param x: the input number.
 * @return Selected byte.
 * @warning Replaces 2 legacy macros: HIGH_BYTE(x) and LOW_BYTE(x).
 ******************************************************************************/

 #define GET_NUM_BYTE(n, x) ((unsigned char)((x >> (8 * n)) & 0xFF))


#define BIT_SET(var, bitno) ((var) |= 1UL << (bitno))


#define BIT_CLR(var, bitno) ((var) &= ~(1UL << (bitno)))


/*******************************************************************************
 * @brief  A macro to get bit <bitno> from byte <byte>.
 *
 * @param byte.
 * @param bitno.
 * @return 0 o 1.
 ******************************************************************************/

 #define BIT_GETVAL(byte, bitno) !(((1UL << (bitno)) & (byte)) == 0)


/*******************************************************************************
 * @brief  A macro to get bit <bitno> from byte <byte>.
 *
 * @param byte.
 * @param bitno.
 * @return 0 si el bit es 0, !0 en otro caso.
 ******************************************************************************/

 #define BIT_GETVAL_QUICK(byte, bitno) ((1UL << (bitno)) & (byte))


/*******************************************************************************
 * @brief  Para escribir una constante del tipo byte, pero estableciendo bit por
 *  bit.
 *
 * @param bi donde i = 7..0.
 * @return byte: donde el mismo fue armado bit por bit usando los bi.
 ******************************************************************************/

 #define BIT_BY_BIT_BYTE(b7, b6, b5, b4, b3, b2, b1, b0) (                     \
    b0 * 1UL << 0 |                                                            \
    b1 * 1UL << 1 |                                                            \
    b2 * 1UL << 2 |                                                            \
    b3 * 1UL << 3 |                                                            \
    b4 * 1UL << 4 |                                                            \
    b5 * 1UL << 5 |                                                            \
    b6 * 1UL << 6 |                                                            \
    b7 * 1UL << 7                                                              \
    )


#define HIGH_NIBBLE(x) ((unsigned char)(x >> 4))


#define LOW_NIBBLE(x) ((unsigned char)(x & 0xFF))


#endif// __PROJECT_H