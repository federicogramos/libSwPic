//******************************************************************************
// ARCHIVO: pwm_lib.c
// AUTOR: Federico Ramos
// ULT. MODIF: 13-12-2021
// COMENTARIO:
// - Fosc asumida = 8Mhz (PIC12F683)
// - PWM seteado por defecto active-high
//******************************************************************************


#ifndef __PWM_LIB_H
#define __PWM_LIB_H


//******************************************************************************
// SETEOS USUARIO: CONSTANTES
//******************************************************************************
#define PIC12F683_FREQUENCY_19_61KHZ
#define PWM_INITIAL_STATE 0
#define VMAX 5.0

//******************************************************************************
// COMPILACION CONDICIONAL: DEFINICIÓN DE PINES
//******************************************************************************
#if	defined(_12F683)// FGR: COMPILACION CONDICIONAL
	volatile bit PWM_PIN @ ((unsigned)&GPIO*8)+2;
	volatile bit PWM_PIN_DDR @ ((unsigned)&TRISIO*8)+2;
#else
	volatile bit PWM_PIN @ ((unsigned)&GPIO*8)+2;
	volatile bit PWM_PIN_DDR @ ((unsigned)&TRISIO*8)+2;
#endif// FGR: COMPILACION CONDICIONAL


//******************************************************************************
// CONSTANTES DE COMPILACIÓN CONDICIONAL
//******************************************************************************
#ifdef PIC12F683_FREQUENCY_19_61KHZ
	#define PR2_VAL 0x65
	#define TIMER2_CKPS0_VAL 0
	#define TIMER2_CKPS1_VAL 0
#endif

#ifdef PIC12F683_FREQUENCY_10_00KHZ
	#define PR2_VAL 0xC8
	#define TIMER2_CKPS0_VAL 0
	#define TIMER2_CKPS1_VAL 0
#endif









//******************************************************************************
// ESTRUCTURAS
typedef struct
   {
   float meanVout;
   }t_pwm;
//******************************************************************************


//******************************************************************************
// DECLARACIÓN DE VARIABLES
extern t_pwm pwm;
//******************************************************************************


//******************************************************************************
// MACROS
#define PWM_INIT()\
	{\
	PWM_PIN_DDR=OUTPUT;\
	PWM_PIN=PWM_INITIAL_STATE;\
	PR2=PR2_VAL;\
	CCP1M0=0;\// PWM mode = active-high
	CCP1M1=0;\// PWM mode = active-high
	CCP1M2=1;\// PWM mode = active-high
	CCP1M3=1;\// PWM mode = active-high
	CCPR1L=0x00;\
	DC1B0=0;\
	DC1B1=0;\
	TMR2IF=0;\
	T2CKPS0=TIMER2_CKPS0_VAL;\// Prescaler
	T2CKPS1=TIMER2_CKPS1_VAL;\// Prescaler
	TMR2ON=1;\
	}
//******************************************************************************


#endif//__PWM_LIB_H