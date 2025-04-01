// pulsadorPin.c

#include <projectHeader.h>
#include <pulsadorPin_lib_1ms.h>

// DEFINICION DE VARIABLES GLOBALES
t_pulsEvent pulsPinBuffer;// PulsPin: los pines tocados se identifican de 1..N porque el 0 se reserva para indicar "ninguno ha sido presionado"
#include <pulsadorPin_1ms_pindef.h>

// Chequea por eventos en todos los pulsadores y los carga en el buffer.
// Para recoger los mensajes usar fgetc().
// Para ejecutar con periodo de 0.075s
void pulsPinDriver(void)
   {
   char i,j;

   for(i=0;i<PULS_PIN_CANT;i++)
      {
      pulsPin[i].state=BIT_GETVAL(*(pulsPin[i].p2port),pulsPin[i].bitNum);
      if(pulsPin[i].state!=pulsPin[i].prevState)
         {
         if(pulsPin[i].fp && pulsPin[i].state==1 && pulsPin[i].prevState==0)
            {
            if(pulsPin[i].timer)
               if(pulsPin[i].unbounceRst)
                  pulsPin[i].timer=PULS_PIN_N_ANTIREBOTE;
               else
                  pulsPin[i].timer--;
            else
               {
               pulsPin[i].timer=PULS_PIN_N_ANTIREBOTE;
               pulsPinBuffer.pulsId=i;
               pulsPinBuffer.flag=1;
               pulsPinBuffer.fp=1;
               }
            }
         if(pulsPin[i].fn && pulsPin[i].state==0 && pulsPin[i].prevState==1)
            {
            if(pulsPin[i].timer)
               if(pulsPin[i].unbounceRst)
                  pulsPin[i].timer=PULS_PIN_N_ANTIREBOTE;
               else
                  pulsPin[i].timer--;
            else
               {
               pulsPin[i].timer=PULS_PIN_N_ANTIREBOTE;
               pulsPinBuffer.pulsId=i;
               pulsPinBuffer.flag=1;
               pulsPinBuffer.fp=0;
               }
            }
         pulsPin[i].prevState=pulsPin[i].state;
         }
      else if(pulsPin[i].timer) pulsPin[i].timer--;
      }
   }

// Necesario para inicializar entradas conectadas a switches con retencion.
void pulsPinInit(void)
  {
   char i;

   for(i=0;i<PULS_PIN_CANT;i++)
      {
       pulsPin[i].state=BIT_GETVAL(*(pulsPin[i].p2port),pulsPin[i].bitNum);
       pulsPin[i].prevState=pulsPin[i].state;
      }
   }
