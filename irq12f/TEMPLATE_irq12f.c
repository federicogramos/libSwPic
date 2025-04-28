// Es un template porque cada proyecto debe implementar su isr. Lo que si puede
// incluir de la libreria es el irq12f.h el cual tiene las definiciones requerid
// as para los perifericos.

/**
 * @file /libSwPic/irq12f/irq12f.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 */


#include <projectHeader.h>
#include <irq12f.h>
#include <timer.h>// Necesario porque dentro de una interrupci�n estoy implemen
// tando un timer por software.
#include <system.h>// Necesario porque contiene la definici�n de los puertos de
// entrada/salida.
//#include <pulsadorPin.h>
//#include <adc.h>


/**
 * @brief
 */
void interrupt isr(void)
    {
    if(IRQ_TIMER1) isr_timer1();
    else if(IRQ_TIMER0) isr_timer0();
    }

   
/**
 * @brief Timer fijo = 250ms
 */
void isr_timer1(void)
    {
    IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);// Reseteo del contador de la interrupci�n.
    timerDriver(TMR_STARTUP);
    timerDriver(TMR_RELAY);
    IRQ_TIMER1_RESET_FLAG();
    }

   
/**
 * @brief Timer fijo = 1ms
 */
void isr_timer0(void)
    {
    IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);
    IRQ_TIMER0_RESET_FLAG();
    }

