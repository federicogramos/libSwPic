// fsm.h
////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////
// DEFINICION ESTRUCTURAS                                              //
/////////////////////////////////////////////////////////////////////////

struct t_transition
   {
   char event;
   const struct t_transition *nextState;
   char action;
   };

typedef struct t_transition t_state;



// FORWARD DECLARATION OF STATES
#include <fsm_forward.h>

extern const t_state *p2tablaDeEstado;

// DECLARACIÓN DE FUNCIONES
void fsmParser(void);