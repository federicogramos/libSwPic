// fsm.c
////////////////////////////////////////////////////////////////////////////////
#include <projectHeader.h>
#include <fsm_lib.h>
#include <fsm_events.h>
#include <fsm_actions.h>
#include <fsm_transitions.h>

const t_state *p2tablaDeEstado=s_boot;

void fsmParser(void)
   {
   char event;

   event=fsmGetEvent();
   while(p2tablaDeEstado->event!=FSM_TABLE_END && p2tablaDeEstado->event!=event)
      {p2tablaDeEstado++;}
   fsmRunAction(p2tablaDeEstado->action);
   p2tablaDeEstado=p2tablaDeEstado->nextState;
   }
