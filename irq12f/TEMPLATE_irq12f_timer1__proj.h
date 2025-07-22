/*******************************************************************************
 * @file /irq12f_setupUser.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Seteos específicos del proyecto relativo a interrupciones  (timer1).
 ******************************************************************************/


#ifndef __IRQ12F_TIMER1_PROJ_H
#define __IRQ12F_TIMER1_PROJ_H


/*******************************************************************************
 * @brief Timer 1
 * 
 * Timer 16 bits.  Tiempo maximo @osc 4Mhz = 
 * -- el oscilador interno fosc/4 es quien incremente timer1
 ******************************************************************************/

#define TMR1ON_VAL	1;	// Entrada de pulsos del contador habilitada. En 1 para que
					// llegue el timer.
#define TMR1CS_VAL	0;	// TMR1CS: Timer1 Clock Source Select bit.
					// 1 = External clock from T1OSO/T1CKI pin (on rising edge)
					// 0 = Internal clock (FOSC/4)

#define T1SYNC_VAL	1;	// Se usa el clock interno, por lo que este bit es ignorado,
					// ya que no tiene sentido sincronizar el clock consigo mism
					// o. Tampoco es indispensable cuando se usa el clock extern
					// o (creo).
					// T1SYNC: Timer1 External Clock Input Sync Control bit.
					// TMR1CS = 1:
					// 1 = Do not synchronize external clock input
					// 0 = Synchronize external clock input

#define T1OSCEN_VAL	0;	// T1OSCEN: LP Oscillator Enable Control bit. LP osc (XTAL) 
					// no se habilita para el timer 1.
					// If (INTOSC without CLKOUT oscillator is active) {
					// 		1 = LP oscillator is enabled for Timer1 clock
					// 		0 = LP oscillator is off
					// }
					// else {
					// 		this bit is ignored
					// }

#define T1CKPS0_VAL	1	// Value | TMR1 rate
#define T1CKPS1_VAL	1	// 00    | 1 : 1
						// 01    | 1 : 2
						// 10    | 1 : 4
						// 11    | 1 : 8

 // Setea el tiempo de interrupcion. Calculo a realizar:
 // IRQ_TIMER1_RESET_VAL = 65536 - Tinterrupt[s] * (fclk[Hz] / [4 * prescaler])
 // Ejemplo para obtener 250ms:
 // IRQ_TIMER1_RESET_VAL = 65536 - 250E-3 * (4E6 / [4 * 8]) = 34286
#define IRQ_TIMER1_RESET_VAL 34286UL
 

#endif // __IRQ12F_TIMER1_PROJ_H