/*******************************************************************************
 * @file t0.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250710 1747
 *
 ******************************************************************************/


#ifndef __T0_H
#define __T0_H


/*******************************************************************************
 * Configuración
 ******************************************************************************/

#include <t0_proj_setup.h>
#include <t0_proj_aliases.h>
 

/*******************************************************************************
 * @brief
 ******************************************************************************/

typedef struct
   {
   type_t0Size 		prescaler;
   unsigned char	loop	: 1; // Timer circular.
   unsigned char	flag	: 1; // Timeout.
   unsigned char	pause	: 1; // Inhabilita decremento del contador.
   } t_t0;
 


/* External declarations ******************************************************/

extern t_t0 t0Mem[T0_CANT]; // Siempre inicializado a cero, por global.
extern type_t0DelayConstant t0DelayConstant[T0_CANT];


/* Macros *********************************************************************/

#define T0_START(i) {                                                          \
	t0Mem[i].flag = 0;                                                         \
	t0Mem[i].prescaler = t0DelayConstant[i];                                   \
	t0Mem[i].pause = 0;                                                        \
}

#define T0_INIT_LOOP(i) {                                                      \
	t0Mem[i].flag = 0;                                                         \
	t0Mem[i].prescaler = t0DelayConstant[i];                                   \
	t0Mem[i].pause = 0;                                                        \
	t0Mem[i].loop = 1;                                                         \
	}

#define T0_TIMEOUT(i) (t0Mem[i].flag? !(t0Mem[i].flag = 0) : 0)
#define T0_TIMEOUT_FORCE(i) (t0Mem[i].flag = 1)

#define T0_RUNNING(i) (!t0Mem[i].pause && t0Mem[i].prescaler != 0)
#define T0_PAUSED(i) (t0Mem[i].pause)

// Se necesita porque si esta en loop, el stop comun no quita el loop, y si se h
// ace TMR_START(), va a empezar como loop, cuando la intencion no hubiera sido 
// esa.
#define T0_STOP(i) {                                                           \
	t0Mem[i].prescaler=0;                                                      \
	}

#define T0_STOP_LOOP(i) {                                                      \
	t0Mem[i].prescaler = 0;                                                    \
	t0Mem[i].pause = 1;                                                        \
	t0Mem[i].loop = 0;                                                         \
	}

#define T0_PAUSE(i) (t0Mem[i].pause = 1)
#define T0_UNPAUSE(i) (t0Mem[i].pause = 0)
#define T0_STOPPED(i) (t0Mem[i].prescaler == 0 && !t0Mem[i].flag)


/* Prototipos *****************************************************************/

void t0Driver(char i);



#endif//__T0_H