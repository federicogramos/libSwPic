//******************************************************************************
// ARCHIVO: pwm_sw_lib.c
// AUTOR: Federico Ramos
// ULT. MODIF: 01-09-2021
//******************************************************************************

// ESTA LIBRERÍA TIENE LA INICIALIZACIÓN DE LOS PUERTOS USADOS COMO PWM YA INCORPORADA
// A LA FUNCIÓN DE INICIALIZACIÓN PWM18F_INIT(), POR ESO NO ES NECESARIO INICIALIZAR
// LOS PUERTOS PWM USADOS.

#ifndef __PWM_SW_LIB_H
#define __PWM_SW_LIB_H


//******************************************************************************
// SETEOS USUARIO: CONSTANTES
//******************************************************************************
#define PERIOD_RST_VAL 1000


//******************************************************************************
// ESTRUCTURAS
typedef struct
    {
    int periodAccum;
    int tonAccum;
    int tonResetVal;//0..1000 = duty cycle 0..100
    }t_pwm_sw;
//******************************************************************************


//******************************************************************************
// DECLARACIÓN DE VARIABLES
extern t_pwm_sw pwm;
//******************************************************************************

void pwm_sw_init(void);
void pwm_sw_driver(void);


#endif//__PWM_SW_LIB_H