////////////////////////////////////////////////////////////////////////////////
// pwm.h                                                                    //
////////////////////////////////////////////////////////////////////////////////

#ifndef __SWPWM_H
#define __SWPWM_H

#define TIM1RST 65490UL
#define TMR1RST_LONGTIME 5536UL

typedef struct
   {
   unsigned int ton;
   unsigned char toff;
   char state;
   }T_SWPWM;

extern T_SWPWM pwm0;

void isr_swPwm(void);
void initSwPwm(void);

#endif
   // __SWPWM_H