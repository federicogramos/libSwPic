//==============================================================================
// Archivo: d7sm.c
// Autor: Federico Ramos
// Modificado: 2023-11-03
//
// Prefijo identificatorio: disp7segMux = d7sm
//
// En este archivo:
// - INCLUDE HEADERS
// - INICIALIZACIÓN DE ESTRUCTURA
// - DEFINICIÓN DE VARIABLES GLOBALES
// - DEFINICIÓN DE FUNCIONES
//     o d7sm_char2pins(char c)
//     o d7sm_puts_scroll(char *string)
//     o d7sm_set_88xx(char, unsigned char, const char*)
//     o d7sm_set_number(char nTitila,unsigned char number)
//     o d7sm_printf(char *fmt, ...)
//
// La inicialización del display se hace en la definición del buffer:
// char d7sm_buffer[D7SM_SCROLL_STRING_LENGTH]={'8','8','8','8'};
// Debería modificar esta inicialización para que sea automaticamente establecid
// a segun el largo del buffer.
// Hasta que no se configure el display para mostrar el buffer de scroll (el lar
// go, con el que se hace scroll, no el del driver d7sm_buffer) no actualiza el
// texto mostrado. Eso se usa para mostrar "8.8.8.8." al bootear.
//==============================================================================


//==============================================================================
// INCLUDE HEADERS
#include <projectHeader.h>
#include <d7sm.h>
#include <system.h>
#include <tmp_11.h>
#include <string.h> // Usa STRLEN() en d7sm_puts()
#include <stdlib.h> // Le usa UCHAR_TO_STR()
#include <ctype.h>  // IS_DIGIT()
#include <stdarg.h> // Para printf()
//==============================================================================


//==============================================================================
// INICIALIZACIÓN DE ESTRUCTURA
// Estado inicial: no scroll. Se encienden todos los puntos decimales para test.
t_d7sm disp=
    {
    d7sm_buffer,//char *str
    D7SM_LENGTH,//char strOffs
    D7SM_LENGTH,//char strLen
    0,//char mux_state;
    0,//char d0_titila;
    0,//char d1_titila;
    0,//char d2_titila;
    0,//char d3_titila;
    1,//char d0_dp
    1,//char d1_dp
    1,//char d2_dp
    1 //char d3_dp
    };
//==============================================================================


//==============================================================================
// DEFINICIÓN DE VARIABLES GLOBALES

// Buffer que lee el driver para procesar y mostrar salida de displays.
char d7sm_buffer[D7SM_SCROLL_STRING_LENGTH]={'8','8','8','8'};
//==============================================================================


//==============================================================================
// FUNCTION d7sm_char2pins(char c)
// Segmentos = minusculas / Letras = mayusculas
//==============================================================================
void d7sm_char2pins(char c)
    {
	D7SM_SDP=1;
	switch(c)
        {
        case '-': D7SM_ASSIGN_SEGMENTS(1,1,1,1,1,1,0); break;

        case '_': D7SM_ASSIGN_SEGMENTS(1,1,1,0,1,1,1); break;

        case 'O':
        case '0': D7SM_ASSIGN_SEGMENTS(0,0,0,0,0,0,1); break;

        case 'l':// L minúscula
        case 'I':
        case '1': D7SM_ASSIGN_SEGMENTS(1,0,0,1,1,1,1); break;

        case '2': D7SM_ASSIGN_SEGMENTS(0,0,1,0,0,1,0); break;

        case '3': D7SM_ASSIGN_SEGMENTS(0,0,0,0,1,1,0); break;

		case '4': D7SM_ASSIGN_SEGMENTS(1,0,0,1,1,0,0); break;

        case '5': D7SM_ASSIGN_SEGMENTS(0,1,0,0,1,0,0); break;

        case 'G':
        case '6': D7SM_ASSIGN_SEGMENTS(0,1,0,0,0,0,0); break;

        case '7': D7SM_ASSIGN_SEGMENTS(0,0,0,1,1,0,1); break;

        case '8': D7SM_ASSIGN_SEGMENTS(0,0,0,0,0,0,0); break;

        case 'g': // G minúscula
        case '9': D7SM_ASSIGN_SEGMENTS(0,0,0,0,1,0,0); break;

        case 'a': D7SM_ASSIGN_SEGMENTS(0,0,0,0,0,1,0); break;

        case 'A': D7SM_ASSIGN_SEGMENTS(0,0,0,1,0,0,0); break;

        case 'b': D7SM_ASSIGN_SEGMENTS(1,1,0,0,0,0,0); break;

        case 'c': D7SM_ASSIGN_SEGMENTS(1,1,1,0,0,1,0); break;

        case 'C': D7SM_ASSIGN_SEGMENTS(0,1,1,0,0,0,1); break;

        case 'D':
        case 'd': D7SM_ASSIGN_SEGMENTS(1,0,0,0,0,1,0); break;

        case 'o': D7SM_ASSIGN_SEGMENTS(1,1,0,0,0,1,0); break;

        case 'e': D7SM_ASSIGN_SEGMENTS(0,0,1,0,0,0,0); break;

        case 'E': D7SM_ASSIGN_SEGMENTS(0,1,1,0,0,0,0); break;

        case 'f':
        case 'F': D7SM_ASSIGN_SEGMENTS(0,1,1,1,0,0,0); break;

        case 'H': D7SM_ASSIGN_SEGMENTS(1,0,0,1,0,0,0); break;

        case 'h': D7SM_ASSIGN_SEGMENTS(1,1,0,1,0,0,0); break;

        case 'i': D7SM_ASSIGN_SEGMENTS(1,1,0,1,1,1,1); break;

        case 'J': D7SM_ASSIGN_SEGMENTS(1,0,0,0,0,1,1); break;

        case 'L': D7SM_ASSIGN_SEGMENTS(1,1,1,0,0,0,1); break;

        case 'm':
        case 'n': D7SM_ASSIGN_SEGMENTS(1,1,0,1,0,1,0); break;

        case 'M':
        case 'N': D7SM_ASSIGN_SEGMENTS(0,0,0,1,0,0,1); break;

        case 'P':
        case 'p': D7SM_ASSIGN_SEGMENTS(0,0,1,1,0,0,0); break;

        case 'q': D7SM_ASSIGN_SEGMENTS(0,0,0,1,1,0,0); break;

        case 'r': D7SM_ASSIGN_SEGMENTS(1,1,1,1,0,1,0); break;

        case 'R': D7SM_ASSIGN_SEGMENTS(0,1,1,1,0,0,1); break;

        case 's':
        case 'S': D7SM_ASSIGN_SEGMENTS(0,1,0,0,1,0,0); break;

		case 'T':        
		case 't': D7SM_ASSIGN_SEGMENTS(1,1,1,0,0,0,0); break;

        case 'v':
        case 'u': D7SM_ASSIGN_SEGMENTS(1,1,0,0,0,1,1); break;

        case 'U': D7SM_ASSIGN_SEGMENTS(1,0,0,0,0,0,1); break;

		case 'y':
        case 'Y': D7SM_ASSIGN_SEGMENTS(1,0,0,0,1,0,0); break;  

		case 'Z': D7SM_ASSIGN_SEGMENTS(0,0,1,0,0,1,0); break;

        case '#': D7SM_ASSIGN_SEGMENTS(0,1,1,0,1,1,0); break;      

        default: D7SM_ASSIGN_SEGMENTS(1,1,1,1,1,1,1); break;
        }
	}


//==============================================================================
// FUNCTION d7sm_puts_scroll(char *string)
//
// Imprime string al display 7 segmentos.
//
// Ejemplo de  uso (castea para evitar advertencia del compilador):
// d7sm_puts_scroll((char *)"imprimo directo con un string");
//==============================================================================
void d7sm_puts_scroll(char *string)
	{

	T0_INIT_LOOP(T0_D7SM_SCROLL);
	disp.strOffs=0;
	disp.str=string;

    STRLEN(string,stringStrlen);
    disp.strLen=stringStrlen;

    D7SM_TITILA_ALL_OFF();  // Apaga todos los disp.d<n>_titila
    D7SM_DP_ALL_OFF();      // Apaga todos los disp.d<n>_dp
    }


//==============================================================================
// FUNCTION d7sm_set_88xx(char, unsigned char, const char*)
//
// Lo que se mostrará en pantalla es:
// NNXX
// | |
// | +- unitText="xx" const string 2 char
// +--- number, del cual nTitila = 1|0, digito que va a titilar
//==============================================================================
void d7sm_set_88xx(char nTitila, unsigned char number,
                          const char* unitText)
	{
    char i, *str=&d7sm_buffer[0];
	
	T0_STOP_LOOP(T0_D7SM_SCROLL);//x las dudas de que esté con scroll
	disp.strOffs=D7SM_LENGTH;
	disp.strLen=D7SM_LENGTH;

    // Lo mismo que la función, pero versión macro, porque de otro modo me tira
    // possible stack overflow
    UCHAR_TO_STR(number,str, 2);
                    
    d7sm_buffer[2]=unitText[0];
    d7sm_buffer[3]=unitText[1];
    disp.str=d7sm_buffer;

    switch(nTitila)
        {
        case 0:
            disp.d0_titila=0;
            disp.d1_titila=0;
            disp.d2_titila=1;
            disp.d3_titila=0;
            break;
        case 1:
            disp.d0_titila=0;
            disp.d1_titila=0;
            disp.d2_titila=0;
            disp.d3_titila=1;
            break;
        }
    }


//==============================================================================
// FUNCTION d7sm_set_number(char nTitila,unsigned char number)
//==============================================================================
void d7sm_set_number(char nTitila,unsigned char number)
	{
	T0_STOP_LOOP(T0_D7SM_SCROLL);//POR LAS DUDAS DE Q ESTÉ CON SCROLL
	disp.strOffs=D7SM_LENGTH;
	disp.strLen=D7SM_LENGTH;

    char *str=&d7sm_buffer[0];
    UCHAR_TO_STR(number,str,4);//TRASLADADO A PREVIO A INVOCAR
                                 // d7sm_set_number() DEBIDO A POSSIBLE
                                 // STACK OVR
    disp.str=d7sm_buffer;

    disp.d0_titila=nTitila;
    disp.d1_titila=nTitila;
    disp.d2_titila=nTitila;
    disp.d3_titila=nTitila;
    }


//==============================================================================
// FUNCTION d7sm_printf()
//
// Imprime al display 7 segmentos con formato.
// - No valida cantidad de caracteres escritos en pantalla que no se pase de lo
//   que es capaz de mostrar.
// - Para %u, siempre debe colocarse el "minimum field width": %<n>u
// - Se pueden imprimir los "dots" ('.') y no ocupa "espacio" en el display,
//   puesto que se usa el mismo punto dp del display.
// - In contrast to standard function, it does not return the total number of
//   chars written
//
// Nota: La funcion va_arg no anda mal. Si uso en un printf 2 argumentos int, me
// devuelve el segundo mal -> Porque le mandas 2 parametros short long int en
// lugar de solamente int.
//==============================================================================
void d7sm_printf(char *fmt, ...)
    {
    va_list ap;// Puntero de argumentos

    // Index para buffer de memoria leído por el driver e impreso en pantalla.
    char i=0;

    // Apago dps y dejo de titilar. Luego si debe cambiar, lo dirá el fmt.
    D7SM_DP_ALL_OFF();
    D7SM_TITILA_ALL_OFF();

    #ifdef D7SM_PRINTF_ENABLE_FMT_U// Customización de d7sm_printf()
    unsigned uval;// No me deja hacer la inicializacion conjunta
    char numLen;// Siempre debe colocarse el "minimum field width"
    #endif
    
    va_start(ap, fmt);// Se hace que ap apunte al primer argumento sin nombre

    for(char *p=fmt; *p; p++)
        {
        if(i>0 && *p=='.')// Los puntos los trata por separado porque usa los
            {             // propios del display.
            D7SM_DP_ON(i);// Switch-case variable dependiendo de D7SM_LENGTH
            }
        else if(*p=='%')
            {
            if(IS_DIGIT(*(p+1))) numLen=*(++p)-'0';// Convierte a numero el char

            switch(*++p)
                {
                #ifdef D7SM_PRINTF_ENABLE_FMT_D// Customización de d7sm_printf()
                case 'd':
                case 'i':
                    int ival=va_arg(ap,int);
                    v=intToStr(ival,str,MAX_PRINTF_INT);
                    while(*v) putc(*(v++));// Copia el string hasta el final
                    break;
                #endif

                #ifdef D7SM_PRINTF_ENABLE_FMT_C// Customización de d7sm_printf()
                case 'c':
                    ival=va_arg(ap,int);
                    (void)putc((char)ival);
                    break;
                #endif

                #ifdef D7SM_PRINTF_ENABLE_FMT_U// Customización de d7sm_printf()
                case 'u':
                    uval=va_arg(ap,unsigned int);

                    // No usa funciones aquí por possible stack overflow.
                    // Calcula longitud que ocupará escribir el nro.
                    UCHAR_TO_STR(uval, &d7sm_buffer[i], numLen);
                    i+=numLen;
                    break;
                #endif

                #ifdef D7SM_PRINTF_ENABLE_FMT_D// Customización de d7sm_printf()
                case 's':
                    for(char *sval=va_arg(ap,char *); *sval; sval++)
                        (void)putc(*sval);
                    break;
                #endif

                #ifdef D7SM_PRINTF_ENABLE_FMT_DEFAULT// Customización
                default: (void)putc(*p);
                #endif
                }
            }
        else d7sm_buffer[i++]=*p;
        }
    va_end(ap);

    disp.str=d7sm_buffer;
	disp.strOffs=D7SM_LENGTH;
	disp.strLen=D7SM_LENGTH;
   }
