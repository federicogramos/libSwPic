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

// Ojo, dependiente de la frecuencia de funcionamiento: mejorar o hacerlo config
//urable o poner una tabla con las escalas.
#define DELAY_US(n) {                                                          \
	nCyclesDelay = ((int) (n / 1.084375));                                     \
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