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
 * 
 * Tiempo de antirebote = 25ms es algo muy aceptable. Perceptiblemente nulo, y e
 * n tiempo de rebote físico del mecanismo suficiente.
 * Tirq 1ms => KPIN__N_ANTIREBOTE = 25
 * Tirq 100us => KPIN__N_ANTIREBOTE = 250
 ******************************************************************************/

 #define KPIN__N_ANTIREBOTE 10


/*******************************************************************************
 * @brief Port usage for keys
 * 20220923: esto esta configurado para proyecto "rpm".
 * Ejemplo pic12f:
 * volatile bit PULSADOR_1 @ ((unsigned) &GPIO * 8) + 4;
 * Ejemplo pic16f:
 * volatile bit PULSADOR_0 @ ((unsigned)&PORTA * 8) + 0;
 ******************************************************************************/

volatile bit PULSADOR_0 @ ((unsigned) &PORTA * 8) + 0;
volatile bit PULSADOR_1 @ ((unsigned) &PORTA * 8) + 2;
volatile bit PULSADOR_2 @ ((unsigned) &PORTA * 8) + 0;
volatile bit PULSADOR_3 @ ((unsigned) &PORTE * 8) + 3;


/*******************************************************************************
 * @brief Estructura principal pines. User debe completar segun pines usados.
 * 
 * La cantidad de elementos corresponde a la cantidad de pulsadores.
 * Cada elemento => {state, prevState, timer}
 * -- state = si usa pull-up => = 1
 * -- prevstate = state (para que no arranque generando un pulso)
 * -- timer = normalmente = 0 si quiere que empieze sin contar.
 ******************************************************************************/

t_kPin kPin[KPIN_CANT] = {
	{ 1, 1, 0 },
    { 1, 1, 0 },
	{ 1, 1, 0 },
	{ 1, 1, 0 }
    };


#endif//__KPIN_PINDEF_H
