/*******************************************************************************
 * @file kPin.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251525 1421
 * @note Uso de pines como pulsadores con debouncing. kPin = key-pin.
 ******************************************************************************/


#ifndef __K_PIN_H
#define __K_PIN_H


/*******************************************************************************
 * @brief Files user must define.
 ******************************************************************************/

 #include <kPin_aliases.h> // Nombres de pulsadores por parte del usuario.

 
/*******************************************************************************
 * @brief Structures
 * 
 * No permite hacer arreglos de bitfields, por eso debo hacer estructura de bitf
 * ield y luego un arreglo de esa estructura.
 ******************************************************************************/

typedef struct {
	unsigned char kId		: 5;
	unsigned char flag		: 1;
	unsigned char flanco	: 1; // Driver escribe el tipo de flanco ocurrido.
	} t_kEvent;

typedef struct {
	unsigned char state		: 1;
	unsigned char prevState	: 1;
	unsigned char timer;
	} t_kPin;


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////// TO-DO, esto acomodar:

#include <kPin_pindef.h> // Pindef e inicialización de vector.


/*******************************************************************************
 * @brief Constant definitions
 ******************************************************************************/

enum e_flanco { FLANCO_N, FLANCO_P };


/*******************************************************************************
 * @brief Extern references
 ******************************************************************************/

extern t_kEvent kPinBuffer;


/*******************************************************************************
 * @brief Macros
 ******************************************************************************/

// Si ocurrió evento en un algun key (cualquiera de todos).
#define KPIN_EVENT() 		(kPinBuffer.flag? !(kPinBuffer.flag = 0) : 0)

// Para el evento actual ocurrido, retorna el id del key.
 #define KPIN_GET_ID() 		(kPinBuffer.kId)

// Si ocurrió evento en un key específico (indicado).
#define KPIN_EVENT_ID(i)	(  kPinBuffer.flag                                 \
							&& kPinBuffer.kId == i? !(kPinBuffer.flag = 0) : 0)

// Si ocurrió evento de flanco positivo en un key específico (indicado).
#define KPIN_EVENT_FP_ID(i)	(  kPinBuffer.flag                                 \
							&& kPinBuffer.flanco == FLANCO_P                   \
							&& kPinBuffer.kId == i? !(kPinBuffer.flag = 0) : 0)

// Si ocurrió evento de flanco negativo en un key específico (indicado).
#define KPIN_EVENT_FN_ID(i)	(kPinBuffer.flag                                   \
							&& kPinBuffer.flanco == FLANCO_N                   \
							&& kPinBuffer.kId == i? !(kPinBuffer.flag = 0) : 0)


/*******************************************************************************
 * @brief Function prototypes
 ******************************************************************************/

void kPin_driverDc(char pi, char kCurrLogState);
void kPin_driverAcFn(char pi, char flanco, char kCurrLogState);
void kPin_driverAcFp(char pi, char flanco, char kCurrLogState);


#endif // __K_PIN_H