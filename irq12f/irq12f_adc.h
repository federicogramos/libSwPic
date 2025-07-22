/*******************************************************************************
 * @file /libSwPic/irq12f/irq12f_adc.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones (adc).
 ******************************************************************************/


#include <irq12f_adc_proj.h>


/*******************************************************************************
 * @brief Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
 ******************************************************************************/

#define IRQ_ADC_ENABLE()			{ ADIE = 1; }
#define IRQ_ADC_DISABLE()			{ ADIE = 0; }
#define IRQ_ADC_RESET_FLAG()		{ ADIF = 0; }
 #define IRQ_ADC					ADIE && ADIF


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
 * @brief Prototipos
 ******************************************************************************/

void isr_adc(void);

