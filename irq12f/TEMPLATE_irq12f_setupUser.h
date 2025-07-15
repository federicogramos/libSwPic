/*******************************************************************************
 * @file /irq12f_setupUser.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Seteos específicos del proyecto relativo a interrupciones.
 ******************************************************************************/


#ifndef __IRQ12F_SETUP_USER_H
#define __IRQ12F_SETUP_USER_H


/* Configuracion **************************************************************/


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


/* Constants ******************************************************************/


/*******************************************************************************
 * @brief Se setea el tiempo de interrupción (oscilador = OSC_FREQ[Hz], timer<N
 * > prescaler = PS2:PS0 => 2..256). Calculo a realizar:
 * IRQ_TIMER0_RESET_VAL = 256 - Tinterrupt[s] * (fclk[Hz] / [4 * prescaler])
 * Ejemplo (OSC_FREQ = 4MHz, PS = 256) para lograr 2.5ms:
 * IRQ_TIMER0_RESET_VAL = 256 - (2.5E - 3) * (4E6 / [4 * 256]) = 246
 ******************************************************************************/

 #define IRQ_TIMER0_RESET_VAL 246UL


/*******************************************************************************
 * @brief Importantísimo: es indispensable especificar que el numero es UL (unsi
 *  gned long), porque de otro modo, el compilador lo pierde en el camino, y cua
 * ndo lo quiero asignar, solamente asigna un byte, y el resto cero.
 * Se setea el tiempo de interrupcion en 25ms (oscilador interno = 4Mhz, timer1
 * con prescaler = 8). Calculo a realizar:
 * IRQ_TIMER1_RESET_VAL = 65536 - Tinterrupt[s] * (fclk[Hz] / [4 * prescaler])
 * IRQ_TIMER1_RESET_VAL = 65536 - 5E-3 * (4E6 / [4 * 8]) = 64911
 ******************************************************************************/

 #define IRQ_TIMER1_RESET_VAL 34286UL
 

#endif//__IRQ12F_SETUP_USER_H