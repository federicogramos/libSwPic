//==============================================================================
// Archivo: /fsm/../fsm.h
// Autor: Federico Ramos
// Modificado: 2022-10-13
//
// En este archivo:
// - DECLARACIÓN DE FUNCIONES
// - DECLARACION DE VARIABLES GLOBALES
// - DEFINICION ESTRUCTURAS
// - DEFINICION DE TABLA DE ESTADO
// - DEFINICION DE MACROS
//==============================================================================


#ifndef __FSM_H
#define __FSM_H


//==============================================================================
// DECLARACIÓN DE FUNCIONES
//==============================================================================
void fsmParser(void);


//==============================================================================
// DECLARACION DE VARIABLES GLOBALES
//==============================================================================
extern char estadoFsm;


//==============================================================================
// DEFINICION ESTRUCTURAS
//==============================================================================
typedef const struct t_transition
    {
    char event;
    void (*action)(void);
    char nextState;
    }t_fsmState;


//==============================================================================
// DEFINICION DE TABLA DE ESTADO
//==============================================================================
#include <fsm_table.h>


//==============================================================================
// MACROS
//==============================================================================

// MACRO: FSM_INIT()
//------------------------------------------------------------------------------
// BOOT_STATE definido en "fsm_table.h"
#define FSM_INIT() {estadoFsm=BOOT_STATE;}


char fsmGetEvent(void);


// MACRO: FSM_PARSER
//------------------------------------------------------------------------------
// Se da la alternativa de formato macro por possible stack overflow para micros
// de 8 niveles de stack como el PIC16F886
#define FSM_PARSER()                                                           \
    {                                                                          \
    char event,ix2Trans;                                                       \
                                                                               \
    ix2Trans=0;                                                                \
    event=fsmGetEvent();                                                       \
                                                                               \
    while(                                                                     \
         ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].event!=           \
         EV_TABLE_END &&                                                       \
         ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].event!=event      \
         )                                                                     \
        ix2Trans++;                                                            \
                                                                               \
    ((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].action();              \
    estadoFsm=((t_fsmState*)(fsmStateTable[estadoFsm]))[ix2Trans].nextState;   \
    }


#endif // __FSM_H

