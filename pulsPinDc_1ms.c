// pulsadorPin.c

#include <projectHeader.h>
#include <pulsPinDc_lib_1ms.h>
//#include <system.h>

// DEFINICION DE VARIABLES GLOBALES
t_pulsEvent pulsPinBuffer;// PulsPin: los pines tocados se identifican de 1..N porque el 0 se reserva para indicar "ninguno ha sido presionado"

//FGR: DEBE SER SETEADO POR EL USUARIO CUALES PUERTOS USA COMO PULSADORES_1..N
volatile bit PULS_DC_0 @ ((unsigned)&GPIO*8)+5;//FGR: PULSADOR
volatile bit PULS_DC_1 @ ((unsigned)&GPIO*8)+3;//FGR: SIGNAL
volatile bit PULS_DC_2 @ ((unsigned)&GPIO*8)+3;//FGR: SIGNAL
volatile bit PULS_DC_3 @ ((unsigned)&GPIO*8)+0;

//FGR: NO MODIFICAR
enum e_names {P0,P1,P2,P3};
enum e_flanco {FLANCO_N,FLANCO_P};

//FGR: DEBE SER SETEADO POR EL USUARIO LOS FLANCOS PARA CADA PULSADOR
#define F_PULS_DC_0 FLANCO_N//FGR: PULSADOR
#define F_PULS_DC_1 FLANCO_N//FGR: SIGNAL
#define F_PULS_DC_2 FLANCO_P
#define F_PULS_DC_3 FLANCO_N

//FGR: SETEAR PARA LA CANT DE PULS USADOS
t_pulsPin pulsPin[PULS_PIN_CANT]={
                                 {1,1,0},
                                 {1,1,0},
                                 {1,1,0}
                                 };


// FGR: DEFINICION DE FUNCIONES

void puls_dc_0_driver(void)
	{
	if(pulsPin[P0].timer) pulsPin[P0].timer--;
	else
		{
		pulsPin[P0].state=PULS_DC_0;
		if(pulsPin[P0].state==F_PULS_DC_0 && pulsPin[P0].prevState==!F_PULS_DC_0)
			{
			pulsPin[P0].timer=PULS_PIN_N_ANTIREBOTE;
			pulsPinBuffer.pulsId=P0;
			pulsPinBuffer.flag=1;
			}
		pulsPin[P0].prevState=pulsPin[P0].state;
		}
	}

// Chequea por eventos en todos los pulsadores y los carga en el buffer.
// Para recoger los mensajes usar fgetc().
// Para ejecutar con periodo de 0.075s
void puls_dc_1_driver(void)
	{
	if(pulsPin[P1].timer) pulsPin[P1].timer--;
	else
		{
		pulsPin[P1].state=PULS_DC_1;
		if(pulsPin[P1].state==F_PULS_DC_1 && pulsPin[P1].prevState==!F_PULS_DC_1)
			{
			pulsPin[P1].timer=PULS_PIN_N_ANTIREBOTE;
			pulsPinBuffer.pulsId=P1;
			pulsPinBuffer.flag=1;
			}
		pulsPin[P1].prevState=pulsPin[P1].state;
		}
	}


void puls_dc_2_driver(void)
	{
	if(pulsPin[P2].timer) pulsPin[P2].timer--;
	else
		{
		pulsPin[P2].state=PULS_DC_2;
		if(pulsPin[P2].state==F_PULS_DC_2 && pulsPin[P2].prevState==!F_PULS_DC_2)
			{
			pulsPin[P2].timer=PULS_PIN_N_ANTIREBOTE;
			pulsPinBuffer.pulsId=P2;
			pulsPinBuffer.flag=1;
			}
		pulsPin[P2].prevState=pulsPin[P2].state;
		}
	}


//FGR IN_FN (USADO PARA DISPARAR ENTRADA)
//FGR: VERSION COMPATIBLE CON AC/DC
/*
void puls_dc_3_driver(void)
	{
	if(pulsPin[P3].timer)
		{
		pulsPin[P3].timer--;
		pulsPin[P3].state=PULS_DC_3;
		if(pulsPin[P3].state==F_PULS_DC_3 && pulsPin[P3].prevState==!F_PULS_DC_3) pulsPin[P3].timer=PULS_PIN_N_ANTIREBOTE;
		pulsPin[P3].prevState=pulsPin[P3].state;
		}
	else
		{
		pulsPin[P3].state=PULS_DC_3;
		if(pulsPin[P3].state==F_PULS_DC_3 && pulsPin[P3].prevState==!F_PULS_DC_3)
			{
			pulsPin[P3].timer=PULS_PIN_N_ANTIREBOTE;
			pulsPinBuffer.pulsId=P3;
			pulsPinBuffer.flag=1;
			}
		pulsPin[P3].prevState=pulsPin[P3].state;
		}
	}

*/

// Necesario para inicializar entradas conectadas a switches con retencion.
void pulsPinInit(void)
	{
	//char i;
	
	//for(i=0;i<PULS_PIN_CANT;i++)
	{
	//pulsPin[i].state=BIT_GETVAL(*(pulsPin[i].p2port),pulsPin[i].bitNum);
	//pulsPin[i].prevState=pulsPin[i].state;
	}
	}
