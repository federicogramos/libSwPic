//==============================================================================
// Archivo: t0.c
// Autor: Federico Ramos
// Modificado: 2023-03-28
//
// En este archivo:
// - INCLUDE HEADERS
// - DEFINICION DE VARIABLES GLOBALES
// - DEFINICION DE FUNCIONES
//       o Funcio?=n: timer0Driver(char i)
//==============================================================================


//==============================================================================
// INCLUDE
#include <t0.h>
#include <t0_delays.h>//delay de timers por parte de usuario
//==============================================================================


//==============================================================================
// DEFINICION DE VARIABLES GLOBALES
t_t0 t0Mem[T0_CANT];
//==============================================================================


//==============================================================================
// Funcio?=n: t0Driver(char i)
//==============================================================================
void t0Driver(char i)
   {
   if(!t0Mem[i].pause && t0Mem[i].prescaler>0)
      {
      t0Mem[i].prescaler--;
      if(t0Mem[i].prescaler==0)
         {
         t0Mem[i].flag=1;
         if(t0Mem[i].loop) t0Mem[i].prescaler=t0DelayConstant[i];
         }
      }
   }
