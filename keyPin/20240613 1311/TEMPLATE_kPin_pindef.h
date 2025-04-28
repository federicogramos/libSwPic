//*****************************************************************************
// ARCHIVO: kPin_pindef.h
// AUTOR: Federico Ramos
// ULT. MODIF: 2022-10-12
// PROYECTO: TMP:11:CIC
//*****************************************************************************

#ifndef __KPIN_PINDEF_H
#define __KPIN_PINDEF_H


//*****************************************************************************
// CONSTANTES DE FUNCIONAMIENTO DE LIBRER�A
//10->INTERRUPCI�N 1MS
//100->INTERRUPCI�N 100US
#define KPIN__N_ANTIREBOTE 10
//*****************************************************************************


//*****************************************************************************
// COMPLETAR ESTRUCTURA PRINCIPAL
// LA CANTIDAD DE ELEMENTOS CORRESPONDE A LA CANTIDAD DE PULSADORES
// {state,prevState,timer}
// Por mas que sea FP o FN, state y prev state = 1 si input tiene pull-up.
t_kPin kPin[KPIN_CANT]=
	{
	{1,1,0},
    {1,1,0},
	{1,1,0},
	{1,1,0}
    };
//*****************************************************************************


#endif//__KPIN_PINDEF_H
