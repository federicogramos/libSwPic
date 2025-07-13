////////////////////////////////////////////////////////////////////////////////
// system.h                                                                   //
// Tener en cuenta que se debe incluir /irq12f/irq12f.h para hacer IRQ_TIMER1_SE
// TUP()
////////////////////////////////////////////////////////////////////////////////

#define INPUT 1
#define OUTPUT 0

#define ANALOG_INPUT 1
#define DIGITAL_IO 0
// Definiciones para seleccionar funcionalidad de ANSEL (A/D).

////////////////////////////////////////////////////////////////////////////////
// PINES Y ORDEN EN EL QUE LOS VOY A UTILIZAR                                 //
////////////////////////////////////////////////////////////////////////////////

#define BCD1 GPIO0
#define BCD2 GPIO1
#define BCD3 GPIO2
#define UNUSED3 GPIO3
#define ADC GPIO4
#define BCD0 GPIO5

////////////////////////////////////////////////////////////////////////////////
// DATA DIRECTION REGISTERS                                                   //
////////////////////////////////////////////////////////////////////////////////

#define DDR_BCD1 TRIS0
#define DDR_BCD2 TRIS1
#define DDR_BCD3 TRIS2
#define DDR_UNUSED3 TRIS3
#define DDR_ADC TRIS4
#define DDR_BCD0 TRIS5

#define INIT_DDR() {                 \
                   DDR_BCD1=OUTPUT;  \
                   DDR_BCD2=OUTPUT;  \
                   DDR_BCD3=OUTPUT;  \
                   DDR_UNUSED3=INPUT;\
                   DDR_ADC=INPUT;\
                   DDR_BCD0=OUTPUT;  \
                   }

////////////////////////////////////////////////////////////////////////////////
// FUNCIONES                                                                  //
////////////////////////////////////////////////////////////////////////////////
void systemInit(void);


////////////////////////////////////////////////////////////////////////////////
// MACROS                                                                     //
////////////////////////////////////////////////////////////////////////////////

#define DISABLE_COMPARATOR() {     \
                             CM0=1;\
                             CM1=1;\
                             CM2=1;\
                             }
// Comparator is set off.


#define DISABLE_AD() {      \
                     ANS0=DIGITAL_IO;\
                     ANS1=DIGITAL_IO;\
                     ANS2=DIGITAL_IO;\
                     ANS3=DIGITAL_IO;\
                     }
// Si no se va a usar el A/D, esta funci�n se debe invocar, ya que por defecto,
// luego del reset, los puertos de entrada comienzan como entradas anal�gicas
// para ser usadas con el A/D, lo cual deshabilita que funcionen como entradas/
// salidas digitales.

#define AD_SETUP() {      \
                     ANS0=DIGITAL_IO;\
                     ANS1=DIGITAL_IO;\
                     ANS2=DIGITAL_IO;\
                     ANS3=ANALOG_INPUT;\
                     CHS0=1;\
                     CHS1=1;\
                     VCFG=0;\
                     ADFM=1;\
                     ADCS0=1;\
                     ADCS1=1;\
                     ADCS2=1;\
                     ADON=1;\
                     }
// Si se va a usar el A/D, esta funci�n se debe invocar, para setear la manera
// en la que se usar� el A/D, cantidad de canales, etc.
// Solo se usa AN3.
// El voltaje de referencia es VDD.
// El resultado se quiere right-justified.
// Se utiliza el oscilador RC dedicado interno para generar frecuencia de
// conversi�n del AD (frecuencia de conversi�n maxima = 45KHz).

#define AD_INIT_CONVERSION() {GODONE=1;}
// Inicia conversi�n del A/D. Si voy a usar el AD mediante interrupciones,
// porque quiero que autom�ticamente me llame la rutina de interrupci�n cada vez
// que hay una conversi�n nueva, al menos 1 vez al principio del booteo del
// programa debo llamar a esta macro, porque si no, nunca va a conmenzar a
// convertir el ADC.
