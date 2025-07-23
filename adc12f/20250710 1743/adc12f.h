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
	ANS0 = ANS0_VAL;                                                           \
	ANS1 = ANS1_VAL;                                                           \
	ANS2 = ANS2_VAL;                                                           \
	ANS3 = ANS3_VAL;                                                           \
	CHS0 = CHS0_VAL;                                                           \
	CHS1 = CHS1_VAL;                                                           \
	VCFG = VCFG_VAL;                                                           \
	ADFM = ADFM_VAL;                                                           \
	ADCS0 = ADCS0_VAL;                                                         \
	ADCS1 = ADCS1_VAL;                                                         \
	ADCS2 = ADCS2_VAL;                                                         \
	ADON = ADON_VAL;                                                           \
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