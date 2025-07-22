/*******************************************************************************
 * @file /libSwPic/irq12f/irq12f_timer1.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones (timer1).
 ******************************************************************************/

#ifndef __IRQ12F_TIMER1_H
#define __IRQ12F_TIMER1_H


#include <irq12f_timer1_proj.h>


/*******************************************************************************
 * @brief Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
 ******************************************************************************/

#define IRQ_TIMER1_ENABLE()			{ TMR1IE = 1; }
#define IRQ_TIMER1_DISABLE()		{ TMR1IE = 0; }
#define IRQ_TIMER1_RESET_FLAG()		{ TMR1IF = 0; }
#define IRQ_TIMER1					TMR1IE && TMR1IF


/*******************************************************************************
 * @brief Asigna un valor al acumulador del timer1.
 ******************************************************************************/

#define IRQ_TIMER1_SET(value) {                                                \
    TMR1L = GET_NUM_BYTE(0, value);                                            \
    TMR1H = GET_NUM_BYTE(1, value);                                            \
}


/*******************************************************************************
 * @brief Configura al timer1.
 ******************************************************************************/

 #define IRQ_TIMER1_SETUP() {                                                  \
    TMR1CS = TMR1CS_VAL;                                                       \
    T1SYNC = T1SYNC_VAL;                                                       \
    T1OSCEN = T1OSCEN_VAL;                                                     \
    T1CKPS0 = T1CKPS0_VAL;                                                     \
    T1CKPS1 = T1CKPS1_VAL;                                                     \
    TMR1ON = TMR1ON_VAL;                                                       \
    IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);                                      \
}


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void isr_timer1(void);


#endif // __IRQ12F_TIMER1_H