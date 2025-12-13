//******************************************************************************
// ARCHIVO: x1wDht11.c
// AUTOR: Federico Ramos
// DESCRIPCIo?=N: Librero?=a
// o?=LT. MODIF: 22-01-2020 1749
// COMENTARIO: Librero?=a para comunicacio?=n 1 wire, dedicada exclusivamente para
//			   integrado DHT11.
//             IMPORTANTE, ESTA LIBRERIA DESHABILITA POR PERIODOS DE US A TODAS
//             LAS INTERRUPCIONES
//******************************************************************************


#include <projectHeader.h>
#include <sys.h>
#include <x1wDht11.h>
#include <t0.h>
#include <t0.h>


/*******************************************************************************
 * @brief Macros
 ******************************************************************************/

// TO-DO: por lo que veo, esto no está siendo usado. Evaluar eliminacion.
#define X1W_0 {                                                                \
	X1_WIRE_0_DDR = OUTPUT;                                                    \
	X1_WIRE_0 = 0;                                                             \
}

// TO-DO: por lo que veo, esto no está siendo usado. Evaluar eliminacion.
#define X1W_RELEASE {                                                          \
	X1_WIRE_0_DDR = INPUT;                                                     \
}

#define X1W_DHT11_OUTPUT_ZERO() {                                              \
	X1W_DHT11_PIN_DDR = OUTPUT;                                                \
	X1W_DHT11_PIN = 0;                                                         \
}

#define X1W_INPUT_HI_Z() {                                                     \
	X1W_DHT11_PIN_DDR = INPUT;                                                 \
}


/*******************************************************************************
 * @brief Globals
 *
 * dht11_mem[0] = byte RH [%] integer part
 * dht11_mem[1] = byte RH [%] decimal part = 0 (always)
 * dht11_mem[2] = byte Temp integer part
 * dht11_mem[3] = byte Temp decimal part = 0 (always)
 * dht11_mem[4] = checksum = sum(dht11_mem0..3) = dht11_mem0 + dht11_mem2
 ******************************************************************************/

char dht11_mem[DHT11_RESPONSE_BYTES];


/*******************************************************************************
 * @brief Inicializa lo necesario antes de usar las funciones de esta libreria.
 ******************************************************************************/

void x1wDht11_init(void) {
	dht11_mem[0] = 1;	// Importante inicializacion para q si no hay sensor, no
						// se quede con que el checksum es correcto (0 + 0 = 0).
}


/*******************************************************************************
 * @brief Recibe el paquete completo de la comunicación.
 *
 * Proceso de comunicación segun hoja de datos dht11:
 * 0 -- starting condition is bus = hi.
 * 1 -- uc sends start signal (pulls down voltage for at least 18ms).
 * 2 -- uc will pull up voltage and wait 20-40us for DHT’s response.
 * 3 -- dht Responses to uc (low-voltage-level response signal, for 80us).
 * 4 -- dht pulls up voltage and keeps it for 80us.
 * 5 -- bit start = 0. Dht sends data to uc. Every bit of data begins with 50us 
 *      low-voltage-level.
 * 6 -- bit end = hi. The length of the following high-voltage-level signal dete
 *      rmines whether data bit is "0" (26-28us) or "1" (70us).
 * 
 *                          |<---- 1 bit of data ---->|      |    last   |
 *                                  |<- 26-28us = 0 ->|      |<-- data ->|
 *                                  |<- 70us = 1 ---->|      |    bit    |
 * _____      ____      ____  dht    _________________  ...__      ______
 *      |    |    |    |    | bit   | dht bit         | other|    |      |
 *      |    |    |    |    | start | logic state     | bits |    |      |
 *      |____|    |____|    |_______| = f(width)      |_...  |____|      |_____
 * start 18ms 40us 80us 80us 50us     26..70us                50us        50us
 * bus   uc   uc   dht  dht  dht      dht bit logic                       dht
 * hi         wait resp resp data     state dependent                     end
 * [0]   [1]  [2]  [3]  [4]  [5]
 ******************************************************************************/

char x1wDht11_get(void) {
	char i, j, res;
	char dataBitWidthMeasurement;	// Acumulador para medir el ancho de 1 bit e
									// n el bus de comunicación. Los bits de dat
									// os que da el dht11 tienen valor logico de
									// 0 o 1 dependiendo del ancho.

	// Communication step 1.
	X1W_DHT11_OUTPUT_ZERO();
	DELAY_MS(18);

	// Communication step 2.
	X1W_INPUT_HI_Z();
	DELAY_US(40); // No necesita corrección.. no es tan tan bajo 40us.

	// Communication step 3.
	res = X1W_DHT11_PIN;
	
	if(res == 0) {

		DHT11_WAIT_FP();	// Blocking. El step 3 finaliza cuando dht pulls-up 
							// voltage.

		// Communication step 4. Dht acaba de hacer 0 => 1. Step 4 dura lo que d
		// ht mantiene data = 1.
		DHT11_WAIT_FN();	// Blocking. Luego de esto, comienza transmision de 
							// datos.

		// Communication step 5: ahora data = 0 durante 50us.

		//TO-DO: creo que esto esta al pepe, porque adentro del loop ya hago el 
		// mini "habilito deshabilito".
		// Deshabilita todas las interrupciones porque:
		// -- los tiempos son justos, no quiero que me agarre dentro de una inte
		//    rrupción cuando haga el flanco positivo (q señala q debo comenzar 
		//    a medir el tiempo).
		// -- por el momento, por como está implementado, no le da el tiempo par
		//    a atenderlas y al mismo tiempo reconocer el estado logico segun 26
		//    us vs 70us.
		#if	defined(_12F683) // Compilacion condicional.
			GIE = 0;
		#else
			INTCONbits.GIE = 0;
		#endif

		for(i = 0; i < DHT11_RESPONSE_BYTES; i++) {
			dht11_mem[i] = 0;
			for(j = 0; j < 8; j++) {
				dataBitWidthMeasurement = 0;

				// -- Cuidado: tengo 50us para atender interrupciones. Si me pas
				// o, se jode todo.
				// -- Deshabilita todas las interrupciones porque por el momento
				// por como está implementado, no le da el tiempo para atenderla
				// s y al mismo tiempo reconocer el estado logico segun 26us vs 
				// 70us.
				#if	defined(_12F683) // Compilacion condicional.
					GIE = 1;
					GIE = 0;
				#else
					INTCONbits.GIE = 1;
					INTCONbits.GIE = 0;
				#endif

				// Step 6: busco el momento en el que 0 -> 1 para comenzar a med
				// ir el ancho de pulso que me dará el valor lógico del bit.
				DHT11_WAIT_FP();

				do {
					//DELAY_US(10.5);
					DELAY_US(DELAY_US_N_CORRECTION(10));
					dataBitWidthMeasurement++;
				} while(X1W_DHT11_PIN == 1);
	
				if(dataBitWidthMeasurement > 3) dht11_mem[i] |= (0x80 >> j);
			}
		}

		#if	defined(_12F683)
			GIE = 1;
		#else
			INTCONbits.GIE = 1;
		#endif
	}
	return res;
}

