/*******************************************************************************
 * @file /irq12f_setupUser.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Seteos específicos del proyecto relativo a interrupciones.
 ******************************************************************************/


#ifndef __IRQ12F_SETUP_USER_H
#define __IRQ12F_SETUP_USER_H


/*******************************************************************************
 * @brief Timer 0.
 *
 * Timer 8 bits. Tiempo maximo @osc 4Mhz = 16.384ms.
*******************************************************************************/

#define T0CS_VAL	0	// T0CS: TMR0 Clock Source Select bit
						// 1 = Transition on GP2/T0CKI pin
						// 0 = Internal instruction cycle clock (CLKOUT)
#define PSA_VAL		1	// PSA: Prescaler Assignment bit
						// 1 = Prescaler is assigned to the WDT
						// 0 = Prescaler is assigned to the TIMER0 module
#define PS0_VAL 	1	// PS2:PS0: Prescaler Rate Select bits
#define PS1_VAL 	1	// Value | TMR0 rate | WDT rate
#define PS2_VAL 	1	// 000   | 1 : 2     | 1 : 1
						// 001   | 1 : 4     | 1 : 2
						// 010   | 1 : 8     | 1 : 4
						// 011   | 1 : 16    | 1 : 8
						// 100   | 1 : 32    | 1 : 16
						// 101   | 1 : 64    | 1 : 32
						// 110   | 1 : 128   | 1 : 64
						// 111   | 1 : 256   | 1 : 128

// T0SE no usado. El flanco del pin T0CKI no tiene uso, ya que no estoy usando d
// icho pin como generador de los pulsos para el timer0.
// INTEDG Ignorado por no tener relacion con el timer0.
// GPPU Ignorado por no tener relacion con el timer0.

// Se setea el tiempo de interrupción (oscilador = OSC_FREQ[Hz], timer<N> presca
// ler = PS2:PS0 => 2..256). Calculo a realizar:
// IRQ_TIMER0_RESET_VAL = 256 - Tinterrupt[s] * (fclk[Hz] / [4 * prescaler])
// Ejemplo (OSC_FREQ = 4MHz, PS = 256) para lograr 2.5ms:
// IRQ_TIMER0_RESET_VAL = 256 - (2.5E - 3) * (4E6 / [4 * 256]) = 246
// Importantísimo: es indispensable especificar que el numero es UL (unsigned lo
// ng), porque de otro modo, el compilador lo pierde en el camino, y cuando lo q
// uiero asignar, solamente asigna un byte, y el resto cero.
  #define IRQ_TIMER0_RESET_VAL 246UL

 
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
 

#endif//__IRQ12F_SETUP_USER_H