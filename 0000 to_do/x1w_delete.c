//******************************************************************************
// ARCHIVO: x1w.c
// AUTOR: Federico Ramos
// DESCRIPCI�N: Librer�a
// �LT. MODIF: 22-01-2020 1338
// COMENTARIO: Librer�a para comunicaci�n 1 wire
//             IMPORTANTE, ESTA LIBRERIA DESHABILITA POR PERIODOS DE US A TODAS
//             LAS INTERRUPCIONES
//
// Por lo que estuve viendo, esta es una version vieja de x1wDht11.c porque aquella la estuve ordenando.
// Este archivo dejarlo un tiempo y luego borrarlo.
//******************************************************************************


//******************************************************************************
// ARCHIVOS DE ENCABEZAMIENTO
#include <projectHeader.h>
#include <system.h>
#include <x1w_lib.h>
#include <timer_fixed_lib.h>
#include <timer_lib.h>
//******************************************************************************


//******************************************************************************
// DEFINICIONES DE USUARIO
//******************************************************************************



//FGR: Requiere un TMR_FIXED_X1W_SLOT (1ms)


//daly aprox 0.5us por cada unidad de delay
int nCyclesDelay;

//FGR: PIC18F4550@48Mhz
//#define MICROSECONDS_CONSTANT(us) ((int)(us/1.084375))

//n>1
#define DELAY_US(n)
	{\
	nCyclesDelay=((int)(n/1.084375));\
	while(--nCyclesDelay);\
	}

#define X1W_0
	{\
	X1_WIRE_0_DDR=OUTPUT;\
	X1_WIRE_0=0;
	}


#define X1W_RELEASE X1_WIRE_0_DDR=INPUT;



//******************************************************************************
// FUNCTION: x1w_rst()
//******************************************************************************
char x1w_rst(void)
    {
    char res;

    X1W_0;
    DELAY_US(480);//FGR:tRSTL=480us UC ENVIA PULSO RESET
    X1W_RELEASE;
    DELAY_US(70);//tPDHIGH=15-60us
    res=X1_WIRE_0;
    DELAY_US(410);
    return res;
    }


void x1w_write_bit(char b)
    {
    if(b)
        {
		#if	defined(_12F683)
			GIE=0;
		#else
			INTCONbits.GIE=0;
		#endif

        X1W_0;
        DELAY_US(6);//start of slot
        X1W_RELEASE;

		#if	defined(_12F683)
			GIE=1;
		#else
			INTCONbits.GIE=1;
		#endif

        DELAY_US(64);//tslot = 60us
        }
    else
        {
	#if	defined(_12F683)
		GIE=0;
	#else
		INTCONbits.GIE=0;
	#endif


        X1W_0;
        DELAY_US(60);//start of slot
        X1W_RELEASE;

	#if	defined(_12F683)
		GIE=1;
	#else
		INTCONbits.GIE=1;
	#endif

        DELAY_US(10);//tslot = 60us
        }
    }

char x1w_read_bit(void)
    {
    char res;

	#if	defined(_12F683)
		GIE=0;
	#else
		INTCONbits.GIE=0;
	#endif

    X1W_0;
    DELAY_US(6);//start of slot
    X1W_RELEASE;
    DELAY_US(9);//tslot = 60us
    res=X1_WIRE_0;

	#if	defined(_12F683)
		GIE=1;
	#else
		INTCONbits.GIE=1;
	#endif

    DELAY_US(55);

    return res;
    }


void x1w_write_byte(char data)
    {
    char i;

    for (i=0;i<8;i++)// Loop to write each bit in the byte, LS-bit first
        {
        x1w_write_bit(data & 0x01);
        data>>=1;// shift the data byte for the next bit
        }
    }

char x1w_read_byte(void)
    {
    char loop, result=0;

    for (loop=0;loop<8;loop++)
        {
        result>>=1;// shift the result to get it ready for the next bit // if result is one, then set MS bit
        if(x1w_read_bit()) result|=0x80;
        }
    return result;
    }



char OWTouchByte(char data)
    {
    char loop, result=0;
    for (loop = 0; loop < 8; loop++)
        {
        // shift the result to get it ready for the next bit
        result >>= 1;
        // If sending a '1' then read a bit else write a '0'
        if (data & 0x01)
            {
            if (x1w_read_bit())
            result |= 0x80;
            }
        else
            x1w_write_bit(0);
        // shift the data byte for the next bit
        data >>= 1;
        }
    return result;
    }



void OWBlock(unsigned char *data, char data_len)
    {
    char loop;
    for(loop=0;loop<data_len;loop++) data[loop]=OWTouchByte(data[loop]);
    }


char ReadPageMAC(void)
    {
    char i;

    if(x1w_rst()) return 0; // Return if no devices found

    x1w_write_byte(0xCC); // Send Skip ROM command to select single device
    x1w_write_byte(0x44); // Read Authentication command

    return 1;
    }

///////////////////////////
////////////////////////
///////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////

#define X1W_02\
	{\
	X1_WIRE_1_DDR=OUTPUT;\
	X1_WIRE_1=0;\
	}


#define X1W_RELEASE2 X1_WIRE_1_DDR=INPUT;

char dht11_mem[DHT11_RESPONSE_BYTES];

char x1w_dht11_get(void)
    {
    char i,j,res,pulseTicks;

    X1W_02;
    DELAY_US(18000);//FGR:tRSTL=480us UC ENVIA PULSO RESET
    X1W_RELEASE2;
    DELAY_US(40);//tPDHIGH=15-60us

    res=X1_WIRE_1;
    
    if(res==0)
        {
        DHT11_WAIT_FP();
        DHT11_WAIT_FN();//luego de esto, empieza transmision de datos

		INTCONbits.GIE=0;
        for(i=0;i<DHT11_RESPONSE_BYTES;i++)
            {
            dht11_mem[i]=0;
            for(j=0;j<8;j++)
                {
                pulseTicks=0;
				INTCONbits.GIE=1;
				INTCONbits.GIE=0;
                DHT11_WAIT_FP();

                do  {
                    DELAY_US(10);
                    pulseTicks++;
                    } while(X1_WIRE_1==1);
    
                if(pulseTicks>3)//bit=1 // porque puede quedar un ultimo tick afuera de la forma de onda
                    {
                    dht11_mem[i]|=(0x80>>j);
                    }
                }
            }
		INTCONbits.GIE=1;
        }
    return res;
    }


