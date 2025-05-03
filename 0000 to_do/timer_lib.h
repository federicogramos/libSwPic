//******************************************************************************
// ARCHIVO: timer_lib.h
//******************************************************************************


#ifndef __TIMER_LIB_H
#define __TIMER_LIB_H


//******************************************************************************
// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timer_user_settings.h>
#include <timer_aliases.h>
//******************************************************************************


//******************************************************************************
// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   type_timerSize prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   unsigned char pause:1;//inhabilita decremento del contador
   }t_timer;
//******************************************************************************


//******************************************************************************
// DECLARACIÓN DE VARIABLES
extern t_timer timerMem[CANT_TIMERS];//Siempre inicializado a cero, por global
extern type_timerSize timerDelayConstant[CANT_TIMERS];
//******************************************************************************


//******************************************************************************
// MACROS
#define TMR_START(i) {                                           \
                     timerMem[i].flag=0;                         \
                     timerMem[i].prescaler=timerDelayConstant[i];\
                     timerMem[i].pause=0;                        \
                     }

#define TMR_INIT_LOOP(i) {                                             \
                         timerMem[i].flag=0;                            \
                         timerMem[i].prescaler=timerDelayConstant[i];\
                         timerMem[i].pause=0;                           \
                         timerMem[i].loop=1;                            \
                         }

#define TMR_TIMEOUT(i) (timerMem[i].flag?!(timerMem[i].flag=0):0)

#define TMR_RUNNING(i) (!timerMem[i].pause && timerMem[i].prescaler!=0)
#define TMR_PAUSED(i) (timerMem[i].pause)
#define TMR_STOP(i) {                           \
                         timerMem[i].prescaler=0;\
                         }
//se necesita porque si esta en loop, el stop comun no quita el loop, y si se hace TMR_START, va a empezar como loop, cuando la intencion no hubiera sido esa.
#define TMR_STOP_LOOP(i) {                           \
                         timerMem[i].prescaler=0;\
                         timerMem[i].pause=1;    \
                         timerMem[i].loop=0;                            \
                         }

#define TMR_PAUSE(i) (timerMem[i].pause=1)
#define TMR_UNPAUSE(i) (timerMem[i].pause=0)
#define TMR_STOPPED(i) (timerMem[i].prescaler==0 && !timerMem[i].flag)


//******************************************************************************
// DECLARACION DE FUNCIONES
void timerDriver(char i);
//******************************************************************************


#endif//__TIMER_LIB_H