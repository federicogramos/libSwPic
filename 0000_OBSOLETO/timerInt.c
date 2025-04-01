// timerInt.c
////////////////////////////////////////////////////////////////////////////////
#include <timerInt_lib.h>

// DEFINICION DE VARIABLES GLOBALES
t_timerInt timerIntMem[CANT_TIMERS_INT];
#include <timerInt_delays.h>//delay de timers por parte de usuario

void timerIntDriver(char i)
   {
   if(!timerIntMem[i].pause && timerIntMem[i].prescaler!=0 && --timerIntMem[i].prescaler==0)
         {
         timerIntMem[i].flag=1;
         if(timerIntMem[i].loop) timerIntMem[i].prescaler=timerIntDelayConstant[i];
         }
   }
