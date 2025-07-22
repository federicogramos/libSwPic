/*******************************************************************************
 * @file /sys/sys12f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 ******************************************************************************/


/*******************************************************************************
 * @brief Debe crearse para cada proyecto en particular.
 ******************************************************************************/

 #include <sys12f_proj.h>


/*******************************************************************************
 * @brief Constants
 ******************************************************************************/

 #define INPUT 1
#define OUTPUT 0


/*******************************************************************************
 * @brief Definiciones para seleccionar funcionalidad de ANSEL (A/D)
 ******************************************************************************/

#define ANALOG_INPUT 1
#define DIGITAL_IO 0


/*******************************************************************************
 * @brief Prototipos
 ******************************************************************************/

void sys12f_init(void);


/*******************************************************************************
 * @brief Macros
 ******************************************************************************/

// Comparator should be set off.
#define DISABLE_COMPARATOR() {                                                 \
	CM0 = 1;                                                                   \
	CM1 = 1;                                                                   \
	CM2 = 1;                                                                   \
}


/*******************************************************************************
 * Si no se va a usar el A/D, esta funcion se debe invocar, ya que por defecto,
 * luego del reset, los puertos de entrada comienzan como entradas analogicas pa
 * ra ser usadas con el A/D, lo cual deshabilita que funcionen como entradas o s
 * alidas digitales.
 * ****************************************************************************/

#define DISABLE_AD() {                                                         \
	ANS0 = DIGITAL_IO;                                                         \
	ANS1 = DIGITAL_IO;                                                         \
	ANS2 = DIGITAL_IO;                                                         \
	ANS3 = DIGITAL_IO;                                                         \
}

/*******************************************************************************
 * Si se va a usar el A/D, esta funcion se debe invocar, para setear la manera e
 * n la que se usara el A/D, cantidad de canales, etc.
 * Solo se usa AN3.
 * El voltaje de referencia es VDD.
 * El resultado se quiere right-justified.
 * Se utiliza el oscilador RC dedicado interno para generar frecuencia de conver
 * sion del AD (frecuencia de conversion maxima = 45KHz).
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
