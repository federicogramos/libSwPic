/*
 * @file adc18f.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250424 1716
 */


// Include

#include <projectHeader.h>
#include <adc18f_lib.h>


t_adc adcStruct;


/*
 * @brief
 */
void adcDriver(void)
   {
   char ch2cnv;

   if(adcStruct.flgs2convert && !adcStruct.inProcessFlg)
      {
      do
         {
         ch2cnv = adcStruct.nx2convert;
         if(adcStruct.nx2convert <= 12) adcStruct.nx2convert++;
         else adcStruct.nx2convert=0;
         }
      while(!BIT_GETVAL_QUICK(adcStruct.flgs2convert, ch2cnv));

      ADCON0bits.CHS = ch2cnv;

      BIT_CLR(adcStruct.flgs2convert, ch2cnv);
      adcStruct.inProcessFlg = 1;
      adcStruct.completeFlg = 0;
      ADCON0bits.GODONE = 1;
      }
   }


/*
 * @brief
 */
int getConv(void)
   {
   adcStruct.inProcessFlg=0;
   adcStruct.completeFlg=0;
   return ADRES;
   }


/*
 * @brief
 */
void isr_adc(void)
   {
   adcStruct.chComp=ADCON0bits.CHS;
   adcStruct.completeFlg=1;

   PIR1bits.ADIF = 0;
   }


/*
 * @brief
 * Necesario siempre indicar cuales son digitales porque por defecto son siempre
 * analogicos.
 */
void adcAllPortsDigital_18F46K80(void)
    {
    }

/*
 * @brief
 * Para PIC18F46K80
 * El setup siempre (aunque no use el ADC) debo ejecutarla, porque configura las
 * entradas que se usan como digitales cuando no se usa el ADC.
 */
void adcSetup_18F46K80(void)
    {
    // Seteo de esto lo hace siempre, porque por defecto arranca el micro con an
    // ologicos, pero los pone en digital si no se usan.
    ANSEL0 = ADC18F_CH00_USE;
    ANSEL1 = ADC18F_CH01_USE;
    ANSEL2 = ADC18F_CH02_USE;
    ANSEL3 = ADC18F_CH03_USE;
    ANSEL4 = ADC18F_CH04_USE;
    ANSEL5 = ADC18F_CH05_USE;
    ANSEL6 = ADC18F_CH06_USE;
    ANSEL7 = ADC18F_CH07_USE;
    ANSEL8 = ADC18F_CH08_USE;
    ANSEL9 = ADC18F_CH09_USE;
    ANSEL10 = ADC18F_CH10_USE;
    ANSEL11 = ADC18F_CH11_USE;
    ANSEL12 = ADC18F_CH12_USE;
    ANSEL13 = ADC18F_CH13_USE;
    ANSEL14 = ADC18F_CH14_USE;

    // Este codigo solo lo pone si hay ADC usandose.
    #if ADC18F_USE
    ADCON1bits.VCFG0 = 0;//Vref+=AVdd (4.1V)
    ADCON1bits.VCFG1 = 0;//Vref+=AVdd (4.1V)
    ADCON1bits.VNCFG = 0;//Vref-=AVss
    
    ADCON2bits.ADFM = 1;//Result format 1 = Right justified
    ADCON2bits.ACQT = 1;//Acquisition time 7 = 20TAD 2 = 4TAD 1=2TAD
    ADCON2bits.ADCS = 6;//Clock conversion bits 6 = FOSC/64 2=FOSC/32
    
    ADCON0bits.ADON = 1; // Turn on ADC
    PIR1bits.ADIF = 0;
    PIE1bits.ADIE = 1;
    #endif
    }
