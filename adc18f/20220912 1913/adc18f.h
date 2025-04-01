//******************************************************************************
// ARCHIVO: adc18f_lib.h
//******************************************************************************


#ifndef __ADC18F_LIB_H
#define __ADC18F_LIB_H


//******************************************************************************
// DEFINO AQUI LOS NOMBRE QUE EL USUAROP VA A SELECCIONAR CUANDO LE PONE UN NOMBRE SIGNIFICATIVO A LOS PUERTOS
// POR ESO LO DEBO DEFINIR ANTES DEL ADC18F_USER_DEFINITIONS.H
#define ADC18F_CHANNEL00 0
#define ADC18F_CHANNEL01 1
#define ADC18F_CHANNEL02 2
#define ADC18F_CHANNEL03 3
#define ADC18F_CHANNEL04 4
#define ADC18F_CHANNEL05 5
#define ADC18F_CHANNEL06 6
#define ADC18F_CHANNEL07 7
#define ADC18F_CHANNEL12 12
//******************************************************************************


//******************************************************************************
// ARCHIVO DENTRO DEL DIRECTORIO DEL PROYECTO, CONFIGURADO POR EL USUARIO
//******************************************************************************
#include <adc18f_user_definitions.h>


//******************************************************************************
// FLAG GENERADO EN FUNCION DE AJUSTES DE USUARIO PARA SABER SI USA O NO ADC Y COMPILAR CODIGO CORRECTO
//******************************************************************************
#define ADC18F_USE (ADC18F_CH01_USE+ADC18F_CH02_USE+ADC18F_CH03_USE+ADC18F_CH04_USE+ADC18F_CH05_USE+ADC18F_CH06_USE+ADC18F_CH07_USE+ADC18F_CH08_USE+ADC18F_CH09_USE+ADC18F_CH10_USE+ADC18F_CH11_USE+ADC18F_CH12_USE+ADC18F_CH13_USE+ADC18F_CH14_USE)

#define IRQ_ADC ADIE&&ADIF//PARA REVISAR SI HA OCURRIDO INTERRUPCIÓN

//******************************************************************************
//
//******************************************************************************
typedef struct
{
unsigned int completeFlg:1;//conversion complete
unsigned int inProcessFlg:1;//está haciendo una conversión. Se mantiene en 1
// mientras esté "ocupado" el ADC. Solo cuando el usuario leyó la conversión,
// regresa a cero.
unsigned char chComp;//numero de canal completado
unsigned int flgs2convert;//flags que indican canales que tienen que convertir
char nx2convert;// Next to convert. Avanza desde channel0 a channel 12 preguntando si tiene
// que convertir. Al llegar al 7, comienza nuevamente desde el 0. Esto permite
// que le de bola a todos, y que no haya priodidades.
}t_adc;


//******************************************************************************
// DECLARACIÓN DE FUNCIONES
//******************************************************************************
int getConv(void);
void adcDriver(void);
void isr_adc(void);
void adcSetup_18F46K80(void);


//******************************************************************************
// DECLARACIÓN DE VARIABLES
//******************************************************************************
extern t_adc adcStruct;


//******************************************************************************
// MACROS
//******************************************************************************
#define ADC_START(n) BIT_SET(adcStruct.flgs2convert,n)//n = channel en decimal 
#define ADC_NEW_RESULT(channel) (adcStruct.completeFlg && adcStruct.chComp==channel)


#endif//__ADC18F_LIB_H