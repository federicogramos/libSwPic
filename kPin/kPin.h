/*******************************************************************************
 * @file kPin.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251525 1421
 * @note Uso de pines como pulsadores con debouncing. kPin = key-pin.
 ******************************************************************************/


#ifndef __K_PIN_H
#define __K_PIN_H


//==============================================================================
// Nombres de pulsadores por parte del usuario.
//==============================================================================

#include <kPin_aliases.h>


//==============================================================================
// Estructuras
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.
//==============================================================================

typedef struct
    {
    unsigned char kId : 5;
    unsigned char flag : 1;
    unsigned char flanco : 1;
    } t_kEvent;

typedef struct
    {
    unsigned char state : 1;
    unsigned char prevState : 1;
    unsigned char timer;
    } t_kPin;



//==============================================================================
// Pindef e inicialización de vector.
//==============================================================================

#include <kPin_pindef.h>


//==============================================================================
// Enum
//==============================================================================

enum e_flanco {FLANCO_N,FLANCO_P};


//==============================================================================
// Globals
//==============================================================================

extern t_kEvent kPinBuffer;


//==============================================================================
// Macros
//==============================================================================

#define KPIN_EVENT() (kPinBuffer.flag?!(kPinBuffer.flag=0):0)
#define KPIN_GET_ID() (kPinBuffer.kId)
#define KPIN_EVENT_ID(i) (kPinBuffer.flag && kPinBuffer.kId==i?!(kPinBuffer.flag=0):0)
#define KPIN_EVENT_FP_ID(i) (kPinBuffer.flag && kPinBuffer.flanco==FLANCO_P && kPinBuffer.kId==i?!(kPinBuffer.flag=0):0)
#define KPIN_EVENT_FN_ID(i) (kPinBuffer.flag && kPinBuffer.flanco==FLANCO_N && kPinBuffer.kId==i?!(kPinBuffer.flag=0):0)


//==============================================================================
// Prototipos
//==============================================================================

void kPin_driverDc(char pi, char kCurrLogState);
void kPin_driverAcFn(char pi, char flanco, char kCurrLogState);
void kPin_driverAcFp(char pi, char flanco, char kCurrLogState);


#endif// __K_PIN_H