// timerInt_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_INT_LIB_H
#define __TIMER_INT_LIB_H

// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timerInt_aliases.h>

// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   int prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   unsigned char pause:1;//inhabilita decremento del contador
   }t_timerInt;

// DECLARACIÓN DE VARIABLES
extern t_timerInt timerIntMem[CANT_TIMERS_INT];//Siempre inicializado a cero, por global

extern int timerIntDelayConstant[CANT_TIMERS_INT];

// MACROS
#define TMR_INT_START(i) {                                             \
                     timerIntMem[i].flag=0;                            \
                     timerIntMem[i].pause=0;                           \
                     timerIntMem[i].prescaler=timerIntDelayConstant[i];\
                     }

#define TMR_INT_INIT_LOOP(i) {                                             \
                         timerIntMem[i].flag=0;                            \
                         timerIntMem[i].pause=0;                           \
                         timerIntMem[i].loop=1;                            \
                         timerIntMem[i].prescaler=timerIntDelayConstant[i];\
                         }

#define TMR_INT_TIMEOUT(i) (timerIntMem[i].flag?!(timerIntMem[i].flag=0):0)

#define TMR_INT_RUNNING(i) (!timerIntMem[i].pause && timerIntMem[i].prescaler!=0)
#define TMR_INT_PAUSED(i) (timerIntMem[i].pause)
#define TMR_INT_STOP(i) {                           \
                         timerIntMem[i].prescaler=0;\
                         timerIntMem[i].pause=0;    \
                         }
#define TMR_INT_PAUSE(i) (timerIntMem[i].pause=1)
#define TMR_INT_UNPAUSE(i) (timerIntMem[i].pause=0)
#define TMR_INT_STOPPED(i) (timerIntMem[i].prescaler==0 && !timerIntMem[i].flag)

// DECLARACION DE FUNCIONES
void timerIntDriver(char i);

#endif//__TIMER_LIB_H