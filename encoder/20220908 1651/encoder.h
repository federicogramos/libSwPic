//*****************************************************************************
// ARCHIVO: encoder_lib.h
// AUTOR: Federico Ramos
// ULT MODIF: 08-09-2022
//*****************************************************************************

#ifndef __ENCODER_H
#define __ENCODER_H

//*****************************************************************************
// NOMBRES DE PULSADORES POR PARTE DEL USUARIO
//#include <pulsadorPinFast_1ms_aliases.h>
//*****************************************************************************

#define ENCODER_N_ANTIREBOTE 1//LE PONGO EN ESTE PROYECTO 10MS PORQUE DE ESA MANERA CON ANTIREBOTE, LA FRECUENCIA MAXIMA ES 50HZ, ALGO ACEPTABLE


//*****************************************************************************
// ESTRUCTURAS
// No permite hacer arreglos de bitfields, por eso debo hacer estructura de
// bitfield y luego un arreglo de esa estructura.
typedef struct
    {
    unsigned char encoderId:5;
    unsigned char encoderFlag:2;
    unsigned char pulsId:2;
    unsigned char pulsFlag:1;
    }t_encoderEvent;

typedef struct
    {
    unsigned char state;
    }t_encoder;

typedef struct
  {
  unsigned char state:1;
  unsigned char prevState:1;
  unsigned char timer;
  }t_encoderPuls;
//*****************************************************************************



//*****************************************************************************
// ENUMS
enum e_encoder_names
    {
    E0,
    ENCODER_CANT
    };
enum e_encoder_flags {ENCODER_NOTHING,ENCODER_CW,ENCODER_CCW};

enum e_encoderPulsAlias
	{
	ENCODER_PIN_AN,
    ENCODER_PIN_BN,
	ENCODER_PIN_AP,
    ENCODER_PIN_BP,
	ENCODER_PIN_CANT
	};

enum e_encoder_states
    {
    ENCODER_STATE_IDLE,
    ENCODER_STATE_A,
    ENCODER_STATE_AB,
    ENCODER_STATE_ABX,
    ENCODER_STATE_B,
    ENCODER_STATE_BA,
    ENCODER_STATE_BAY
    };
enum e_encoder_flanco {ENCODER_FLANCO_N,ENCODER_FLANCO_P};
//*****************************************************************************


//*****************************************************************************
// DECLARACIÓN DE VARIABLES GLOBALES
extern t_encoderEvent encoderBuffer;
//*****************************************************************************


//*****************************************************************************
// MACROS
#define ENCODER_EVENT() (encoderBuffer.encoderFlag?!(encoderBuffer.encoderFlag=0):0)
#define ENCODER_GET_ID() (encoderBuffer.encoderId)
#define ENCODER_CW_ID(i) (encoderBuffer.encoderFlag==ENCODER_CW && encoderBuffer.encoderId==i?!(encoderBuffer.encoderFlag=0):0)
#define ENCODER_CCW_ID(i) (encoderBuffer.encoderFlag==ENCODER_CCW && encoderBuffer.encoderId==i?!(encoderBuffer.encoderFlag=0):0)

#define ENCODER_PULS_EVENT_ID(i) (encoderBuffer.pulsFlag && encoderBuffer.pulsId==i?!(encoderBuffer.pulsFlag=0):0)
//*****************************************************************************

#define ENCODER_0_DRIVER() (encoder_driver(E0))

//*****************************************************************************
// DECLARACIÓN DE FUNCIONES
void encoderInit(void);
void encoder_driver(char e);
//*****************************************************************************


#endif//__ENCODER_H
