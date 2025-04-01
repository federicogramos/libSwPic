// timerShortLong.c
////////////////////////////////////////////////////////////////////////////////
#include <timerShortLong_lib.h>

// DEFINICION DE VARIABLES GLOBALES
t_timerShortLong timerShortLongMem[CANT_TIMERS_SHORTLONG];
#include <timerShortLong_delays.h>//delay de timers por parte de usuario

void timerShortLongDriver(char i)
   {
   if(timerShortLongMem[i].prescaler!=0 && --timerShortLongMem[i].prescaler==0)

         {
         timerShortLongMem[i].flag=1;
         if(timerShortLongMem[i].loop) timerShortLongMem[i].prescaler=timerShortLongDelayConstant[i];
         }
   }
