/*******************************************************************************
 * @file /libSwPic/irq12f/irq12f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Maneja las interrupciones (principal).
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

   
