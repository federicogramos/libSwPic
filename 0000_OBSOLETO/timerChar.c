// timerChar.c
////////////////////////////////////////////////////////////////////////////////
#include <timerChar_lib.h>

// DEFINICION DE VARIABLES GLOBALES
t_timerChar timerCharMem[CANT_TIMERS_CHAR];
#include <timerChar_delays.h>//delay de timers por parte de usuario

void timerCharDriver(char i)
   {
   if(timerCharMem[i].prescaler!=0 && --timerCharMem[i].prescaler==0)
         {
         timerCharMem[i].flag=1;
         if(timerCharMem[i].loop) timerCharMem[i].prescaler=timerCharDelayConstant[i];
         }
   }
