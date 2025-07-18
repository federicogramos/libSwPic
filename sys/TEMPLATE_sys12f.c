/*******************************************************************************
 * @file /system/system_12f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 *
 * Cada proyecto particular tiene su propio archivo "system.c".
 ******************************************************************************/


#include <projectHeader.h>
#include <system_12f.h>
#include <interrupts.h>


/*******************************************************************************
 * @brief
 ******************************************************************************/

void systemInit(void) {
   
	// De todos los periféricos que no se usan y existen en el microcontrolador,
	// el único que arranca en un modo que no es convieniente, es el comparador,
	// por lo que al iniciar, se lo pone en la configuración óptima para deshabi
	// litarlo.
	DISABLE_COMPARATOR();

	IRQ_TIMER1_SETUP(); // Setup interrupt. Timer1 16 bit timer.

	INIT_DDR(); // Establece los puertos de entrada/salida.

	AD_SETUP(); // Va a usar el A/D.

	IRQ_AD_ENABLE(); // Habilita interrupción del A/D.

	IRQ_TIMER1_ENABLE();

	// Timer 1 interrupt entra dentro de las "peripheral interrupts", por lo que
	// debo habilitarlas para que funcione.
	IRQ_PERIPHERAL_ENABLE();

	IRQ_ENABLE(); // Enable all interrupts.

	AD_INIT_CONVERSION(); // Inicia conversiones del ADC.
}

