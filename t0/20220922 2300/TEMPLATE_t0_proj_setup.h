/*******************************************************************************
 * @file /elevador12f675/sw/t0_proj_setup.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250723 1546
 * 
 * Timers por software.
 ******************************************************************************/


#ifndef __T0_PROJ_SETUP_H
#define __T0_PROJ_SETUP_H


/*******************************************************************************
 * @brief
 ******************************************************************************/

typedef unsigned int type_t0Size;//TAMA�O DE VARIABLE QUE VA A CONTABILIZAR EL TIEMPO: char, int, long (unsigned or not)
typedef type_t0Size type_t0DelayConstant;//SE GENERA UN ARRAY QUE CONTIENE LOS TIEMPOS DE DURACI�N DE CADA TIMER. SE PUEDE DECLARAR "const" A ESTE TIPO DE DATO, PARA QUE NO OCUPE RAM EN CASO DE NO NECESITAR ALTERAR EL TIEMPO DE LOS TEMPORIZADORES.


#endif // __T0_PROJ_SETUP_H