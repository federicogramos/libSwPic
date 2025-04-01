// timerLong_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __TIMER_LONG_LIB_H
#define __TIMER_LONG_LIB_H

// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timerLong_aliases.h>

// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   long prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   }t_timerLong;

// DECLARACIÓN DE VARIABLES
extern t_timerLong timerLongMem[CANT_TIMERS_LONG];//Siempre inicializado a cero, por global

extern long timerLongDelayConstant[CANT_TIMERS_LONG];

// MACROS
#define TMR_LONG_START(i) {                                           \
                     timerLongMem[i].flag=0;                         \
                     timerLongMem[i].prescaler=timerLongDelayConstant[i];\
                     }

#define TMR_LONG_INIT_LOOP(i) {                                           \
                         timerLongMem[i].flag=0;                         \
                         timerLongMem[i].loop=1;                         \
                         timerLongMem[i].prescaler=timerLongDelayConstant[i];\
                         }

#define TMR_LONG_TIMEOUT(i) (timerLongMem[i].flag?!(timerLongMem[i].flag=0):0)

#define TMR_LONG_RUNNING(i) (timerLongMem[i].prescaler!=0)
#define TMR_LONG_STOP(i) (timerLongMem[i].prescaler=0)

// DECLARACION DE FUNCIONES
void timerLongDriver(char i);

#endif//__TIMER_LIB_H