// pulsador.h

// NOMBRES DE PULSADORES POR PARTE DEL USUARIO
#include <pulsadorPin_1ms_aliases.h>

// CONSTANTES
#define PULS_PIN_N_ANTIREBOTE 100

// ESTRUCTURAS
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.

typedef struct
   {
   unsigned char pulsId:5;
   unsigned char flag:1;
   unsigned char fp:1;//Guarda si es positivo o negativo.
   }t_pulsEvent;

typedef struct
  {
  char *p2port;
  unsigned char bitNum:3;
  unsigned char state:1;
  unsigned char prevState:1;
  unsigned char fp:1; //deteccion de flanco positivo fp=1 -> flanco positivo (suelta pulsador pull-up)
  unsigned char fn:1; //deteccion de flanco negativo (presiona pulsador con pull-up)
  unsigned char unbounceRst:1; //while in unbounce interval, reset unbounce time until input stays quiet.
  unsigned char timer;
  }t_pulsPin;

// DECLARACIÓN DE FUNCIONES
void pulsPinDriver(void);
void pulsPinInit(void);

extern t_pulsEvent pulsPinBuffer;

#define PULSPIN_EVENT() (pulsPinBuffer.flag?!(pulsPinBuffer.flag=0):0)
#define PULSPIN_GET_ID() (pulsPinBuffer.pulsId)
#define PULSPIN_EVENT_ID(i) (pulsPinBuffer.flag && pulsPinBuffer.pulsId==i?!(pulsPinBuffer.flag=0):0)
#define PULSPIN_EVENT_FP() (pulsPin[pulsPinBuffer.pulsId].state)
#define PULSPIN_EVENT_ID_FP(i) (pulsPinBuffer.flag && pulsPinBuffer.pulsId==i && pulsPinBuffer.fp==1 ?!(pulsPinBuffer.flag=0):0)
#define PULSPIN_EVENT_ID_FN(i) (pulsPinBuffer.flag && pulsPinBuffer.pulsId==i && pulsPinBuffer.fp==0?!(pulsPinBuffer.flag=0):0)