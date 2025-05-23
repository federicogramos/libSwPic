// pulsPinDc_lib_1ms.h

// NOMBRES DE PULSADORES POR PARTE DEL USUARIO
#include <pulsPinDc_1ms_aliases.h>

// CONSTANTES
#define PULS_PIN_N_ANTIREBOTE 100

// ESTRUCTURAS
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.

typedef struct
   {
   unsigned char pulsId:5;
   unsigned char flag:1;
   }t_pulsEvent;

typedef struct
  {
  unsigned char state:1;
  unsigned char prevState:1;
  unsigned char timer;
  }t_pulsPin;

// DECLARACIÓN DE FUNCIONES
void puls_dc_0_driver(void);
void puls_dc_1_driver(void);
void puls_dc_2_driver(void);
void puls_dc_3_driver(void);
void puls_dc_4_driver(void);
void pulsPinInit(void);

extern t_pulsEvent pulsPinBuffer;

#define PULSPIN_EVENT() (pulsPinBuffer.flag?!(pulsPinBuffer.flag=0):0)
#define PULSPIN_GET_ID() (pulsPinBuffer.pulsId)
#define PULSPIN_EVENT_ID(i) (pulsPinBuffer.flag && pulsPinBuffer.pulsId==i?!(pulsPinBuffer.flag=0):0)

