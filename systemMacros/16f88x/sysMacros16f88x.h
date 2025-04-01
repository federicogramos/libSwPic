//******************************************************************************
//
// archivo: system_macros_p16f88x.h
// autor: Federico Ramos
// modificado 2023-03-22
//
// En este archivo:
// - MACROS
//
//******************************************************************************



//******************************************************************************
//
// MACROS
//
//******************************************************************************



//******************************************************************************
// P16F88X_ECCP1_MODE_SELECT_OFF()

//CCP1M<3:0>: ECCP Mode Select bits
//0000 = Capture/Compare/PWM off (resets ECCP module)
//0001 = Unused (reserved)
//0010 = Compare mode, toggle output on match (CCP1IF bit is set)
//0011 = Unused (reserved)
//0100 = Capture mode, every falling edge
//0101 = Capture mode, every rising edge
//0110 = Capture mode, every 4th rising edge
//0111 = Capture mode, every 16th rising edge
//1000 = Compare mode, set output on match (CCP1IF bit is set)
//1001 = Compare mode, clear output on match (CCP1IF bit is set)
//1010 = Compare mode, generate software interrupt on match (CCP1IF bit is set,
//       CCP1 pin is unaffected)
//1011 = Compare mode, trigger special event (CCP1IF bit is set; CCP1 resets
//       TMR1 or TMR2
//1100 = PWM mode; P1A, P1C active-high; P1B, P1D active-high
//1101 = PWM mode; P1A, P1C active-high; P1B, P1D active-low
//1110 = PWM mode; P1A, P1C active-low; P1B, P1D active-high
//1111 = PWM mode; P1A, P1C active-low; P1B, P1D active-low
#define PIC16F88X_ECCP1_MODE_SELECT_OFF()   \
    {                                       \
    CCP1M0=0;                               \
    CCP1M1=0;                               \
    CCP1M2=0;                               \
    CCP1M3=0;                               \
    }

//******************************************************************************



//******************************************************************************
// P16F88X_ECCP2_MODE_SELECT_OFF()

#define PIC16F88X_ECCP2_MODE_SELECT_OFF()   \
    {                                       \
    CCP2M0=0;                               \
    CCP2M1=0;                               \
    CCP2M2=0;                               \
    CCP2M3=0;                               \
    }

//******************************************************************************



//******************************************************************************
// P16F88X_8MHZ()
#define PIC16F88X_8MHZ()\
    {                   \
    IRCF0=1;            \
    IRCF1=1;            \
    IRCF2=1;            \
    }
//******************************************************************************



