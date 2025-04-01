//******************************************************************************
// ARCHIVO: adc18f.c
//******************************************************************************


//******************************************************************************
// INCLUDES
#include <projectHeader.h>
#include <adc18f_lib.h>
//******************************************************************************


//******************************************************************************
// DEFINICIÓN DE VARIABLES
t_adc adcStruct;
//******************************************************************************


//******************************************************************************
//
//******************************************************************************
void adcDriver(void)
   {
   char ch2cnv;

   if(adcStruct.flgs2convert && !adcStruct.inProcessFlg)
      {
      do
         {
         ch2cnv=adcStruct.nx2convert;
         if(adcStruct.nx2convert<=12) adcStruct.nx2convert++;
         else adcStruct.nx2convert=0;
         }
      while(!BIT_GETVAL_QUICK(adcStruct.flgs2convert,ch2cnv));

      ADCON0bits.CHS=ch2cnv;

      BIT_CLR(adcStruct.flgs2convert,ch2cnv);
      adcStruct.inProcessFlg=1;
      adcStruct.completeFlg=0;
      ADCON0bits.GODONE=1;
      }
   }


//******************************************************************************
//
//******************************************************************************
int getConv(void)
   {
   adcStruct.inProcessFlg=0;
   adcStruct.completeFlg=0;
   return ADRES;
   }


//******************************************************************************
//
//******************************************************************************
void isr_adc(void)
   {
   adcStruct.chComp=ADCON0bits.CHS;
   adcStruct.completeFlg=1;

   PIR1bits.ADIF=0;
   }


//NECESARIO SIEMPRE INDICAR CUALES SON DIGITALES PORQUE POR DEFECTO SON SIEMPRE ANALOGICOS
void adcAllPortsDigital_18F46K80(void)
    {
    }

//******************************************************************************
// PARA PIC18F46K80
// EL SETUP SIEMPRE (AUNQUE NO USE EL ADC) DEBO EJECUTARLA, PORQUE CONFIGURA LAS
// ENTRADAS QUE SE USAN COMO DIGITALES CUANDO NO SE USA EL ADC.
//******************************************************************************
void adcSetup_18F46K80(void)
    {
    //SETEO DE ESTO LO HACE SIEMPRE, PORQUE POR DEFECTO ARRANCA EL MICRO CON ANALOGICOS, PERO LOS PONE EN DIGITAL SI NO SE USAN
    ANSEL0=ADC18F_CH00_USE;
    ANSEL1=ADC18F_CH01_USE;
    ANSEL2=ADC18F_CH02_USE;
    ANSEL3=ADC18F_CH03_USE;
    ANSEL4=ADC18F_CH04_USE;
    ANSEL5=ADC18F_CH05_USE;
    ANSEL6=ADC18F_CH06_USE;
    ANSEL7=ADC18F_CH07_USE;
    ANSEL8=ADC18F_CH08_USE;
    ANSEL9=ADC18F_CH09_USE;
    ANSEL10=ADC18F_CH10_USE;
    ANSEL11=ADC18F_CH11_USE;
    ANSEL12=ADC18F_CH12_USE;
    ANSEL13=ADC18F_CH13_USE;
    ANSEL14=ADC18F_CH14_USE;

    //ESTE CODIGO SOLO LO PONE SI HAY ADC USANDOSE
    #if ADC18F_USE
    ADCON1bits.VCFG0=0;//Vref+=AVdd (4.1V)
    ADCON1bits.VCFG1=0;//Vref+=AVdd (4.1V)
    ADCON1bits.VNCFG=0;//Vref-=AVss
    
    ADCON2bits.ADFM=1;//Result format 1 = Right justified
    ADCON2bits.ACQT=1;//Acquisition time 7 = 20TAD 2 = 4TAD 1=2TAD
    ADCON2bits.ADCS=6;//Clock conversion bits 6 = FOSC/64 2=FOSC/32
    
    ADCON0bits.ADON=1; // Turn on ADC
    PIR1bits.ADIF=0;
    PIE1bits.ADIE=1;
    #endif
    }
