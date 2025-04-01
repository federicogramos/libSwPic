//*****************************************************************************
// ARCHIVO: pulsadorPinFast_1ms_pindef.h
// AUTOR: Federico Ramos
// ULT. MODIF: 2022-10-12
// PROYECTO: TMP:11:CIC
//*****************************************************************************

#ifndef __PULSADOR_PIN_FAST_1MS_PINDEF_H
#define __PULSADOR_PIN_FAST_1MS_PINDEF_H


//*****************************************************************************
// CONSTANTES DE FUNCIONAMIENTO DE LIBRERÍA
//10->INTERRUPCIÓN 1MS
//100->INTERRUPCIÓN 100US
#define PULS_PIN_N_ANTIREBOTE 10
//*****************************************************************************


//*****************************************************************************
// SETEAR PUERTOS UTILIZADOS COMO PULSADORES
// 23-09-2022 ESTO ESTA CONFIGURADO PARA PROYECTO "RPM"
volatile bit PULSADOR_0 @ ((unsigned)&PORTA*8)+0;
volatile bit PULSADOR_1 @ ((unsigned)&PORTA*8)+2;
volatile bit PULSADOR_2 @ ((unsigned)&PORTA*8)+0;
volatile bit PULSADOR_3 @ ((unsigned)&PORTE*8)+3;

//UNUSED
//volatile bit PULSADOR_4 @ ((unsigned)&PORTC*8)+2;
//volatile bit PULSADOR_5 @ ((unsigned)&PORTA*8)+1;
//volatile bit PULSADOR_6 @ ((unsigned)&PORTD*8)+0;
//volatile bit PULSADOR_7 @ ((unsigned)&PORTD*8)+1;
//volatile bit PULSADOR_8 @ ((unsigned)&PORTC*8)+1;
//*****************************************************************************


//*****************************************************************************
// COMPLETAR ESTRUCTURA PRINCIPAL
// LA CANTIDAD DE ELEMENTOS CORRESPONDE A LA CANTIDAD DE PULSADORES
// {state,prevState,timer}
t_pulsPin pulsPin[PULS_PIN_CANT]=
	{
	{1,1,0},
    {1,1,0},
	{1,1,0},
	{1,1,0}
    };
//*****************************************************************************


#endif//__PULSADOR_PIN_FAST_1MS_PINDEF_H
