// pulsador_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __PULSADOR_LIB_H
#define __PULSADOR_LIB_H

// NOMBRES DE PULSADORES POR PARTE DEL USUARIO
#include <pulsador_aliases.h>

// CONSTANTES (SETEAR PULS_N_ANTIREBOTE*TINTERRUPT=40MS)
#define PULS_N_ANTIREBOTE 4

// ESTRUCTURAS
typedef struct
   {
   unsigned char pulsId:5;
   unsigned char flag:1;
   }t_pulsEvent;

typedef struct
   {
   char *p2port;
   unsigned char bitNum:3;
   unsigned char event_on_push:1;
   unsigned char state:1;
   unsigned char prevState:1;
   unsigned char timer:6;
   }t_pulsPin;

// DECLARACIÓN DE VARIABLES
extern t_pulsEvent pulsBuffer;
extern t_pulsPin pulsPin[CANT_PULS];

// DECLARACIÓN DE FUNCIONES
void pulsPinDriver(void);

// MACROS
#define PULS_EVENT() (pulsBuffer.flag?!(pulsBuffer.flag=0):0)
#define PULS_GET_ID() (pulsBuffer.pulsId)
#define PULS_EVENT_ID(i) (pulsBuffer.flag && pulsBuffer.pulsId==i?!(pulsBuffer.flag=0):0)

// MACRO AUXILIAR
#define BIT_GETVAL_PULS(byte,bitno) !(((1UL<<(bitno)) & (byte))==0)

#endif//__PULSADOR_LIB_H