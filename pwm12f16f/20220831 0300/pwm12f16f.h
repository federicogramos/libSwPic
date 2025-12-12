/*******************************************************************************
 * @file pwm12f16f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251125 1757
 * @note Uso pwm.
 *
 * - Fosc asumida = 8Mhz (PIC12F683)
 * - PWM seteado por defecto active-high
 ******************************************************************************/


////////////////////////////////////////////////////////////////////////////////
// TO-DO: aun tiene que ser trabajada, debo separar lo que son los seteos de usu
// ario de aquello que es el funcionamiento y no se toca nunca.
////////////////////////////////////////////////////////////////////////////////


#ifndef __PWM12F16F_H
#define __PWM12F16F_H


/*******************************************************************************
 * @brief Seteos de usuario: frecuencia pwm
 * 
 * Se debe definir alguna de estas 2:
 * #define PIC12F683_FREQUENCY_19_61KHZ
 * #define PIC12F683_FREQUENCY_10_00KHZ
 * Y en funcion de cual se deja habilitada, en pwm12f16f.h hay compilacion condi
 * cional que setea los valores de los registros de frecuencia TIMER2_CKPS0 y 1.
 ******************************************************************************/

#define PIC12F683_FREQUENCY_19_61KHZ
// #define PIC12F683_FREQUENCY_10_00KHZ

/*******************************************************************************
 * @brief Seteos de usuario: varios
 ******************************************************************************/

#define PWM_INITIAL_STATE 0
#define VMAX 5.0


/*******************************************************************************
 * @brief Compilacion condicional: definicion de pines
 ******************************************************************************/

#if	defined(_12F683)
	volatile bit PWM_PIN @ ((unsigned)&GPIO*8)+2;
	volatile bit PWM_PIN_DDR @ ((unsigned)&TRISIO*8)+2;
#else
	volatile bit PWM_PIN @ ((unsigned)&GPIO*8)+2;
	volatile bit PWM_PIN_DDR @ ((unsigned)&TRISIO*8)+2;
#endif


/*******************************************************************************
 * @brief Constantes de compilacion condicional
 ******************************************************************************/

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


/*******************************************************************************
 * @brief Structures
 * 
 * Esto no está implementado, pero no es mala idea.
 ******************************************************************************/

typedef struct {
   float meanVout;
} t_pwm;



/*******************************************************************************
 * @brief External declarations
 ******************************************************************************/

extern t_pwm pwm;


/*******************************************************************************
 * @brief Macros
 ******************************************************************************/

#define PWM_INIT() {                                                           \
	PWM_PIN_DDR = OUTPUT;                                                      \
	PWM_PIN = PWM_INITIAL_STATE;                                               \
	PR2 = PR2_VAL;                                                             \
	CCP1M0 = 0;                                       \// PWM mode = active-high
	CCP1M1 = 0;                                       \// PWM mode = active-high
	CCP1M2 = 1;                                       \// PWM mode = active-high
	CCP1M3 = 1;                                       \// PWM mode = active-high
	CCPR1L = 0x00;                                                             \
	DC1B0 = 0;                                                                 \
	DC1B1 = 0;                                                                 \
	TMR2IF = 0;                                                                \
	T2CKPS0 = TIMER2_CKPS0_VAL;                                    \// Prescaler
	T2CKPS1 = TIMER2_CKPS1_VAL;                                    \// Prescaler
	TMR2ON = 1;                                                                \
}


#endif // __PWM12F16F_H