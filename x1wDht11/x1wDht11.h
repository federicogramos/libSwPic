/*******************************************************************************
 * @file x1wDht11.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251212 1723
 * @note Para lib manejo dht11.
 ******************************************************************************/


#ifndef __X1W_DHT11_H
#define __X1W_DHT11_H


#include <x1wDht11_settings.h>


/*******************************************************************************
 * @brief Constants
 ******************************************************************************/

int nCyclesDelay; // Delay aprox 0.5us por cada unidad de delay.


/*******************************************************************************
 * @brief Constants
 ******************************************************************************/

#define DHT11_RESPONSE_BYTES 5
#define DELAY_MS_PROPORTIONAL_CONSTANT 4595
#define DELAY_US_OFFSET_TIME 2	// Si o si tiene que ser entero para que sea met
								// ido en valor calculado en DELAY_US_N_CORRECTI
								// ON() en tiempo de compilacion.
#define DELAY_US_PROPORTIONAL_CONSTANT 4.595
//#define DELAY_US_PROPORTIONAL_CONSTANT 1.0 // Just for calibration.

/*******************************************************************************
 * @brief External declarations
 ******************************************************************************/

extern char dht11_mem[DHT11_RESPONSE_BYTES];


/*******************************************************************************
 * @brief Macros
 ******************************************************************************/

#define DHT11_WAIT_FP() while(X1W_DHT11_PIN == 0);
#define DHT11_WAIT_FN() while(X1W_DHT11_PIN == 1);

// Checksum es la suma de los 4 bytes enviados, pero como el dht11 tiene las par
// tes decimales = 0, entonces estas suman 0. Es el dht22 (creo) que envia los 4
// bytes útiles.
#define DHT_XX_CHECKSUM() (dht11_mem[0] + dht11_mem[2] == dht11_mem[4])


/*******************************************************************************
 * @brief Delay us. Hay un valor minimo de argumento minimo para q tiempo ok.
 * Cuidado: n > DELAY_US_PROPORTIONAL_CONSTANT
 * Cuidado si se usa DELAY_US_N_CORRECTION() porque puede resultar el calculo un
 * nro negativo.
 * 
 * Formula real para pic12f683 @ fclk = 8Mhz:
 * DELAY_US(n) = 1.92us + 4.28us * n
 * 
 * Ojo, dependiente de la frecuencia de funcionamiento: mejorar o hacerlo config
 * urable o poner una tabla con las escalas.
 * 
 * Mediciones realizadas el 12-12-2025 para calibrarlo. Lo mejor es tomar 2 tand
 * as: una con n bajo para el tFixed y otra con n grande para el proporcional.
 * -- pic12f683 @ fclk = 8Mhz
 * -- DELAY_US_PROPORTIONAL_CONSTANT = 1.0
 * -- DELAY_US(1) = 6.2us
 * -- DELAY_US(2) = 10.48us
 * -- DELAY_US(3) = 14.96us
 * 
 * Calculos:
 * -- tStep = 4.28us
 * -- tFixed = 1.92us (DELAY_US_OFFSET_TIME)
 * 
 * Tabla para bajos valores de n, y luego cuando 1.92us * n >> 1.92us el tFixed 
 * se hace despreciable.
 * 
 * -- pic12f683 @ fclk = 8Mhz
 * -- DELAY_US_PROPORTIONAL_CONSTANT = 1.0
 * -- DELAY_US(1000) = 4595us
 * Se corrige la constante (despreciando el tiempo de asignación en el ciclo):
 * 4595 [us] = 1000 / DELAY_US_PROPORTIONAL_CONSTANT
 * DELAY_US_PROPORTIONAL_CONSTANT = 4595 / 1000 = 4.595
 * Con esta calibración, he medido DELAY_US(1000) = 997.0us
 * 
 * Rutina usada para calibrar (deshabilitar irq, que no molesten). La diferencia
 *  entre ambos pulsos+ indica el tiempo proporcional de cada incremento de n.
 * 
 * 	while(1) {
 *		FLAG_START_COMM = 1;
 *		DELAY_US(1); // time1
 *		FLAG_START_COMM = 0;
 *		DELAY_US(1);
 *
 *		FLAG_START_COMM = 1;
 *		DELAY_US(2); // time2
 *		FLAG_START_COMM = 0;
 *		DELAY_US(2);
 *	}
 *
 * time2 - time1 = step
 * time1- step = timeFixed donde timeFixed es lo que la macro tarda en hacer cal
 * culo de n / DELAY_US_PROPORTIONAL_CONSTANT tiempo q no se puede eliminar.
 */

#define DELAY_US(n) {                                                          \
	nCyclesDelay = ((int) (n / DELAY_US_PROPORTIONAL_CONSTANT));               \
	while(--nCyclesDelay);                                                     \
	}

#define DELAY_US_N_CORRECTION(n) (n - DELAY_US_OFFSET_TIME)


/*******************************************************************************
 * @brief Delay ms
 * 
 * Basicamente igual que us pero con otra CALIBRATE_CONSTANT que ya desprecia el
 * tFixed.
 ******************************************************************************/

#define DELAY_MS(n) {                                                          \
	nCyclesDelay = ((int) (n / DELAY_MS_PROPORTIONAL_CONSTANT));               \
	while(--nCyclesDelay);                                                     \
	}


//******************************************************************************
//PARA DS18B20
//
// TO-DO: esto eliminarlo.
//******************************************************************************

///////////////////////////////////////////////////#define X1W_DS18B20_SKIP 0xCC
////////////////////////////////////////////////#define X1W_DS18B20_CONVERT 0x44
///////////////////////////////////////////////#define X1W_DS18B20_READTEMP 0xBE


//******************************************************************************
//DEFINICION DE USUARIOS
//******************************************************************************
/////////////////////////////////volatile bit X1_WIRE_0 @ ((unsigned)&GPIO*8)+5;
/////////////////////////////volatile bit X1_WIRE_0_DDR @ ((unsigned)&GPIO*8)+5;
////////////////////////////volatile bit X1W_DHT11_PIN @ ((unsigned)&PORTA*8)+3;
////////////////////////volatile bit X1W_DHT11_PIN_DDR @ ((unsigned)&TRISA*8)+3;

/////////////////////////////////volatile bit X1_WIRE_0 @ ((unsigned)&GPIO*8)+5;
///////////////////////////volatile bit X1_WIRE_0_DDR @ ((unsigned)&TRISIO*8)+5;

////////////////////////////////////////////////////////#define X1_WIRE_BUFLEN 8


char x1wDht11_get(void);
void x1wDht11_init(void);


#endif // __X1W_DHT11_H