//******************************************************************************
// ARCHIVO: timerEeprom.c
//******************************************************************************

//******************************************************************************
// INCLUDES
#include <timerEeprom_lib.h>
//******************************************************************************
#include <projectHeader.h>
//#include <eeprom_16f_lib.h>



//******************************************************************************
// DEFINICION DE VARIABLES GLOBALES
t_timerEeprom timerEepromMem[CANT_TIMERS_EEPROM];

#include <timerEeprom_delays.h>//delay de timers por parte de usuario

void timerEepromDriver(char i)
   {

   if(!timerEepromMem[i].pause && timerEepromMem[i].prescaler>0)
      {
      timerEepromMem[i].prescaler--;
      if(timerEepromMem[i].prescaler==0)
         {
         timerEepromMem[i].flag=1;
         if(timerEepromMem[i].loop)
            //EEPROM_READ_SHORTLONG_INT(timerEepromDelayConstantAddress[i],timerEepromMem[i].prescaler);

              {                           
              timerEepromMem[i].prescaler=0x0000L;                          
              timerEepromMem[i].prescaler|=(long)eeprom_read(timerEepromDelayConstantAddress[i]+0)<<(8*2);
              timerEepromMem[i].prescaler|=(long)eeprom_read(timerEepromDelayConstantAddress[i]+1)<<(8*1);
              timerEepromMem[i].prescaler|=(long)eeprom_read(timerEepromDelayConstantAddress[i]+2)<<(8*0);
              }

            //timerEepromMem[i].prescaler=timerEepromDelayConstant[i];
         }
      }
   }
