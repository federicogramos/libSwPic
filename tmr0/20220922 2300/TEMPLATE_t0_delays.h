//******************************************************************************
// ARCHIVO: timer_delays.h
//******************************************************************************


#ifndef __T0_DELAYS_H
#define __T0_DELAYS_H


//******************************************************************************
// DEFINICION DE TIEMPOS POR PARTE DEL USUARIO
//******************************************************************************
type_t0DelayConstant t0DelayConstant[T0_CANT]=
	{
	40,
	16,
	8,
	1,
	0,
	1,
	0//mem_tZero=000.0[ms] -> LEVANTA EL VALOR DESDE MEMORIA
	};


#endif//__T0_DELAYS_H