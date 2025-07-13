/**
 * @file /libSwPic/irq12f/irq12f.h
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version 20250427 1843
 * @note Librer�a que maneja las interrupciones.
 */


// Constants ===================================================================


/**
 * @brief Se setea el tiempo de interrupción en 2.5ms (oscilador=4Mhz,
 * timer0 prescaler=64). Calculo a realizar:
 * n=256-(Tinterrupt[s])*(fclk[Hz]/[4*prescaler])=256-(65E-3)*(4E6/[4*256])=2
 */
#define IRQ_TIMER0_RESET_VAL 225UL


/**
 * @brief Important�simo: es indispensable especificar que el n�mero es UL (unsigned
 * long), porque de otro modo, el compilador lo pierde en el camino, y cuando
 * lo quiero asignar, solamente asigna un byte, y el resto cero.
 * Se setea el tiempo de interrupci�n en 25ms (oscilador interno = 4Mhz,
 * timer1 con prescaler = 8). Calculo a realizar:
 * n = 65536 - (Tinterrupt[s]) * (fclk[Hz] / [4 * prescaler])
 * n = 65536 - 5E-3 * (4E6 / [4 * 8]) = 64911
 */
#define IRQ_TIMER1_RESET_VAL 34286UL


// Macros ======================================================================


#define IRQ_ENABLE()  {GIE=1;}
#define IRQ_DISABLE() {GIE=0;}


/**
 * @brief Peripheral interrupts: timer1, comparator, AD, EEPROM write complete.
 */
#define IRQ_PERIPHERAL_ENABLE()  {PEIE=1;}
#define IRQ_PERIPHERAL_DISABLE() {PEIE=0;}

   
#define IRQ_ADC_ENABLE()  {ADIE=1;}
#define IRQ_ADC_DISABLE() {ADIE=0;}

#define IRQ_TIMER0_ENABLE()  {T0IE=1;}
#define IRQ_TIMER0_DISABLE() {T0IE=0;}

#define IRQ_TIMER1_ENABLE()  {TMR1IE=1;}
#define IRQ_TIMER1_DISABLE() {TMR1IE=0;}

#define IRQ_TIMER0_RESET_FLAG()  {T0IF=0;}
#define IRQ_TIMER1_RESET_FLAG()  {TMR1IF=0;}
#define IRQ_ADC_RESET_FLAG()  {ADIF=0;}


/**
 * @brief Asigna un valor al acumulador del timer0.
 * If TMR0 is written, the increment is inhibited for the following two
 * instruction cycles. The user can work around this by writing an adjusted
 * value to the TMR0 register.
 */
#define IRQ_TIMER0_SET(value)                                                  \
    {                                                                          \
    TMR0 = value;                                                              \
    }

/**
 * @brief Asigna un valor al acumulador del timer1.
 */

#define HIGH_BYTE(x) ((unsigned char)(x>>8))
#define LOW_BYTE(x) ((unsigned char)(x & 0xFF))

#define ___IRQ_TIMER1_SET(value) {                      \
                              TMR1L=LOW_BYTE(value); \
                              TMR1H=HIGH_BYTE(value);\
                              }

#define IRQ_TIMER1_SET(value)                                                  \
    {                                                                          \
    TMR1L = GET_NUM_BYTE(0, value);                                            \
    TMR1H = GET_NUM_BYTE(1, value);                                            \
    }


/**
 * @brief Configura al timer0.
 * - prescaler=8
 * - el oscilador interno fosc/4 es quien incremente timer0
 * 
 * PS0
 * PS1
 * PS2
 * Prescaler no utilizado, sino que se utiliza PSA=1 para que no exista
 * prescaler a la se�al de clock.
 * (PS2,PS1,PS0)=(0,0,0):prescaler=2
 * (PS2,PS1,PS0)=(0,0,1):prescaler=4
 * (PS2,PS1,PS0)=(0,1,0):prescaler=8
 * (PS2,PS1,PS0)=(0,1,1):prescaler=16
 * (PS2,PS1,PS0)=(1,0,0):prescaler=32
 * (PS2,PS1,PS0)=(1,0,1):prescaler=64
 * (PS2,PS1,PS0)=(1,1,0):prescaler=128
 * (PS2,PS1,PS0)=(1,1,1):prescaler=256
 * 
 * PSA=0; El prescaler no se usa para el watchdog, y sino para el timer0.
 * PSA=1; No prescaler (relacion 1:1). El prescaler se usa para el watchdog.
 * 
 * T0SE
 * No usado. El flanco del pin T0CKI no tiene uso, ya que no estoy usando dicho
 * pin como generador de los pulsos para el timer0.
 * 
 * T0CS=0;
 * El clock usado no es el pin T0CKI, sino que el clock del ciclo de
 * instrucci�n del microcontrolador, es decir, que tiene una frecuencia de
 * fosc/4.
 * 
 * INTEDG
 * Ignorado por no tener relaci�n con el timer0
 * 
 * GPPU
 * Ignorado por no tener relaci�n con el timer0
 */
#define IRQ_TIMER0_SETUP()                                                     \
    {                                                                          \
    PSA = 1;                                                                   \
    T0CS = 0;                                                                  \
    PS0 = 0;                                                                   \
    PS1 = 0;                                                                   \
    PS2 = 0;                                                                   \
    IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);                                      \
    }


/**
 * @brief Configura al timer1.
 * - el oscilador interno fosc/4 es quien incremente timer1
 * - prescaler=8
 * 
 * TMR1ON=1;
 * Entrada de pulsos del contador habilitada.
 * 
 * TMR1CS=0;
 * Utilizaci�n del clock interno.
 * 
 * T1SYNC=1;
 * Se usa el clock interno, por lo que este bit es ignorado, ya que no tiene
 * sentido sincronizar el clock consigo mismo. Tampoco es indispensable cuando
 * se usa el clock externo (creo).
 * 
 * T1OSCEN=0;
 * LP oscillator no se habilita para el timer 1.
 * 
 * T1CKPS0=1;
 * T1CKPS1=0;
 * Establecimiento del prescaler en valor=8
 * (T1CKPS1,T1CKPS0)=(1,1) -> prescaler=8
 * (T1CKPS1,T1CKPS0)=(1,0) -> prescaler=4
 * (T1CKPS1,T1CKPS0)=(0,1) -> prescaler=2
 * (T1CKPS1,T1CKPS0)=(0,0) -> prescaler=1
 */
#define IRQ_TIMER1_SETUP()                                                     \
    {                                                                          \
    TMR1CS = 0;                                                                \
    T1SYNC = 1;                                                                \
    T1OSCEN = 0;                                                               \
    T1CKPS0 = 1;                                                               \
    T1CKPS1 = 1;                                                               \
    TMR1ON = 1;                                                                \
    IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);                                      \
    }





// El 887 no necesita port configuration (mucho mejor)
//                      PCFG0=0; \
//                      PCFG1=1; \
//                      PCFG2=0; \
//                      PCFG3=0; \



//                      ADCS2=1; \ Solo se usa para 87X versi�n A


//
//ADCS=Fosc/64 
//PCFG=AN0..4->analog / AN5..7->digital


/**
 * @brief Timer0 interrupt enable and flag set.
 */
#define IRQ_TIMER0 T0IE && T0IF


/**
 * @brief Timer1 interrupt enable and flag set.
 */
#define IRQ_TIMER1 TMR1IE && TMR1IF


/**
 * @brief ADC
 */
#define IRQ_ADC ADIE && ADIF


// Funciones ===================================================================


void isr_timer0(void);
void isr_timer1(void);
void isr_adc(void);

