/*******************************************************************************
 * @file /system/system_18f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250711 1816
 *
 * Cada proyecto particular tiene su propio archivo "system.c".
 ******************************************************************************/


#include <projectHeader.h>
#include <system_18f.h>
#include <interrupts.h>
//#include <adc_lib.h>


/*******************************************************************************
 * @brief
 ******************************************************************************/

void systemInit(void) {
   OSCCONbits.SCS = 0x00; // System Clock = Primary oscillator.
   UCFGbits.UTRDIS = 1; // Necesario para poder usar RC4/5 como digital input.
   RCONbits.IPEN = 1; // Low priority interrupts enable
   INTCON2bits.RBPU=0;// pull ups portb

   IPR2bits.TMR3IP=0;//interrupt timer 3 es low priority
   //IPR1bits.TMR1IP=1;//interrupt timer 3 es hi priority
   //IPR1bits.ADIP=0;//int AD low priority

   ADCON1bits.PCFG=0x0F;//para que todos los pines sean digitales y poder leer sus estados digitales.
   //adcSetup();

   IRQ_TIMER0_SETUP();
   //IRQ_TIMER1_SETUP();
   IRQ_TIMER3_SETUP();

   INIT_DDR();// Establece los puertos de entrada/salida.
   INIT_PORTS();// Al arranque, pone en un estado conocido a las salidas.

   INTCONbits.TMR0IE=1;
   //PIE1bits.TMR1IE=1;
   PIE2bits.TMR3IE=1;
 

// CCP1
  // IPR1bits.CCP1IP=0;//interrupt timer 3 es low priority
   //PIE1bits.CCP1IE=1;

//CCP1CON



   INTCONbits.PEIE=1;
   INTCONbits.GIE=1;
   INTCONbits.GIEH=1;
   INTCONbits.GIEL=1;
}

