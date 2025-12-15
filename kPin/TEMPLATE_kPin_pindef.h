/*******************************************************************************
 * @file kPin_pindef.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20251215 1645
 * @note Pines fisicos que usará como entradas de pulsador.
 ******************************************************************************/


#ifndef __KPIN_PINDEF_H
#define __KPIN_PINDEF_H


/*******************************************************************************
 * @brief Constants
 * Tirq 1ms => KPIN__N_ANTIREBOTE = 10
 * Tirq 100us => KPIN__N_ANTIREBOTE = 100
 ******************************************************************************/

 #define KPIN__N_ANTIREBOTE 10


/*******************************************************************************
 * @brief Port usage for keys
 * 20220923: esto esta configurado para proyecto "rpm".
 ******************************************************************************/

volatile bit PULSADOR_0 @ ((unsigned)&PORTA*8)+0;
volatile bit PULSADOR_1 @ ((unsigned)&PORTA*8)+2;
volatile bit PULSADOR_2 @ ((unsigned)&PORTA*8)+0;
volatile bit PULSADOR_3 @ ((unsigned)&PORTE*8)+3;


/*******************************************************************************
 * @brief Estructura principal pines. User debe completar segun pines usados.
 * 
 * La cantidad de elementos corresponde a la cantidad de pulsadores.
 ******************************************************************************/

// {state,prevState,timer}
t_kPin kPin[KPIN_CANT] = {
	{ 1, 1, 0 },
    { 1, 1, 0 },
	{ 1, 1, 0 },
	{ 1, 1, 0 }
    };
//*****************************************************************************


#endif//__KPIN_PINDEF_H
