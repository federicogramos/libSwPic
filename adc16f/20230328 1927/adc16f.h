//******************************************************************************
//
// Archivo: adc16f_lib.h
// Autor: Federico Ramos
// Modificado: 2023-03-31
//
// En este archivo:
// - USO DE LA LIBRERIA
// - DECLARACIÓN DE FUNCIONES
// - DEFINICIÓN DE CONSTANTES
// - DEFINICIÓN DE MACROS
// - DEFINICIÓN DE ESTRUCTURAS
// - DECLARACIÓN DE VARIABLES GLOBALES
//
//******************************************************************************



#ifndef __ADC16F_LIB_H
#define __ADC16F_LIB_H



//******************************************************************************
//
// ADC USER CONSTANT DEFINITIONS
//
//*****************************************************************************

#include <adc16f_userSettings.h>



//******************************************************************************
//
// USO DE LA LIBRERÍA
//
//*****************************************************************************

// - "adc16f_driver" en el ciclo principal del programa:
// void main(void)
//      {
//      while(1)
//		    {
//          adc16f_driver();// Inicia y administra conversiones.
//
//          // Si TSAMPLE() es suficientemente grande comparado con el ciclo
//          // while y TconversionADC, los 2 canales son esencialmente
//          // muestreados al mismo TSAMPLE() definido.
//          if(ADC16F_TSAMPLE())
//              {
//              if(ADC16F_NEW_RESULT(ADC16F_VIN))
//                  voltage = adc16f_getConv();
//              else if(ADC16F_NEW_RESULT(ADC16F_VOUT))
//                  voltage = adc16f_getConv();
//              }
//          }
//      }

// Dentro de las llamadas a interrupción:
// - "adc16f_isr"
// - "IRQ_ADC_RESET_FLAG"
// void interrupt isr(void)
//      {
//      if(IRQ_ADC())
//          {
//          adc16f_isr();
//          IRQ_ADC_RESET_FLAG();
//          }
//      }

// En la inicialización del sistema:
// - "ADC16F_ENABLE"
// - "ADC16F_ANSELECT"
// - "ADC16F_IRQ_ENABLE"
// void systemInit(void)
//      {
//      ADC16F_ENABLE();
//      ADC16F_ANSELECT(0,0,0,0,0,0,0,0,1,0,1);// RB5=AN13, RB4=AN11
//      ADC16F_IRQ_ENABLE();
//      IRQ_ENABLE();// Enable all interrupts
//      }
//
// ADC16F_START(n)
// ADC16F_NEW_RESULT(channel)
// adc16f_getConv()



//******************************************************************************
// DECLARACIÓN DE FUNCIONES

void adc16f_driver(void);
void adc16f_isr(void);
unsigned char adc16f_getConv(void);

//******************************************************************************



//******************************************************************************
//
// DEFINICIÓN DE CONSTANTES
//
// A estas constantes se debe referir el usuario para definir los canales que va
// a utilizar
//
//******************************************************************************

#define ADC16F_CH00 0// AN0
#define ADC16F_CH01 1// AN1
#define ADC16F_CH02 2// AN2
#define ADC16F_CH03 3// AN3
#define ADC16F_CH04 4// AN4
#define ADC16F_CH05 5// AN5
#define ADC16F_CH06 6// AN6
#define ADC16F_CH07 7// AN7
#define ADC16F_CH08 8// AN8
#define ADC16F_CH09 9// AN9
#define ADC16F_CH10 10// AN10
#define ADC16F_CH11 11// AN11
#define ADC16F_CH12 12// AN12
#define ADC16F_CH13 13// AN13
#define ADC16F_CH14 14// CVREF
#define ADC16F_CH15 15// FixedRef



//******************************************************************************
//
// MACROS
//
//******************************************************************************

#define IRQ_ADC() (ADIE&&ADIF)

#define IRQ_ADC_RESET_FLAG()  {ADIF=0;}

#define ADC16F_IRQ_ENABLE() {ADIE=1;}

#define ADC16F_IRQ_DISABLE() {ADIE=0;}

#define ADC16F_START(n) BIT_SET(adc16f_t.flgs2convert, n)

#define ADC16F_NEW_RESULT(channel) (   \
    adc16f_t.completeFlg &&            \
    adc16f_t.chComp==channel)          \

// ANSEL configura puerto como analógico o digital. Si es analógico, aún se debe
// configurar el multiplexor CHS para que rutee esa entrada al AD.
//
// Si no deshabilito todos los analogicos, los pull ups no puedan estar.
//
//          +-------------------------------------------+
// ANSEL  = |ANS7|ANS6|ANS5 |ANS4 |ANS3 |ANS2 |ANS1|ANS0|
//          +-------------------------------------------+
// ANSELH = | -  | -  |ANS13|ANS12|ANS11|ANS10|ANS9|ANS8|
//          +-------------------------------------------+
//
// Se inicializa ANSEL = ANSELH = 0. Luego una macro debe setear pines
// analogicos.
//
// 28 pin uc not implemented: ANS5, ANS6, ANS7
//
// ADC       | Source | 20    | 8     | 4     | 1      |
// Clock     | ADCS   | MHz   | MHz   | MHz   | MHz    |
//           | <1:0>  |       |       |       |        |
// FOSC/2    | 00     | 100 ns| 250 ns| 500 ns| 2.0  us|
// FOSC/8    | 01     | 400 ns| 1.0 us| 2.0 us| 8.0  us|
// FOSC/32   | 10     | 1.6 us| 4.0 us| 8.0 us| 32.0 us|
// FRC       | 11     | 2-6 us| 2-6 us| 2-6 us| 2-6  us|
#define ADC16F_ENABLE()                                                        \
    {                                                                          \
    ANSEL=0; /* Inicializa ANSEL = ANSELH = 0. Luego una macro debe setear   */\
    ANSELH=0;/* pines analogicos.                                            */\
                                                                               \
    ADCS0=1;/* Conversion Clock = FOSC/8                                     */\
    ADCS1=0;                                                                   \
                                                                               \
    ADFM=0;/* Format a la izquierda para tomar solo ADRESH y usar 8 bits ADC */\
    ADIF=0;                                                                    \
    ADON=1;                                                                    \
    }

// Si no se va a usar el A/D, esta función se debe invocar, ya que por defecto,
// luego del reset, los puertos de entrada comienzan como entradas analógicas
// para ser usadas con el A/D, lo cual deshabilita que funcionen como entradas o
// salidas digitales.
#define ADC16F_DISABLE()                                                       \
    {                                                                          \
    ANSEL=0; /* Si no deshabilito todos los analogicos, los pull ups no      */\
    ANSELH=0;/* pueden estar                                                 */\
    }

// 28 pin uc not implemented: ANS5, ANS6, ANS7
//#define ADC16F_ANSELECT(an0,an1,an2,an3,an4,an8,an9,an10,an11,an12,an13)       
#define ADC16F_ANSELECT(an13, an12, an11, an10, an9, an8,                      \
an4, an3, an2, an1, an0)                                                       \
    {                                                                          \
    ANS0 = an0;/* ANSEL                                                      */\
    ANS1 = an1;                                                                \
    ANS2 = an2;                                                                \
    ANS3 = an3;                                                                \
    ANS4 = an4;                                                                \
                                                                             \
    ANS8 = an8;/* ANSELH                                                     */\
    ANS9 = an9;                                                                \
    ANS10 = an10;                                                              \
    ANS11 = an11;                                                              \
    ANS12 = an12;                                                              \
    ANS13 = an13;                                                              \
    }



//******************************************************************************
//
// DEFINICIÓN DE ESTRUCTURAS
//
//******************************************************************************

typedef struct
    {
    unsigned int completeFlg:1;// Conversion complete

    // Está haciendo una conversión. Se mantiene en 1 mientras esté "ocupado" el
    // ADC. Solo cuando el usuario leyó la conversión, regresa a cero.
    unsigned int inProcessFlg:1;

    unsigned char chComp;// numero de canal completado

    // Uso interno del driver: indica canales a convertir (array de bits)
    // Bits corresponden 1 a 1 con el número de canal según las constantes
    // definidas: ADC16F_CHXX
    // +-----------------------------+------------------------------+
    // | CH15 CH14 ... CH10 CH9 CH08 | CH07 CH06 ... CH02 CH01 CH00 |
    // +-----------------------------+------------------------------+
    // Puedo tener seteados varios simuntáneamente, y el adc16f_driver() irá
    // barriendo y convirtiendo.
    unsigned int flgs2convert;

    // Avanza desde ch0 a ch15 preguntando si tiene que convertir. Al llegar al
    // tope (15), comienza nuevamente desde el 0. Esto permite que le de bola a
    // todos, y que no haya priodidades
    char nx2convert;
    } adc16f_struct;

// Bitfield definitions. La defino yo, porque el el header por defecto vienen
// definidos los bits por separado, pero en este caso particular para el
// adc16f_driver() lo requiero a CHS como un valor entero para no usar macros de
// desplazamiento (BIT_GETVAL_QUICK no asignaba correctamente).
extern volatile union
    {
    struct
        {
        unsigned ADON   :1;
        unsigned GODONE :1;
        unsigned CHS    :4;// CHS3..CHS0
        unsigned ADCS   :2;// ADCS1:ADCS0
        };
    struct
        {
        unsigned ADCON0 :8;
        };
    } ADCON0_t @ &ADCON0;



//******************************************************************************
// DECLARACIÓN DE VARIABLES GLOBALES

extern adc16f_struct adc16f_t;

//******************************************************************************



#endif// __ADC16F_LIB_H
