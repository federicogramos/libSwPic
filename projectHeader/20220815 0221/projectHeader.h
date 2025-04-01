//******************************************************************************
//
// Archivo: projectHeader.h
// Autor: Federico Ramos
// Modificado: 2023-04-18
//
// En este archivo:
// - INCLUDE HEADERS
// - MACROS DE MANEJO DE BITS
//
//******************************************************************************


#ifndef __PROJECT_HEADER_H
#define __PROJECT_HEADER_H


//******************************************************************************
// INCLUDE HEADERS
// Este include va adentro del .h, solo porque es un include que deben tener
// todos los archivos fuente.

#include <htc.h>

//******************************************************************************



//******************************************************************************
//
// MACROS DE MANEJO DE BITS
//
//******************************************************************************

#define GET_NUM_BYTE(n,x) ((unsigned char)((x>>(8*n))&0xFF))

#define BIT_SET(var,bitno) ((var) |= 1UL << (bitno))
#define BIT_CLR(var,bitno) ((var) &= ~(1UL << (bitno)))

// Retorna 0 o 1.
#define BIT_GETVAL(byte,bitno) !(((1UL<<(bitno)) & (byte))==0)

// Retorna 0 si el bit es 0, !0 en otro caso.
#define BIT_GETVAL_QUICK(byte,bitno) ((1UL<<(bitno)) & (byte))

#define HIGH_NIBBLE(x) ((unsigned char)(x>>4))
#define LOW_NIBBLE(x) ((unsigned char)(x & 0xFF))



#endif// __PROJECT_HEADER_H