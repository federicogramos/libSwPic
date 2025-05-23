//==============================================================================
// ARCHIVO: kPin.h
// AUTOR: Federico Ramos
// ULT MODIF: 2024-06-12
//==============================================================================


//==============================================================================
// NOMBRES DE PULSADORES POR PARTE DEL USUARIO
#include <kPin_aliases.h>
//==============================================================================


//==============================================================================
// ESTRUCTURAS
//==============================================================================
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.

typedef struct
    {
    unsigned char kId:5;
    unsigned char flag:1;
    }t_kEvent;

typedef struct
    {
    unsigned char state:1;
    unsigned char prevState:1;
    unsigned char timer;
    }t_kPin;


//==============================================================================
// PINDEF E INICIALIZACIÓN DE VECTOR
#include <kPin_pindef.h>
//==============================================================================


//==============================================================================
// ENUMS
enum e_flanco {FLANCO_N,FLANCO_P};
//==============================================================================


//==============================================================================
// DECLARACIÓN DE VARIABLES GLOBALES
extern t_kEvent kPinBuffer;
//==============================================================================


//==============================================================================
// MACROS
#define KPIN_EVENT() (kPinBuffer.flag?!(kPinBuffer.flag=0):0)
#define KPIN_GET_ID() (kPinBuffer.kId)
#define KPIN_EVENT_ID(i) (kPinBuffer.flag && kPinBuffer.kId==i?!(kPinBuffer.flag=0):0)
//==============================================================================


//==============================================================================
// DECLARACION DE FUNCIONES
void kPin_driverDc(char pi, char flanco, char pulsCurrentState);
void kPin_driverAcFn(char pi, char flanco, char pulsCurrentState);
void kPin_driverAcFp(char pi, char flanco, char pulsCurrentState);
//==============================================================================

