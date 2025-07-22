/*******************************************************************************
 * @file /adc16f/adc16f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250710 1747
 ******************************************************************************/


#ifndef __ADC12F_H
#define __ADC12F_H


 #include <adc12f_proj.h> // Local a proyecto especifico. Debe ser configurado.


/*******************************************************************************
 * @brief Constants
 ******************************************************************************/

#define ADC12F_MAX 1023
#define ADC12F_MIN 0


/*******************************************************************************
 * @brief Globals
 ******************************************************************************/

extern int adc12f_val;


/*******************************************************************************
 * @brief Macros
*******************************************************************************/

#define IRQ_ADC_ENABLE()		{ ADIE = 1; }
#define IRQ_ADC_DISABLE()		{ ADIE = 0; }
#define IRQ_ADC_RESET_FLAG()	{ ADIF = 0; }
#define IRQ_ADC					ADIE && ADIF


/*******************************************************************************
 * Si se va a usar el A/D, esta funcion se debe invocar, para setear la manera e
 * n la que se usara el A/D, cantidad de canales, etc.
 * -- solo se usa AN3.
 * -- el voltaje de referencia es VDD.
 * -- el resultado se quiere right-justified.
 * -- se utiliza el oscilador RC dedicado interno para generar frecuencia de con
 *    version del AD (frecuencia de conversion maxima = 45KHz).
 ******************************************************************************/

#define AD_SETUP() {                                                           \
	ANS0 = DIGITAL_IO;                                                         \
	ANS1 = DIGITAL_IO;                                                         \
	ANS2 = DIGITAL_IO;                                                         \
	ANS3 = ANALOG_INPUT;                                                       \
	CHS0 = 1;                                                                  \
	CHS1 = 1;                                                                  \
	VCFG = 0;                                                                  \
	ADFM = 1;                                                                  \
	ADCS0 = 1;                                                                 \
	ADCS1 = 1;                                                                 \
	ADCS2 = 1;                                                                 \
	ADON = 1;                                                                  \
}


/*******************************************************************************
 * Inicia conversion del A/D. Si voy a usar el AD mediante interrupciones, porqu
 * e quiero que automaticamente me llame la rutina de interrupcion cada vez que 
 * hay una conversion nueva, al menos 1 vez al principio del booteo del programa 
 * debo llamar a esta macro, porque si no, nunca va a conmenzar a convertir el A
 * DC.
 ******************************************************************************/

#define AD_INIT_CONVERSION() { GODONE = 1; }


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void adc12f_driver(void);
void isr_adc(void);


#endif // __ADC12F_H