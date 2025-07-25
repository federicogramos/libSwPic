/*******************************************************************************
 * @file /tmr0/t0.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250721 1900
 ******************************************************************************/


#include <t0.h>
#include <t0_proj_delays.h> // Delay de timers por parte de usuario.


/*******************************************************************************
 * Globals
 ******************************************************************************/

 t_t0 t0Mem[T0_CANT];


/*******************************************************************************
 * @brief
 ******************************************************************************/

void t0Driver(char i)
   {
   if(!t0Mem[i].pause && t0Mem[i].prescaler > 0)
      {
      t0Mem[i].prescaler--;
      if(t0Mem[i].prescaler == 0)
         {
         t0Mem[i].flag = 1;
         if(t0Mem[i].loop) t0Mem[i].prescaler = t0DelayConstant[i];
         }
      }
   }
