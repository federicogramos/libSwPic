//==============================================================================
// Archivo: fsm.c
// Autor: Federico Ramos
// Modificado: 17-11-2023 1650
//
// En este archivo:
// - INCLUDE HEADERS
// - DEFINICION DE VARIABLES GLOBALES
// - DEFINICION DE FUNCIONES
//      o fsmParser(void)
//==============================================================================


//==============================================================================
// INCLUDE
#include <projectHeader.h>
#include <fsm.h>
#include <fsm_events.h>
#include <fsm_actions.h>
//==============================================================================


//==============================================================================
// DEFINICION DE VARIABLES GLOBALES

// Estados posibles = 0..n
// Mnemotécnicamente, se encuentran definidos en fsm_table_ix mediante un enum.
// fsmStateTable[n] es el puntero a un array con todas las transiciones que el
// estado <n> tiene.

char estadoFsm;
//==============================================================================


//==============================================================================
// FUNCTION fsmParser(void)
//==============================================================================
void fsmParser(void)
    {
    char event,ix2Trans;

    ix2Trans=0;// Recorre transiciones posibles para un estado.
    event=fsmGetEvent();

    while(
         ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].event!=
         EV_TABLE_END &&
         ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].event!=event
         )
        ix2Trans++;

    ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].action();

    estadoFsm=((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].nextState;
    }

