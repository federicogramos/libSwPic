// timerShortLong_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_SHORTLONG_LIB_H
#define __TIMER_SHORTLONG_LIB_H

// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timerShortLong_aliases.h>

// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   short long prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   }t_timerShortLong;

// DECLARACIÓN DE VARIABLES
extern t_timerShortLong timerShortLongMem[CANT_TIMERS_SHORTLONG];//Siempre inicializado a cero, por global

extern short long timerShortLongDelayConstant[CANT_TIMERS_SHORTLONG];

// MACROS
#define TMR_SHORTLONG_START(i) {                                           \
                     timerShortLongMem[i].flag=0;                         \
                     timerShortLongMem[i].prescaler=timerShortLongDelayConstant[i];\
                     }

#define TMR_SHORTLONG_INIT_LOOP(i) {                                           \
                         timerShortLongMem[i].flag=0;                         \
                         timerShortLongMem[i].loop=1;                         \
                         timerShortLongMem[i].prescaler=timerShortLongDelayConstant[i];\
                         }

#define TMR_SHORTLONG_TIMEOUT(i) (timerShortLongMem[i].flag?!(timerShortLongMem[i].flag=0):0)

#define TMR_SHORTLONG_RUNNING(i) (timerShortLongMem[i].prescaler!=0)
#define TMR_SHORTLONG_STOP(i) (timerShortLongMem[i].prescaler=0)

// DECLARACION DE FUNCIONES
void timerShortLongDriver(char i);

#endif//__TIMER_LIB_H