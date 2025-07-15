/*******************************************************************************
 * @file /irq12f.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones.
 *
 * Es un template porque cada proyecto debe implementar su isr. Lo que si puede
 * incluir de la libreria es el irq12f.h el cual tiene las definiciones requerid
 * as para los perifericos.
 ******************************************************************************/


#include <projectHeader.h>
#include <irq12f.h>
#include <adc12f.h>
#include <timer.h> // Timers por software.
#include <sys12f.h> // Definicion de puertos de entrada/salida.
//#include <pulsadorPin.h>


/*******************************************************************************
 * @brief Cuando se produce una interrupcion, siempre se llama a la misma funcio
 * n (esta). Dentro de esta rutina es donde se tiene que fijar viendo los flags 
 * de interrupcion, cual fue el que causo la llamada.
 ******************************************************************************/

 void interrupt isr(void) {
    if(IRQ_TIMER1) isr_timer1();
    else if(IRQ_TIMER0) isr_timer0();
	if(IRQ_ADC) isr_adc();
}

   
/*******************************************************************************
 * @brief
 ******************************************************************************/

 void isr_timer1(void) {
    IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);// Reseteo del contador de la interrupci�n.
    timerDriver(TMR_STARTUP);
    timerDriver(TMR_RELAY);
    IRQ_TIMER1_RESET_FLAG();
}

   
/*******************************************************************************
 * @brief
 ******************************************************************************/

void isr_timer0(void) {
    IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);
    IRQ_TIMER0_RESET_FLAG();
}


/*******************************************************************************
 * @brief
 ******************************************************************************/

void isr_adc() {
	AD_INIT_CONVERSION() // Comienza una nueva conversisn, para que las conversiones sean perisdicas.
	adc12f_driver();
	IRQ_ADC_RESET_FLAG()
}
