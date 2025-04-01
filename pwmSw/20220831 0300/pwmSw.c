//******************************************************************************
// ARCHIVO: pwm_sw.c
// AUTOR: Federico Ramos
// ULT. MODIF: 01-09-2022
//******************************************************************************


#include <projectHeader.h>
#include <pwm_sw_lib.h>
#include <system.h>

//******************************************************************************
// DEFINICION DE VARIABLES GLOBALES
t_pwm_sw pwm;
//******************************************************************************


//******************************************************************************
// 	FUNCTION: 
//******************************************************************************
void pwm_sw_init(void)
    {


    }


void pwm_sw_driver(void)
    {
    if(pwm.periodAccum++==PERIOD_RST_VAL)
        {
        pwm.periodAccum=0;
        PWM=1;
        }
    if(PWM==1 && pwm.tonAccum++==pwm.tonResetVal)
        {
        pwm.tonAccum=0;
        PWM=0;
        }
    }