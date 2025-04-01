//==============================================================================
// Archivo: d7sm.h
// Autor: Federico Ramos
// Modificado: 05-11-2023
//
// Prefijo identificatorio: disp7segMux = d7sm
//
// En este archivo:
// - HEDERS CON SETEOS POR PARTE DEL USUARIO
// - DEFINICION DE MACROS CONDICIONALES
// - DEFINICION DE ESTRUCTURAS
// - DECLARACION DE VARIABLES GLOBALES
// - DEFINICION DE MACROS 
// - DECLARACION DE FUNCIONES
//    o d7sm_char2pins(char c);
//    o d7sm_scroll_constString(const char *string);
//    o d7sm_puts_scroll(char *string);
//    o d7sm_set_88xx(char nTitila, unsigned char number, const char *unitText);
//    o d7sm_set_number(char nTitila, unsigned char number);
//    o d7sm_printf(char *fmt, ...);
//
// Requiere un timer T0_D7SM_SCROLL definido.
//==============================================================================


#ifndef __D7SM_H
#define __D7SM_H


//==============================================================================
// HEDERS CON SETEOS POR PARTE DEL USUARIO
//
// Definición de pines por parte del usuario. Ejemplo C:\0000 FEDE\16GB\0000 INT
// ERIOR\PFP_TMP_11\sw main\0003 pwm\0000 pulsos.
#include <d7sm_pindef.h>
#include <d7sm_setupUser.h>
//==============================================================================


//==============================================================================
// DEFINICION DE MACROS CONDICIONALES
//==============================================================================

// Macros condicionales para:
// - Individualmente apagar titileo de display <n> (auxiliar usada en D7SM_DP_AL
// L_OFF() -> d7sm_puts())
// - Individualmente apagar dp (dot point) de display <n> (auxiliar usada en D7S
// M_TITILA_ALL_OFF() -> d7sm_puts())
// - Individualmente apagar el anode (auxiliar usada en D7SM_ANODES_OFF() -> D7S
// M_IRQ_DRIVER()
// - Declarar en la estructura 
#ifdef  D7SM_A5
#define D7SM_TITILA_D5_OFF()    disp.d5_titila=0;
#define D7SM_DP5_OFF()          disp.d5_dp=0;
#define D7SM_A5_OFF()           D7SM_A5=0;
#define D7SM_TITILA_D5          char d5_titila:1;
#define D7SM_DP_D5              char d5_dp:1;
#else
#define D7SM_TITILA_D5_OFF()    {}
#define D7SM_DP5_OFF()          {}
#define D7SM_A5_OFF()           {}
#define D7SM_TITILA_D5
#define D7SM_DP_D5
#endif

#ifdef  D7SM_A4
#define D7SM_TITILA_D4_OFF()    disp.d4_titila=0;
#define D7SM_DP4_OFF()          disp.d4_dp=0;
#define D7SM_A4_OFF()           D7SM_A4=0;
#define D7SM_TITILA_D4          char d4_titila:1;
#define D7SM_DP_D4              char d4_dp:1;
#else
#define D7SM_TITILA_D4_OFF()    {}
#define D7SM_DP4_OFF()          {}
#define D7SM_A4_OFF()           {}
#define D7SM_TITILA_D4
#define D7SM_DP_D4
#endif

#ifdef  D7SM_A3
#define D7SM_TITILA_D3_OFF()    disp.d3_titila=0;
#define D7SM_DP3_OFF()          disp.d3_dp=0;
#define D7SM_A3_OFF()           D7SM_A3=0;
#define D7SM_TITILA_D3          char d3_titila:1;
#define D7SM_DP_D3              char d3_dp:1;
#else
#define D7SM_TITILA_D3_OFF()    {}
#define D7SM_DP3_OFF()          {}
#define D7SM_A3_OFF()           {}
#define D7SM_TITILA_D3
#define D7SM_DP_D3
#endif

#ifdef  D7SM_A2
#define D7SM_TITILA_D2_OFF()    disp.d2_titila=0;
#define D7SM_DP2_OFF()          disp.d2_dp=0;
#define D7SM_A2_OFF()           D7SM_A2=0;
#define D7SM_TITILA_D2          char d2_titila:1;
#define D7SM_DP_D2              char d2_dp:1;
#else
#define D7SM_TITILA_D2_OFF()    {}
#define D7SM_DP2_OFF()          {}
#define D7SM_A2_OFF()           {}
#define D7SM_TITILA_D2
#define D7SM_DP_D2
#endif

#ifdef  D7SM_A1
#define D7SM_TITILA_D1_OFF()    disp.d1_titila=0;
#define D7SM_DP1_OFF()          disp.d1_dp=0;
#define D7SM_A1_OFF()           D7SM_A1=0;
#define D7SM_TITILA_D1          char d1_titila:1;
#define D7SM_DP_D1              char d1_dp:1;
#else
#define D7SM_TITILA_D1_OFF()    {}
#define D7SM_DP1_OFF()          {}
#define D7SM_A1_OFF()           {}
#define D7SM_TITILA_D1
#define D7SM_DP_D1
#endif

#ifdef  D7SM_A0
#define D7SM_TITILA_D0_OFF()    disp.d0_titila=0;
#define D7SM_DP0_OFF()          disp.d0_dp=0;
#define D7SM_A0_OFF()           D7SM_A0=0;
#define D7SM_TITILA_D0          char d0_titila:1;
#define D7SM_DP_D0              char d0_dp:1;
#else
#define D7SM_TITILA_D0_OFF()    {}
#define D7SM_DP0_OFF()          {}
#define D7SM_A0_OFF()           {}
#define D7SM_TITILA_D0
#define D7SM_DP_D0
#endif

// D7SM_TITILA_ALL_OFF()
// Macro variable, dependiendo de la cantidad de anodes definidos.
// D7SM_TITILA_D<n>_OFF() puede ser que asigne valor a una salida o puede ser
// que no haga nada, dependiendo de si el anode correspondiente está definido.
#define D7SM_TITILA_ALL_OFF()                                                  \
    {                                                                          \
    D7SM_TITILA_D0_OFF();                                                      \
    D7SM_TITILA_D1_OFF();                                                      \
    D7SM_TITILA_D2_OFF();                                                      \
    D7SM_TITILA_D3_OFF();                                                      \
    D7SM_TITILA_D4_OFF();                                                      \
    D7SM_TITILA_D5_OFF();                                                      \
    }

// D7SM_DP_ALL_OFF()
// Macro variable, dependiendo de la cantidad de anodes definidos.
// D7SM_DP<n>_OFF() puede ser que asigne valor a una salida o puede ser que no
// haga nada, dependiendo de si el anode correspondiente está definido.
#define D7SM_DP_ALL_OFF()                                                      \
    {                                                                          \
    D7SM_DP0_OFF();                                                            \
    D7SM_DP1_OFF();                                                            \
    D7SM_DP2_OFF();                                                            \
    D7SM_DP3_OFF();                                                            \
    D7SM_DP4_OFF();                                                            \
    D7SM_DP5_OFF();                                                            \
    }

// D7SM_ANODES_ALL_OFF()
// Macro variable, dependiendo de la cantidad de anodes definidos.
// D7SM_Ai_OFF() puede ser que asigne valor a una salida o puede ser que no haga
// nada, dependiendo de si el anode correspondiente está definido.
#define D7SM_ANODES_ALL_OFF()                                                  \
    {                                                                          \
    D7SM_A0_OFF();                                                             \
    D7SM_A1_OFF();                                                             \
    D7SM_A2_OFF();                                                             \
    D7SM_A3_OFF();                                                             \
    D7SM_A4_OFF();                                                             \
    D7SM_A5_OFF();                                                             \
    }

// D7SM_TITILA_ALL_OFF()
// Macro variable, dependiendo de la cantidad de anodes definidos.
// D7SM_TITILA_D<n>_OFF() puede ser que asigne valor a una salida o puede ser
// que no haga nada, dependiendo de si el anode correspondiente está definido.
#define D7SM_DECLARE_BITS_TITILA                                               \
    D7SM_TITILA_D0                                                             \
    D7SM_TITILA_D1                                                             \
    D7SM_TITILA_D2                                                             \
    D7SM_TITILA_D3                                                             \
    D7SM_TITILA_D4                                                             \
    D7SM_TITILA_D5                                                             \

// D7SM_TITILA_ALL_OFF()
// Macro variable, dependiendo de la cantidad de anodes definidos.
// D7SM_TITILA_D<n>_OFF() puede ser que asigne valor a una salida o puede ser
// que no haga nada, dependiendo de si el anode correspondiente está definido.
#define D7SM_DECLARE_BITS_DP                                                   \
    D7SM_DP_D0                                                                 \
    D7SM_DP_D1                                                                 \
    D7SM_DP_D2                                                                 \
    D7SM_DP_D3                                                                 \
    D7SM_DP_D4                                                                 \
    D7SM_DP_D5                                                                 \


// Auxiliar usada en D7SM_A<n> -> D7SM_ANODES_ON() -> D7SM_IRQ_DRIVER()
#define D7SM_CASE_GENERICO(num, dispTitila, dispDp, dispAnode)                 \
    case num:                                                                  \
        if(!(dispTitila && bitTitila))                                         \
            {                                                                  \
            D7SM_SDP=!dispDp;                                                  \
            dispAnode=1;                                                       \
            }                                                                  \
        break;

// Auxiliar usada en d7sm_printf
#define D7SM_PRINTF_CASE_DP_GENERICO(num, dp)  case num: dp=1; break;

// Individuales para el switch
// Auxiliar usada en D7SM_ANODES_ON() -> D7SM_IRQ_DRIVER()
#ifdef  D7SM_A0
#define D7SM_A0_CASE() D7SM_CASE_GENERICO(0, disp.d0_titila, disp.d0_dp, D7SM_A0)
#define D7SM_PRINTF_CASE_DP0()  D7SM_PRINTF_CASE_DP_GENERICO(0, disp.d0_dp)
#else
#define D7SM_A0_CASE()              {}
#define D7SM_PRINTF_CASE_DP0()    {}
#endif

#ifdef  D7SM_A1
#define D7SM_A1_CASE() D7SM_CASE_GENERICO(1, disp.d1_titila, disp.d1_dp, D7SM_A1)
#define D7SM_PRINTF_CASE_DP1()  D7SM_PRINTF_CASE_DP_GENERICO(1, disp.d1_dp)
#else
#define D7SM_A1_CASE() {}
#define D7SM_PRINTF_CASE_DP1()    {}
#endif

#ifdef  D7SM_A2
#define D7SM_A2_CASE() D7SM_CASE_GENERICO(2, disp.d2_titila, disp.d2_dp, D7SM_A2)
#define D7SM_PRINTF_CASE_DP2()  D7SM_PRINTF_CASE_DP_GENERICO(2, disp.d2_dp)
#else
#define D7SM_A2_CASE() {}
#define D7SM_PRINTF_CASE_DP2()    {}
#endif

#ifdef  D7SM_A3
#define D7SM_A3_CASE() D7SM_CASE_GENERICO(3, disp.d3_titila, disp.d3_dp, D7SM_A3)
#define D7SM_PRINTF_CASE_DP3()  D7SM_PRINTF_CASE_DP_GENERICO(3, disp.d3_dp)
#else
#define D7SM_A3_CASE() {}
#define D7SM_PRINTF_CASE_DP3()    {}
#endif

#ifdef  D7SM_A4
#define D7SM_A4_CASE() D7SM_CASE_GENERICO(4, disp.d0_titila, disp.d4_dp, D7SM_A4)
#define D7SM_PRINTF_CASE_DP4()  D7SM_PRINTF_CASE_DP_GENERICO(4, disp.d4_dp)
#else
#define D7SM_A4_CASE() {}
#define D7SM_PRINTF_CASE_DP4()    {}
#endif

#ifdef  D7SM_A5
#define D7SM_A5_CASE() D7SM_CASE_GENERICO(5, disp.d5_titila, disp.d5_dp, D7SM_A5)
#define D7SM_PRINTF_CASE_DP5()  D7SM_PRINTF_CASE_DP_GENERICO(5, disp.d5_dp)
#else
#define D7SM_A5_CASE() {}
#define D7SM_PRINTF_CASE_DP5()    {}
#endif

// Macro variable, dependiendo de la cantidad de anodes definidos.
// El switch funcionaría también con "disp.mux_state" únicamente en el
// argumento, pero en ese caso, los índices de los "case" se  invierten, y no
// coincide el nro de case con el nro de ánode a encender, por lo que no puedo
// sintetizar la macro variable, sino que tengo que definirlas individualmente
// para cada cantidad de displays.
#define D7SM_ANODE_ON(mux_state)                                               \
    switch(D7SM_LENGTH-1-mux_state)                                            \
        {                                                                      \
        D7SM_A0_CASE();                                                        \
        D7SM_A1_CASE();                                                        \
        D7SM_A2_CASE();                                                        \
        D7SM_A3_CASE();                                                        \
        D7SM_A4_CASE();                                                        \
        D7SM_A5_CASE();                                                        \
        default: break;                                                        \
        }

// Macro variable, dependiendo de la cantidad de displays definidos.
#define D7SM_DP_ON(dp)                                                         \
    switch(D7SM_LENGTH-dp)                                                     \
        {                                                                      \
        D7SM_PRINTF_CASE_DP0();                                                \
        D7SM_PRINTF_CASE_DP1();                                                \
        D7SM_PRINTF_CASE_DP2();                                                \
        D7SM_PRINTF_CASE_DP3();                                                \
        D7SM_PRINTF_CASE_DP4();                                                \
        D7SM_PRINTF_CASE_DP5();                                                \
        default: break;                                                        \
        }

// D7SM_IRQ_DRIVER()
// Macro variable, dependiendo de la cantidad de anodes definidos.
#define D7SM_IRQ_DRIVER()                                                      \
    {                                                                          \
    D7SM_ANODES_ALL_OFF();                                                     \
                                                                               \
    if(disp.mux_state == (D7SM_LENGTH+OFF_PERIODS)) disp.mux_state=0;          \
    if(disp.mux_state < D7SM_LENGTH)                                           \
        {                                                                      \
        if  (                                                                  \
            disp.strOffs + disp.mux_state<D7SM_LENGTH ||                       \
            disp.strOffs+disp.mux_state > disp.strLen+D7SM_LENGTH-1            \
            )                                                                  \
            d7sm_char2pins(' ');                                               \
        else                                                                   \
            d7sm_char2pins(*(char*)(                                           \
                disp.str + disp.strOffs + disp.mux_state - D7SM_LENGTH));      \
                                                                               \
        D7SM_ANODE_ON(disp.mux_state);                                         \
        }                                                                      \
    disp.mux_state++;                                                          \
    }



//==============================================================================
// DEFINICION DE ESTRUCTURAS
//==============================================================================

// Se coloca en user settings porque dependiendo de cantidad de displays debo
// ajustar cantidad de titila y dots
typedef struct
    {
    // String pointer to memory that will be displayed. Pointer points to an
    // array of DISPLAY_LENGTH bytes. No hay condicionamiento de tamaño del
    // espacio de memoria que puede apuntar, ya que se configura para que
    // muestre con y sin scroll.
    char *str;

    // Barre string para el scroll cuando TMR0_D7SM_SCROLL corre. Inicializar
    // disp.strOffs=D7SM_LENGTH para que arranque scrolleando ok.
    char strOffs;


    // No es la cantidad de displays, sino del string a mostrar (en modo scroll,
    // puede ser de cualquier longitud).
    char strLen;

    char mux_state;// Barre de 0 a D7SM_LENGTH-1 para multiplexar (hay una
                   // sutileza para contemplar el brillo, pero importa.

    // Bitfield variable segun cantidad de displays
    D7SM_DECLARE_BITS_TITILA
    D7SM_DECLARE_BITS_DP
    }t_d7sm;


//==============================================================================
// DECLARACION DE VARIABLES GLOBALES

extern t_d7sm disp;// Estructura principal de la librería d7sm
extern char d7sm_buffer[];// Usada en d7sm_puts_scroll() con sting en ram
//==============================================================================


//==============================================================================
// DEFINICION DE MACROS
//==============================================================================

// MACRO: D7SM_SCROLL_DRIVER()
//==============================================================================
// Se invoca 1 única vez en todo el programa, por lo que puede ser macro sin inc
// onvenientes, para ahorrar stack.
// T0_D7SM_SCROLL es un timer que el usuario debe definir en la interrupción de
// timer0.
#define D7SM_SCROLL_DRIVER()                                                   \
   if(T0_TIMEOUT(T0_D7SM_SCROLL))                                              \
        {                                                                      \
        disp.strOffs++;                                                        \
        if(disp.strOffs>disp.strLen+4) disp.strOffs=0;                         \
        }

// MACRO: D7SM_ASSIGN_SEGMENTS()
//==============================================================================
// Usada en d7sm_char2pins(char c) para dibujar fácilmente las letras.
#define D7SM_ASSIGN_SEGMENTS(a,b,c,d,e,f,g)                                    \
    {                                                                          \
    D7SM_SA=a;                                                                 \
    D7SM_SB=b;                                                                 \
    D7SM_SC=c;                                                                 \
    D7SM_SD=d;                                                                 \
    D7SM_SE=e;                                                                 \
    D7SM_SF=f;                                                                 \
    D7SM_SG=g;                                                                 \
    }

// MACRO: D7SM_SET_NUMBER(nTitila,number)
//==============================================================================
// Versión macro de la función con el mismo nombre. Se implementa esta opción, p
// orque previene possible stack overflow para stacks de 8 niveles.
#define D7SM_SET_NUMBER(nTitila,number)                                        \
    {                                                                          \
	T0_STOP_LOOP(T0_D7SM_SCROLL);                                              \
	disp.strOffs=D7SM_LENGTH;                                                  \
	disp.strLen=D7SM_LENGTH;                                                   \
                                                                               \
    char *str=&d7sm_buffer[0];                                                 \
    UCHAR_TO_STR(number,str,4);                                                \
                                                                               \
    disp.str=d7sm_buffer;                                                      \
                                                                               \
    disp.d0_titila=nTitila;                                                    \
    disp.d1_titila=nTitila;                                                    \
    disp.d2_titila=nTitila;                                                    \
    disp.d3_titila=nTitila;                                                    \
    }

//==============================================================================
// DECLARACION DE FUNCIONES
void d7sm_char2pins(char c);
void d7sm_scroll_constString(const char *string);
void d7sm_puts_scroll(char *string);
void d7sm_set_88xx(char nTitila, unsigned char number, const char *unitText);
void d7sm_set_number(char nTitila, unsigned char number);
void d7sm_printf(char *fmt, ...);
//==============================================================================


#endif//__D7SM_H