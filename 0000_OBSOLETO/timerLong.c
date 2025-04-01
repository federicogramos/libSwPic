// timerLong.c
////////////////////////////////////////////////////////////////////////////////
#include <timerLong_lib.h>

// DEFINICION DE VARIABLES GLOBALES
t_timerLong timerLongMem[CANT_TIMERS_LONG];
#include <timerLong_delays.h>//delay de timers por parte de usuario

void timerLongDriver(char i)
   {
   if(timerLongMem[i].prescaler!=0 && --timerLongMem[i].prescaler==0)
         {
         timerLongMem[i].flag=1;
         if(timerLongMem[i].loop) timerLongMem[i].prescaler=timerLongDelayConstant[i];
         }
   }
