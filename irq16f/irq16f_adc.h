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

#define IRQ_ADC_ENABLE()		{ ADIE = 1; }
#define IRQ_ADC_DISABLE()		{ ADIE = 0; }
#define IRQ_ADC_RESET_FLAG()	{ ADIF = 0; }
#define IRQ_ADC					ADIE && ADIF


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void isr_adc(void);

