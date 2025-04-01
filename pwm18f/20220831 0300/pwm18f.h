//******************************************************************************
// ARCHIVO: pwm18f_lib.c
// AUTOR: Federico Ramos
// ULT. MODIF: 01-09-2021
// - Fosc asumida = 8Mhz (PIC12F683)
// - PWM seteado por defecto active-high
//******************************************************************************

// ESTA LIBRERÍA TIENE LA INICIALIZACIÓN DE LOS PUERTOS USADOS COMO PWM YA INCORPORADA
// A LA FUNCIÓN DE INICIALIZACIÓN PWM18F_INIT(), POR ESO NO ES NECESARIO INICIALIZAR
// LOS PUERTOS PWM USADOS.

#ifndef __PWM18F_LIB_H
#define __PWM18F_LIB_H




//******************************************************************************
// SETEOS USUARIO: CONSTANTES
//******************************************************************************
#define PIC12F683_FREQUENCY_19_61KHZ
#define PWM_INITIAL_STATE 0
#define VMAX 5.0
#define FOSC


//******************************************************************************
// COMPILACION CONDICIONAL: DEFINICIÓN DE PINES
// volatile bit PWM18F_PIN @ ((unsigned)&PORT_USADO*8)+NRO_DE_BIT_USADO;
//******************************************************************************
//#if	defined(_12F683)// FGR: COMPILACION CONDICIONAL
//	volatile bit PWM18F_PIN @ ((unsigned)&GPIO*8)+2;
//	volatile bit PWM18F_PIN_DDR @ ((unsigned)&TRISIO*8)+2;
//#else
	volatile bit PWM18F_PIN @ ((unsigned)&PORTC*8)+7;
	volatile bit PWM18F_PIN_DDR @ ((unsigned)&TRISC*8)+7;
//#endif// FGR: COMPILACION CONDICIONAL


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
   }t_pwm18f;
//******************************************************************************


//******************************************************************************
// DECLARACIÓN DE VARIABLES
extern t_pwm18f pwm18f;
//******************************************************************************


//EL USUARIO DEBE SELECCIONAR QUE PWM USAR DEFINIENDO PWMX
#ifdef PWM4
    enum  CCP4_TIMER_SELECTION {CCP4_TMR12,CCP4_TMR34};
    #define CCP4_TIMER_SELECTION CCP4_TMR34// SELECCION POR PARTE DEL USUARIO PARA QUE TIMERS USA CCP4
    #define CXTSEL C4TSEL
    #define CCPRXL CCPR4L
#define CCPXM0 CCP4M0
#define CCPXM1 CCP4M1
#define CCPXM2 CCP4M2
#define CCPXM3 CCP4M3
	#define PR2_VAL 0x65
	#define TIMER2_CKPS0_VAL 0
	#define TIMER2_CKPS1_VAL 0
#endif









//******************************************************************************
// MACROS
#define PWM18F_INIT()\
	{\
CXTSEL=CCP4_TIMER_SELECTION;\
	PWM18F_PIN_DDR=OUTPUT;\
	PWM18F_PIN=PWM18F_INITIAL_STATE;\
	
PR2=PR2_VAL;\
	CCPXM0=0;\// PWM mode = active-high
	CCPXM1=0;\// PWM mode = active-high
	CCPXM2=1;\// PWM mode = active-high
	CCPXM3=1;\// PWM mode = active-high

CCPRXL=0x00;\

	DC1B0=0;\
	DC1B1=0;\
	TMR2IF=0;\
	T2CKPS0=TIMER2_CKPS0_VAL;\// Prescaler
	T2CKPS1=TIMER2_CKPS1_VAL;\// Prescaler
	TMR2ON=1;\
	}
//******************************************************************************


#endif//__PWM18F_LIB_H