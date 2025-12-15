/*******************************************************************************
 * @file kPin.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251525 1421
 * @note Uso de pines como pulsadores con debouncing. kPin = key-pin.
 ******************************************************************************/


#include <project.h>
#include <kPin.h>


/*******************************************************************************
 * @brief Globals
 ******************************************************************************/

t_kEvent kPinBuffer;


/*******************************************************************************
 * @brief Maneja un pin: pulsador conectado a dc.
 * @param char pi = kPinAlias. Constante que toma valores de 0..(K_PIN_CANT-1). 
 * Normalmente se invocará utilizando el nombre del pulsador (segun definicion k
 * Pin_aliases.h/e_kPinAlias).
 * @param char kCurrLogState = K_i
 ******************************************************************************/

void kPin_driverDc(char pi, char kCurrLogState) {
	if(kPin[pi].timer) kPin[pi].timer--;
	else {
		kPin[pi].state = kCurrLogState;

		if(kPin[pi].state == FLANCO_P && kPin[pi].prevState ==! FLANCO_P) {
			kPinBuffer.flag = 1;
			kPinBuffer.flanco = FLANCO_P;
			kPin[pi].timer = KPIN__N_ANTIREBOTE;// Importantisimo: estos siguien
			// tes 2 renglones, si bien son comunes a ambos, no se deben sacar c
			// omo factor com�n porque si lo hago y uso kPinBuffer.flag para dis
			// tinguirlos, se confunde el driver en el momento en que aprietan o
			// tro boton (kPinBuffer.flag accionado por otro) y entonces funcion
			// a mal (mucho tiempo para darme cuenta).
			kPinBuffer.kId = pi;
		}
		else if(kPin[pi].state==FLANCO_N && kPin[pi].prevState==!FLANCO_N) {
			kPinBuffer.flag = 1;
			kPinBuffer.flanco = FLANCO_N;
			kPin[pi].timer = KPIN__N_ANTIREBOTE;
			kPinBuffer.kId = pi;
		}

		kPin[pi].prevState = kPin[pi].state;
	}
}


/*******************************************************************************
 * @brief Maneja un pin. Version compatible con AC/DC. Para flanco negativo.
 * @param char pi = kPinAlias. Constante que toma valores de 0..(K_PIN_CANT-1). 
 * Normalmente se invocará utilizando el nombre del pulsador (segun definicion k
 * Pin_aliases.h/e_kPinAlias).
 * @param char flanco.
 * @param char kCurrLogState = K_i
 ******************************************************************************/

void kPin_driverAcFn(char pi, char flanco, char kCurrLogState) {
	if(kPin[pi].timer) {
		kPin[pi].timer--;
		kPin[pi].state=kCurrLogState;
		if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
		kPin[pi].prevState=kPin[pi].state;
	}
	else {
		kPin[pi].state=kCurrLogState;
		if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) {
			kPin[pi].timer=KPIN__N_ANTIREBOTE;
			kPinBuffer.kId=pi;
			kPinBuffer.flag=1;
		}
		kPin[pi].prevState=kPin[pi].state;
	}
}


/*******************************************************************************
 * @brief Maneja un pin. Version compatible con AC/DC. Para flanco positivo.
 * @param char pi = kPinAlias. Constante que toma valores de 0..(K_PIN_CANT-1). 
 * Normalmente se invocará utilizando el nombre del pulsador (segun definicion k
 * Pin_aliases.h/e_kPinAlias).
 * @param char flanco.
 * @param char kCurrLogState = K_i
 ******************************************************************************/

void kPin_driverAcFp(char pi, char flanco, char kCurrLogState) {
	if(kPin[pi].timer) {
		kPin[pi].timer--;
		if(kPin[pi].timer==0) kPinBuffer.flag=1;//FGR:SETEA EL FLAG AL FINAL DEL ANTIREBOTE PARA COMPATIBILIZAR CON 220V
		kPin[pi].state=kCurrLogState;
		if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
		kPin[pi].prevState=kPin[pi].state;
	}
	else {
		kPin[pi].state=kCurrLogState;
		if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) {
			kPin[pi].timer=KPIN__N_ANTIREBOTE;
			kPinBuffer.kId=pi;
		}
		kPin[pi].prevState=kPin[pi].state;
	}
}

