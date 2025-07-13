//==============================================================================
// Archivo: t0.h
// Autor: Federico Ramos
// Modificado: 03-11-2023
//
// En este archivo:
// - NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
// - ESTRUCTURA PARA CONTROL DE TIEMPO
// - DECLARACIÓN DE VARIABLES
// - MACROS
// - DECLARACION DE FUNCIONES
//==============================================================================


#ifndef __T0_H
#define __T0_H


//==============================================================================
// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <t0_setupUser.h>
#include <t0_aliases.h>
//==============================================================================


//==============================================================================
// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   type_t0Size prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   unsigned char pause:1;//inhabilita decremento del contador
   }t_t0;
//==============================================================================


//==============================================================================
// DECLARACIÓN DE VARIABLES
extern t_t0 t0Mem[T0_CANT];//Siempre inicializado a cero, por global
extern type_t0DelayConstant t0DelayConstant[T0_CANT];
//==============================================================================


//==============================================================================
// MACROS
//==============================================================================
#define T0_START(i) {                                           \
                     t0Mem[i].flag=0;                         \
                     t0Mem[i].prescaler=t0DelayConstant[i];\
                     t0Mem[i].pause=0;                        \
                     }

#define T0_INIT_LOOP(i) {                                             \
                         t0Mem[i].flag=0;                            \
                         t0Mem[i].prescaler=t0DelayConstant[i];\
                         t0Mem[i].pause=0;                           \
                         t0Mem[i].loop=1;                            \
                         }

#define T0_TIMEOUT(i) (t0Mem[i].flag?!(t0Mem[i].flag=0):0)
#define T0_TIMEOUT_FORCE(i) (t0Mem[i].flag=1)

#define T0_RUNNING(i) (!t0Mem[i].pause && t0Mem[i].prescaler!=0)
#define T0_PAUSED(i) (t0Mem[i].pause)
#define T0_STOP(i) {                           \
                         t0Mem[i].prescaler=0;\
                         }
//se necesita porque si esta en loop, el stop comun no quita el loop, y si se hace TMR_START, va a empezar como loop, cuando la intencion no hubiera sido esa.
#define T0_STOP_LOOP(i) {                           \
                         t0Mem[i].prescaler=0;\
                         t0Mem[i].pause=1;    \
                         t0Mem[i].loop=0;                            \
                         }

#define T0_PAUSE(i) (t0Mem[i].pause=1)
#define T0_UNPAUSE(i) (t0Mem[i].pause=0)
#define T0_STOPPED(i) (t0Mem[i].prescaler==0 && !t0Mem[i].flag)


//==============================================================================
// DECLARACION DE FUNCIONES
void t0Driver(char i);
//==============================================================================


#endif//__T0_H