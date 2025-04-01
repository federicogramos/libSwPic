/******************************************************************************/
/* ARCHIVO:     pulsadorPin.c                                                 */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: Funciones específicas de cada proyecto.                       */
/* ÚLT. MODIF:  18-06-2019 1712                                               */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO INDISPENSABLES                                  */
/******************************************************************************/
#include <projectHeader.h>
#include <pulsadorPin_lib_1ms.h>


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO INDISPENSABLES: ESTE ARCHIVO DEBE SER INCLUIDO  */
/* Y EDITADO A MEDIDA SEGUN EL PROYECTO                                       */
/******************************************************************************/
#include <pulsadorPin_1ms_pindef.h>


/******************************************************************************/
/* VARIABLES GLOBALES                                                         */
/******************************************************************************/
// PulsPin: los pines tocados se identifican de 1..N porque el 0 se reserva para
// indicar "ninguno ha sido presionado".
t_pulsEvent pulsPinBuffer;


/******************************************************************************/
/* FUNCIÓN:     pulsPinDriver(void)                                           */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: Chequea por eventos en todos los pulsadores y los carga en el */
/*              buffer.                                                       */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:  Para ejecutar con periodo de 1ms                              */
/******************************************************************************/
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


/******************************************************************************/
/* FUNCIÓN:     pulsPinInit(void)                                             */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:                                                                */
/******************************************************************************/
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
