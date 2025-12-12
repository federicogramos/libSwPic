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


//******************************************************************************
// ARCHIVOS DE ENCABEZAMIENTO
#include <projectHeader.h>
#include <sys.h>
#include <x1wDht11.h>
#include <t0.h>
#include <t0.h>
//******************************************************************************





#define X1W_0\
	{\
	X1_WIRE_0_DDR=OUTPUT;\
	X1_WIRE_0=0;\
	}


#define X1W_RELEASE X1_WIRE_0_DDR=INPUT;



//******************************************************************************
// MACROS
//******************************************************************************
#define X1W_DHT11_OUTPUT_ZERO()\
	{\
	X1W_DHT11_PIN_DDR=OUTPUT;\
	X1W_DHT11_PIN=0;\
	}


#define X1W_INPUT_HI_Z()\
	{\
	X1W_DHT11_PIN_DDR=INPUT;\
	}


//******************************************************************************
// DEFINICIo?=N DE VARIABLES
// dht11_mem[0] = byte %RH integer part
// dht11_mem[1] = byte %RH decimal part = 0 (always)
// dht11_mem[2] = byte Temp integer part
// dht11_mem[3] = byte Temp decimal part
// dht11_mem[4] = checksum
//******************************************************************************

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
 ******************************************************************************/

char x1wDht11_get(void)
    {
    char i,j,res,pulseTicks;

    X1W_DHT11_OUTPUT_ZERO();
    DELAY_US(18000);//FGR:tRSTL=480us UC ENVIA PULSO RESET
    X1W_INPUT_HI_Z();
    DELAY_US(40);//tPDHIGH=15-60us

    res=X1W_DHT11_PIN;
    
    if(res==0)
        {
        DHT11_WAIT_FP();
        DHT11_WAIT_FN();//luego de esto, empieza transmision de datos

		#if	defined(_12F683)// FGR: COMPILACION CONDICIONAL
			GIE=0;
		#else
			INTCONbits.GIE=0;
		#endif// FGR: COMPILACION CONDICIONAL

        for(i=0;i<DHT11_RESPONSE_BYTES;i++)
            {
            dht11_mem[i]=0;
            for(j=0;j<8;j++)
                {
                pulseTicks=0;

				#if	defined(_12F683)// FGR: COMPILACION CONDICIONAL
					GIE=1;
					GIE=0;
				#else
					INTCONbits.GIE=1;
					INTCONbits.GIE=0;
				#endif// FGR: COMPILACION CONDICIONAL

                DHT11_WAIT_FP();

                do  {
                    DELAY_US(10.5);
                    pulseTicks++;
                    } while(X1W_DHT11_PIN==1);
    
                if(pulseTicks>3)//bit=1 // porque puede quedar un ultimo tick afuera de la forma de onda
                    dht11_mem[i]|=(0x80>>j);
                }
            }

		#if	defined(_12F683)
			GIE=1;
		#else
			INTCONbits.GIE=1;
		#endif
        }
    return res;
    }

