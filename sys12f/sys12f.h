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
