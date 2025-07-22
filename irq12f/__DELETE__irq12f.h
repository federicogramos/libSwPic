/*******************************************************************************
 * @file /libSwPic/irq12f/irq12f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones.
 ******************************************************************************/


#include <irq12f_setupUser.h>


/*******************************************************************************
 * @brief
 ******************************************************************************/

#define IRQ_ENABLE()				{ GIE = 1; }
#define IRQ_DISABLE()				{ GIE = 0; }


/*******************************************************************************
 * @brief Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
 ******************************************************************************/

#define IRQ_PERIPHERAL_ENABLE()		{ PEIE = 1; }
#define IRQ_PERIPHERAL_DISABLE()	{ PEIE = 0; }

   
#define IRQ_ADC_ENABLE()			{ ADIE = 1; }
#define IRQ_ADC_DISABLE()			{ ADIE = 0; }

#define IRQ_TIMER0_ENABLE()			{ T0IE = 1; }
#define IRQ_TIMER0_DISABLE()		{ T0IE = 0; }

#define IRQ_TIMER1_ENABLE()			{ TMR1IE = 1; }
#define IRQ_TIMER1_DISABLE()		{ TMR1IE = 0; }

#define IRQ_TIMER0_RESET_FLAG()		{ T0IF = 0; }
#define IRQ_TIMER1_RESET_FLAG()		{ TMR1IF = 0; }
#define IRQ_ADC_RESET_FLAG()		{ ADIF = 0; }


/*******************************************************************************
 * @brief Asigna un valor al acumulador del timer0.
 * If TMR0 is written, the increment is inhibited for the following two
 * instruction cycles. The user can work around this by writing an adjusted
 * value to the TMR0 register.
 ******************************************************************************/

#define IRQ_TIMER0_SET(value)		{ TMR0 = value; }


/*******************************************************************************
 * @brief Asigna un valor al acumulador del timer1.
 ******************************************************************************/

#define HIGH_BYTE(x) ((unsigned char)(x >> 8))
#define LOW_BYTE(x) ((unsigned char)(x & 0xFF))

#define IRQ_TIMER1_SET(value) {                                                \
    TMR1L = GET_NUM_BYTE(0, value);                                            \
    TMR1H = GET_NUM_BYTE(1, value);                                            \
}


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


// El 887 no necesita port configuration (mucho mejor)
//                      PCFG0=0; \
//                      PCFG1=1; \
//                      PCFG2=0; \
//                      PCFG3=0; \

//                      ADCS2=1; \ Solo se usa para 87X version A

//
//ADCS=Fosc/64 
//PCFG=AN0..4->analog / AN5..7->digital


/*******************************************************************************
 * @brief Timer0 interrupt enable and flag set.
 ******************************************************************************/

 #define IRQ_TIMER0 T0IE && T0IF


/*******************************************************************************
 * @brief Timer1 interrupt enable and flag set.
 ******************************************************************************/

 #define IRQ_TIMER1 TMR1IE && TMR1IF


/*******************************************************************************
 * @brief ADC
 ******************************************************************************/

 #define IRQ_ADC ADIE && ADIF


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void isr_timer0(void);
void isr_timer1(void);
void isr_adc(void);

