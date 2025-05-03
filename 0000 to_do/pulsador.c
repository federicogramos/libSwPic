// pulsadorPin.c                                                                      //
////////////////////////////////////////////////////////////////////////////////
#include <projectHeader.h>
#include <pulsador_lib.h>

// DEFINICION DE VARIABLES GLOBALES
t_pulsEvent pulsBuffer;
#include <pulsador_pindef.h>

void pulsPinDriver(void)
   {
   char i;

   for(i=0;i<CANT_PULS;i++)
      {
      pulsPin[i].state=BIT_GETVAL_PULS(*(pulsPin[i].p2port),pulsPin[i].bitNum);
      if(pulsPin[i].timer) pulsPin[i].timer--;
      else
         {
         if(pulsPin[i].event_on_push)
            {
            if(pulsPin[i].state==0 && pulsPin[i].prevState==1)
               {
               pulsPin[i].timer=PULS_N_ANTIREBOTE;
               pulsBuffer.pulsId=i;
               pulsBuffer.flag=1;
               }
            if(pulsPin[i].state==1 && pulsPin[i].prevState==0)
               {
               pulsPin[i].timer=PULS_N_ANTIREBOTE;
               }
            }
         else
            {
            if(pulsPin[i].state==1 && pulsPin[i].prevState==0)
               {
               pulsPin[i].timer=PULS_N_ANTIREBOTE;
               pulsBuffer.pulsId=i;
               pulsBuffer.flag=1;
               }
            if(pulsPin[i].state==0 && pulsPin[i].prevState==1)
               {
               pulsPin[i].timer=PULS_N_ANTIREBOTE;
               }
            }
         pulsPin[i].prevState=pulsPin[i].state;
         }
      }
   }
