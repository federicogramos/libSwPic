//******************************************************************************
// ARCHIVO: timer.c
// AUTOR: Federico Ramos
// ÚLT. MODIF:  08-11-2021 1652
//******************************************************************************


//******************************************************************************
// ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS
#include <timer_lib.h>
//******************************************************************************


//******************************************************************************
// DEFINICION DE VARIABLES GLOBALES
t_timer timerMem[CANT_TIMERS];

#include <timer_delays.h>//delay de timers por parte de usuario

void timerDriver(char i)
   {

   if(!timerMem[i].pause && timerMem[i].prescaler>0)
      {
      timerMem[i].prescaler--;
      if(timerMem[i].prescaler==0)
         {
         timerMem[i].flag=1;
         if(timerMem[i].loop) timerMem[i].prescaler=timerDelayConstant[i];
         }
      }
   }
