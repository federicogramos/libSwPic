/*******************************************************************************
 * @file /libSwPic/irq12f/irq12f_timer0.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones (timer0)
 ******************************************************************************/


#include <irq12f_timer0_proj.h>


/*******************************************************************************
 * @brief Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
 ******************************************************************************/

#define IRQ_TIMER0_ENABLE()			{ T0IE = 1; }
#define IRQ_TIMER0_DISABLE()		{ T0IE = 0; }
#define IRQ_TIMER0_RESET_FLAG()		{ T0IF = 0; }
#define IRQ_TIMER0					T0IE && T0IF


/*******************************************************************************
 * @brief Asigna un valor al acumulador del timer0.
 * If TMR0 is written, the increment is inhibited for the following two
 * instruction cycles. The user can work around this by writing an adjusted
 * value to the TMR0 register.
 ******************************************************************************/

#define IRQ_TIMER0_SET(value)		{ TMR0 = value; }



/*******************************************************************************
 * @brief Configura al timer0.
 ******************************************************************************/

 #define IRQ_TIMER0_SETUP() {                                                  \
    PSA = PSA_VAL;                                                             \
    T0CS = T0CS_VAL;                                                           \
    PS0 = PS0_VAL;                                                             \
    PS1 = PS1_VAL;                                                             \
    PS2 = PS2_VAL;                                                             \
    IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);                                      \
}


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void isr_timer0(void);
