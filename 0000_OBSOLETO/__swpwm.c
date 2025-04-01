////////////////////////////////////////////////////////////////////////////////
// swpwm.c                                                                    //
////////////////////////////////////////////////////////////////////////////////

#include <projectHeader.h>
#include <swpwm.h>
#include <system.h>



//T_SWPWM pwm0={63286,62536,0};//ton 1.5ms,toff 2ms
T_SWPWM pwm0={210,58036,0};//ton 1.5ms,toff 2ms

void initSwPwm(void)//rosello ccp2 a pin36 rb3 / 200Hz pwm
   {
   T1CONbits.TMR1CS=0;
   T1CONbits.RD16=1;
   T1CONbits.T1SYNC=1;
   T1CONbits.T1CKPS=0x00;//prescale=0
   TMR1=65513UL;//pwm0.toff;
   PIE1bits.TMR1IE=1;
   T1CONbits.TMR1ON=1;
   }
char aux;

void isr_swPwm(void)//pwm rosello pin 36, solo el unico disponible para pwm
   {
TMR1=TIM1RST;
//if(++pwmCounter==pwm0.ton) PWM0=0;
//else if(pwmCounter==255) PWM0=1,pwmCounter=0;

if(aux) aux=0,PWM0=0;
else aux=1,PWM0=1;

   PIR1bits.TMR1IF=0;
   }
