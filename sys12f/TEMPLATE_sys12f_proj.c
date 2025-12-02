/*******************************************************************************
 * @file /system/sys12f_proj.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 * @note Cada proyecto particular tiene su propio archivo "system.c".
 ******************************************************************************/


#include <project.h>
#include <sys12f.h>			// Puertos en <proj>/sys12f_proj.h

#include <irq12f.h>			// Main definition.
#include <irq12f_timer1.h>	// Accesoria,si se usa.

#include <adc12f.h>			// Accesoria,si se usa.


/*******************************************************************************
 * @brief
 ******************************************************************************/

void sys12f_init(void) {
   
	// De todos los periféricos que no se usan y existen en el microcontrolador,
	// el único que arranca en un modo que no es convieniente, es el comparador,
	// por lo que al iniciar, se lo pone en la configuración óptima para deshabi
	// litarlo.
	DISABLE_COMPARATOR();

	INIT_DDR(); // Establece los puertos de entrada/salida.

	INIT_PORTS();// Al arranque, pone en un estado conocido a las salidas.

	IRQ_TIMER1_SETUP(); // Setup interrupt. Timer1 16 bit timer.

	AD_SETUP(); // Va a usar el A/D.

	IRQ_AD_ENABLE(); // Habilita interrupción del A/D.

	IRQ_TIMER1_ENABLE();

	// Timer 1 interrupt entra dentro de las "peripheral interrupts", por lo que
	// debo habilitarlas para que funcione.
	IRQ_PERIPHERAL_ENABLE();

	IRQ_ENABLE(); // Enable all interrupts.

	AD_INIT_CONVERSION(); // Inicia conversiones del ADC.
}

