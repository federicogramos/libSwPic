/******************************************************************************/
/* ARCHIVO:     x1_wire.c                                                       */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: Librería                                                      */
/* ÚLT. MODIF:  22-01-2020 1338                                               */
/* COMENTARIO:  Librería para comunicación 1 wire.                            */
/******************************************************************************/


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/
#include <projectHeader.h>
#include <system.h>
#include <x1w_lib.h>
#include <timer_fixed_lib.h>

#include <thisProject.h>//Funciones específicas de cada proyecto
#include <disp7seg_lib.h>

//FGR: Requiere un TMR_FIXED_X1W_SLOT (1ms)




unsigned char x1_wire_buf[X1_WIRE_BUFLEN];


t_x1_wire x1_wireMem;//Siempre inicializado a cero, por global


void x1_wire_init(void)
    {
    x1_wireMem.newData=0;
    x1_wireMem.error=0;
    X1_WIRE_0=0;
    }

void x1w_sendByte(unsigned char byte)
    {
    X1_WIRE_0_DDR=OUTPUT;//PUT 0
    TMR_FIXED_STOP(TMR_FIXED_X1W_RST);
    TMR_FIXED_START(TMR_FIXED_X1W_RST);
    x1_wireMem.state=X1W_TX_RST_WAIT;


LED0=0;

disp_sys.dispNum=10;
    }


char aux;



void x1_wire_readBytes(char nBytes)
    {
    }

void x1_wire_driver()
    {
    if(x1_wireMem.state==X1W_TX_RST_WAIT)
        {
        if(TMR_FIXED_TIMEOUT(TMR_FIXED_X1W_RST))
            {
            X1_WIRE_0_DDR=INPUT;
            TMR_FIXED_START(TMR_FIXED_X1W_RST);
            x1_wireMem.state=X1W_RX_RST_WAIT_ZERO;


LED0=1;
disp_sys.dispNum=9;
            }
        }
    else if(x1_wireMem.state==X1W_RX_RST_WAIT_ZERO)
        {
        aux=X1_WIRE_0;
        if(aux==0)
            {
            x1_wireMem.state=X1W_RX_RST_WAIT_FP;
            disp_sys.dispNum=21;
            }
        else if(TMR_FIXED_TIMEOUT(TMR_FIXED_X1W_RST))
            {
            x1_wireMem.error=1;
            disp_sys.dispNum=22;
 x1_wire_sendByte(0);
            }


        }
    else if(x1_wireMem.state==X1W_RX_RST_WAIT_FP)
        {
        aux=X1_WIRE_0;
        if(aux==1)
            {
            x1_wireMem.state=X1W_RX_RST_OK;
            disp_sys.dispNum=31;
            }
disp_sys.dispNum=3;
        }
    else if(x1_wireMem.state==X1W_RX_RST_OK)
        {
        if(TMR_FIXED_TIMEOUT(TMR_FIXED_X1W_RST))
            {
            disp_sys.dispNum=1000;
            }
        
disp_sys.dispNum=4;
}
//    x1_wireMem.newData=1;
    }


/******************************************************************************/
/* DEFINICION DE VARIABLES GLOBALES                                           */
/******************************************************************************/

