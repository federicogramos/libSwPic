/*******************************************************************************
 * @file /elevador12f675/sw/t0_proj_delays.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250723 1546
 * 
 * Timers por software.
 ******************************************************************************/


#ifndef __T0_DELAYS_H
#define __T0_DELAYS_H


/*******************************************************************************
 * @brief Definiciones usuario.
 ******************************************************************************/

type_t0DelayConstant t0DelayConstant[T0_CANT] = {
	40,
	16,
	8,
	1,
	0,
	1,
	0//mem_tZero=000.0[ms] -> LEVANTA EL VALOR DESDE MEMORIA
};


#endif // __T0_DELAYS_H