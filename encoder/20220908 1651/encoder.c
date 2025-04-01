//*****************************************************************************
// ARCHIVO: encoder.c
// AUTOR: Federico Ramos
// ULT. MODIF: 08-09-2022
//*****************************************************************************


//*****************************************************************************
// INCLUDES
#include <projectHeader.h>
#include <encoder_lib.h>
#include <system.h>
//*****************************************************************************
#include <timer_lib.h>

//*****************************************************************************
// USUARIO
#include <encoder_pindef.h>
//*****************************************************************************


//*****************************************************************************
// DEFINICION DE VARIABLES GLOBALES
t_encoderEvent encoderBuffer;// PulsPin: los pines tocados se identifican de 1..N porque el 0 se reserva para indicar "ninguno ha sido presionado"
//*****************************************************************************

// LA CANTIDAD DE ELEMENTOS CORRESPONDE A LA CANTIDAD DE PULSADORES {state,prevState,timer}
t_encoderPuls encoderPuls[ENCODER_PIN_CANT]=
	{
	{1,1,0},
    {1,1,0},
    {1,1,0},
    {1,1,0}
    };
//*****************************************************************************


void encoderPin_driver(char pi, char flanco, char pulsCurrentState)
	{
	if(encoderPuls[pi].timer) encoderPuls[pi].timer--;
	else
		{
		encoderPuls[pi].state=pulsCurrentState;
		if(encoderPuls[pi].state==flanco && encoderPuls[pi].prevState==!flanco)
			{
			encoderPuls[pi].timer=ENCODER_N_ANTIREBOTE;
			encoderBuffer.pulsId=pi;
			encoderBuffer.pulsFlag=1;
			}
		encoderPuls[pi].prevState=encoderPuls[pi].state;
		}
	}



void encoder_driver(char e)
	{
    encoderPin_driver(e+0,ENCODER_FLANCO_N,PORTDbits.RD0);//ENCODER_PIN_AN
    encoderPin_driver(e+1,ENCODER_FLANCO_N,PORTDbits.RD1);//ENCODER_PIN_BN
    encoderPin_driver(e+2,ENCODER_FLANCO_P,PORTDbits.RD0);//ENCODER_PIN_AP
    encoderPin_driver(e+3,ENCODER_FLANCO_P,PORTDbits.RD1);//ENCODER_PIN_BP



    switch(encoder[e].state)
        {
        case ENCODER_STATE_A:
            if(ENCODER_PULS_EVENT_ID(e+1))//VIENE FNB
                {
                encoder[e].state=ENCODER_STATE_AB;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;

        case ENCODER_STATE_AB:
            if(ENCODER_PULS_EVENT_ID(e+2))//FPA
                {
                encoder[e].state=ENCODER_STATE_ABX;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;

        case ENCODER_STATE_ABX:
            if(ENCODER_PULS_EVENT_ID(e+3))//VIENE FNB
                {
                encoder[e].state=ENCODER_STATE_IDLE;//YA TENGO UN PULSO ANTIHORARIO
                encoderBuffer.encoderId=e;
                encoderBuffer.encoderFlag=ENCODER_CW;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;


        case ENCODER_STATE_B:
            if(ENCODER_PULS_EVENT_ID(e+0))//VIENE FNA
                {
                encoder[e].state=ENCODER_STATE_BA;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;

        case ENCODER_STATE_BA:
            if(ENCODER_PULS_EVENT_ID(e+3))//FPB
                {
                encoder[e].state=ENCODER_STATE_BAY;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;

        case ENCODER_STATE_BAY:
            if(ENCODER_PULS_EVENT_ID(e+2))//VIENE FPA
                {
                encoder[e].state=ENCODER_STATE_IDLE;//YA TENGO UN PULSO ANTIHORARIO
                encoderBuffer.encoderId=e;
                encoderBuffer.encoderFlag=ENCODER_CCW;
                }
            else if(ENCODER_EVENT())
                encoder[e].state=ENCODER_STATE_IDLE;//CANCELAR
            break;

        case ENCODER_STATE_IDLE://IDLE
            if(ENCODER_PULS_EVENT_ID(e+0))//VIENE FNA
                encoder[e].state=ENCODER_STATE_A;
            if(ENCODER_PULS_EVENT_ID(e+1))//VIENE FNB
                encoder[e].state=ENCODER_STATE_B;
        }





    }

