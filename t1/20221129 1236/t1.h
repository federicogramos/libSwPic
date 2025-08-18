//==============================================================================
// Archivo: t1_lib.h
// Autor: Federico Ramos
// Modificado: 03-11-2023
//
// Timers por software.
//==============================================================================


#ifndef __T1_H
#define __T1_H


//******************************************************************************
// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS

#include <t1_setupUser.h>
#include <t1_aliases.h>

//******************************************************************************


//******************************************************************************
// ESTRUCTURA PARA CONTROL DE TIEMPO
// TO-DO: copiar las aclaraciones de T0.

typedef struct
   {
   type_t1Size prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   unsigned char pause:1;//inhabilita decremento del contador
   }t_t1;

//******************************************************************************



//******************************************************************************
// DECLARACI�N DE VARIABLES

extern t_t1 t1Mem[T1_CANT];//Siempre inicializado a cero, por global
extern type_t1DelayConstant t1DelayConstant[T1_CANT];

//******************************************************************************



//******************************************************************************
//
// MACROS
//
//******************************************************************************

#define T1_START(i)                              \
     {                                             \
     t1Mem[i].flag=0;                          \
     t1Mem[i].prescaler=t1DelayConstant[i];\
     t1Mem[i].pause=0;                         \
     }

#define T1_INIT_LOOP(i)                          \
     {                                             \
     t1Mem[i].flag=0;                          \
     t1Mem[i].prescaler=t1DelayConstant[i];\
     t1Mem[i].pause=0;                         \
     t1Mem[i].loop=1;                          \
     }

#define T1_TIMEOUT(i) (t1Mem[i].flag?!(t1Mem[i].flag=0):0)
#define T1_TIMEOUT_FORCE(i) (t1Mem[i].flag=1)

#define T1_RUNNING(i) (!t1Mem[i].pause && t1Mem[i].prescaler!=0)
#define T1_PAUSED(i) (t1Mem[i].pause)
#define T1_STOP(i) {                           \
                         t1Mem[i].prescaler=0;\
                         }
//se necesita porque si esta en loop, el stop comun no quita el loop, y si se hace TMR_START, va a empezar como loop, cuando la intencion no hubiera sido esa.
#define T1_STOP_LOOP(i) {                           \
                         t1Mem[i].prescaler=0;\
                         t1Mem[i].pause=1;    \
                         t1Mem[i].loop=0;                            \
                         }

#define T1_PAUSE(i) (t1Mem[i].pause=1)
#define T1_UNPAUSE(i) (t1Mem[i].pause=0)
#define T1_STOPPED(i) (t1Mem[i].prescaler==0 && !t1Mem[i].flag)



//******************************************************************************
// DECLARACION DE FUNCIONES

void t1Driver(char i);

//******************************************************************************

#endif// __T1_H