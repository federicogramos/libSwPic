/*******************************************************************************
 * @file /irq12f_setupUser.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note HW timer. Seteos específicos del proyecto relativo a interrupciones.
 * 
 * Se mantiene esta libreria del timer dentro del ambito de irq porque el timer0
 * es exclusivo para usar con irq, a diferencia del adc que podria ser usado con
 * o sin las interrupciones.
 ******************************************************************************/


#ifndef __IRQ12F_TIMER0_PROJ_H
#define __IRQ12F_TIMER0_PROJ_H


/*******************************************************************************
 * @brief Timer 0.
 *
 * Timer 8 bits. Tiempo maximo @osc 4Mhz = 16.384ms. (675 = 4Mhz, 683 = 8Mhz).
*******************************************************************************/

#define T0CS_VAL	0	// T0CS: TMR0 Clock Source Select bit
						// 1 = Transition on GP2/T0CKI pin
						// 0 = Internal instruction cycle clock (CLKOUT)
#define PSA_VAL		0	// PSA: Prescaler Assignment bit
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


#endif //__IRQ12F_TIMER0_PROJ_H