// timerChar_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_CHAR_LIB_H
#define __TIMER_CHAR_LIB_H

// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timerChar_aliases.h>

// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   unsigned char prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   }t_timerChar;

// DECLARACIÓN DE VARIABLES
extern t_timerChar timerCharMem[CANT_TIMERS_CHAR];//Siempre inicializado a cero, por global

extern unsigned char timerCharDelayConstant[CANT_TIMERS_CHAR];

// MACROS
#define TMR_CHAR_START(i) {                                           \
                     timerCharMem[i].flag=0;                         \
                     timerCharMem[i].prescaler=timerCharDelayConstant[i];\
                     }

#define TMR_CHAR_INIT_LOOP(i) {                                           \
                         timerCharMem[i].flag=0;                         \
                         timerCharMem[i].loop=1;                         \
                         timerCharMem[i].prescaler=timerCharDelayConstant[i];\
                         }

#define TMR_CHAR_TIMEOUT(i) (timerCharMem[i].flag?!(timerCharMem[i].flag=0):0)

#define TMR_CHAR_RUNNING(i) (timerCharMem[i].prescaler!=0)
#define TMR_CHAR_STOP(i) (timerCharMem[i].prescaler=0)

// DECLARACION DE FUNCIONES
void timerCharDriver(char i);

#endif//__TIMER_CHAR_LIB_H