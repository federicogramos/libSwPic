enum e_fsmEvent{E_SET_GIRO,
                E_SET_AVANCE,E_ACEPTAR,
                E_SET_RETROCESO,E_SET_VUELTAS,
                E_INICIO_HORARIO,
                E_INICIO_ANTIHORARIO,E_FIN,E_CERO_RETROCEDIENDO,
                E_PAUSE,
                FSM_NO_EVENT,FSM_ALWAYS,FSM_TABLE_END};
// No event se usa por defecto para enviar a la fsm, en el caso de que no ocurra
// nada. Dado que NO_EVENT es distinto a cualquier otro evento que pueda
// ocurrir en cualquier circunstancia, indefectiblemente la fsm llegará a
// TABLE_END y ejecutará esa acción, es decir, justo lo que se quería hacer.

//#include <pulsadorPin_lib.h>
//#include <auxiliar.h>
#include <interrupts.h>
//#include <mx_no_mem_4x4.h>
//#include <timerInt_lib.h>
#include <system.h>

// Para determinar el estado en el que me encuentro, en lugar de hacer un
// "switch", lo que hago es un "if" porque el compilador no permite realizar
// esa instrucción con un puntero, y si quiero hacer un "casteo" de la variable
// también tira error.

char fsmGetEvent(void)
   {
   char event=FSM_NO_EVENT;

//   if(p2tablaDeEstado==s_boot) event=FSM_ALWAYS;

  // if(p2tablaDeEstado==s_esperaComienzo)
      {
/*      if(PULSPIN_EVENT_ID_FN(PEDAL))
         {
         TMR_INT_START(TMR_BEEP_BOOT);
         BUZZ=1;

         if(bobinadora.estadoGiro==ESTADO_DETENIDO) bobinadora.pulsosActuales=0;
         bobinadora.estadoGiro=ESTADO_AVANCE;

         if(bobinadora.sentidoGiro==SEN_GIR_HOR)
            {
            event=E_INICIO_HORARIO;
            SENTIDO_GIRO=SEN_GIR_HOR;
            }
         else
            {
            event=E_INICIO_ANTIHORARIO;
            SENTIDO_GIRO=SEN_GIR_ANTIHOR;
            }
         //bobinadora.irqTimerResetVal=(unsigned int)(65536-500/(unsigned int)bobinadora.velAvance);
         //bobinadora.irqTimerResetVal=(unsigned int)(65536-(unsigned int)bobinadora.velAvance);
         bobinadora.irqTimerResetVal=(unsigned long)(65536-(unsigned long)1800000/bobinadora.velAvance);
         SYS_TIMER1_RUN_ENABLE();
         }
      if(kbhit())
         {
         c=getchar();
         if(c=='*')
            {
            TMR_INT_START(TMR_BEEP_BOOT);
            BUZZ=1;

            if(bobinadora.estadoGiro==ESTADO_DETENIDO) bobinadora.pulsosActuales=0;
            bobinadora.estadoGiro=ESTADO_RETROCESO;
            if(bobinadora.sentidoGiro==SEN_GIR_HOR)
               {
               event=E_INICIO_ANTIHORARIO;
               SENTIDO_GIRO=SEN_GIR_ANTIHOR;
               }
            else
               {
               event=E_INICIO_HORARIO;
               SENTIDO_GIRO=SEN_GIR_HOR;
               }
            bobinadora.irqTimerResetVal=(unsigned int)(65536-500/(unsigned int)bobinadora.velRetroceso);
            SYS_TIMER1_RUN_ENABLE();
            }
         else if(c=='A') event=E_SET_VUELTAS;
         else if(c=='B') event=E_SET_AVANCE;
         else if(c=='C') event=E_SET_RETROCESO;
         else if(c=='D') event=E_SET_GIRO;
         }
*/
      }

   if(p2tablaDeEstado==s_seteoSentidoGiro)
      {
      }

   if(p2tablaDeEstado==s_ingresoVelocidadAvance)
      {
      }

   if(p2tablaDeEstado==s_seteoVelocidadRetroceso)
      {
      }

   if(p2tablaDeEstado==s_ingresoCantidadVueltas)
      {
      
      }

   if(p2tablaDeEstado==s_giroHorario)
      {/*
      if(bobinadora.estadoGiro==ESTADO_DETENIDO) event=E_FIN;

      if(PULSPIN_EVENT_ID_FN(PEDAL))
         {
         TMR_INT_START(TMR_BEEP_BOOT);
         BUZZ=1;

         bobinadora.estadoGiro=ESTADO_PAUSA;
         event=E_PAUSE;
         SYS_TIMER1_RUN_DISABLE();
         }

      if(kbhit())
         {
         c=getchar();
         if(c=='*')
            {
            TMR_INT_START(TMR_BEEP_BOOT);
            BUZZ=1;

            bobinadora.estadoGiro=ESTADO_PAUSA;
            event=E_PAUSE;
            SYS_TIMER1_RUN_DISABLE();
            }
         }
      */}

   if(p2tablaDeEstado==s_giroAntihorario)
      {
/*      if(bobinadora.estadoGiro==ESTADO_DETENIDO) event=E_FIN;

      if(PULSPIN_EVENT_ID_FN(PEDAL))
         {
         TMR_INT_START(TMR_BEEP_BOOT);
         BUZZ=1;

         bobinadora.estadoGiro=ESTADO_PAUSA;
         event=E_PAUSE;
         SYS_TIMER1_RUN_DISABLE();
         }

      if(kbhit())
         {
         c=getchar();
         if(c=='*')
            {
            TMR_INT_START(TMR_BEEP_BOOT);
            BUZZ=1;

            bobinadora.estadoGiro=ESTADO_PAUSA;
            event=E_PAUSE;
            SYS_TIMER1_RUN_DISABLE();
            }
         }
  */    }

   if(p2tablaDeEstado==s_notificacionFinal)
      {
      /*if(kbhit())
         {
         c=getchar();
         if(c=='#')
            {
            event=E_ACEPTAR;
            TMR_INT_START(TMR_BEEP_BOOT);
            BUZZ=1;
            }
         }
      if(PULSPIN_EVENT_ID_FN(PEDAL))
         {
         event=E_ACEPTAR;
         TMR_INT_START(TMR_BEEP_BOOT);
         BUZZ=1;
         }
      */}

   return event;
   }