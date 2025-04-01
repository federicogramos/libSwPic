//******************************************************************************
//
// archivo: adc16f.c
// autor: Federico Ramos
// modificado: 2022-10-13
//
// En este archivo:
// - INCLUDES
// - DEFINICIÓN DE VARIABLES GLOBALES
// - DEFINICIÓN DE FUNCIONES
//      o Función: adc16f_driver()
//      o Función: adc16f_isr()
//      o Función: adc16f_getConv()
//
//******************************************************************************



//******************************************************************************
// INCLUDES

#include <projectHeader.h>
#include <adc16f_lib.h>

//******************************************************************************



//******************************************************************************
// DEFINICIÓN DE VARIABLES GLOBALES

adc16f_struct adc16f_t;

//******************************************************************************



//******************************************************************************
//
// Función: adc16f_driver()
//
// Esta función se ubica fuera de las interrupciones, idealmente en un loop
// periódico de programa.
//
// Inicia conversiones. Administra los distintos canales del ADC para que se
// vayan procesando sus conversiones.
//
// Cada vez que corre la función, inicia una conversión. No inicia si:
// - hay conversion pendiente para leer en el buffer
// - está haciendo una conversión que aún no finalizó
//
//******************************************************************************

void adc16f_driver(void)
    {
    char ch2Cnv;

    if(adc16f_t.flgs2convert && !adc16f_t.inProcessFlg)
        {
        do// Busca un flag seteado para iniciar conversión
            {
            ch2Cnv = adc16f_t.nx2convert;
            if(adc16f_t.nx2convert<=15) adc16f_t.nx2convert++;
            else adc16f_t.nx2convert=0;
            }
        while(!BIT_GETVAL_QUICK(adc16f_t.flgs2convert,ch2Cnv));

        // Originalmente implementado usando BIT_GETVAL_QUICK() pero en debugueo
        // ha saltado que no logra asignar correctamente los valores. Usando
        // BIT_GETVAL() lo hace bien. Se ha elegido de todos modos, la mejor
        // alternativa, que es usar una máscara.
        // A saber: definitions for ADCON0 register.
        // +-------+-------+------+------+------+------+--------+------+
        // | ADCS1 | ADCS0 | CHS3 | CHS2 | CHS1 | CHS0 | GODONE | ADON |
        // +-------+-------+------+------+------+------+--------+------+
        ADCON0_t.CHS=ch2Cnv;

        BIT_CLR(adc16f_t.flgs2convert,ch2Cnv);
        adc16f_t.inProcessFlg=1;
        adc16f_t.completeFlg=0;
        GODONE = 1;
        }
    }



//******************************************************************************
//
// Función: isr_adc()
//
//******************************************************************************

void adc16f_isr(void)
    {
    adc16f_t.chComp=CHS0|CHS1<<1|CHS2<<2|CHS3<<3;
    adc16f_t.completeFlg=1;
    
    ADIF=0;
    }



//******************************************************************************
//
// Función: getConv()
//
// Devuelve conversión en 8 bits (seteo alineación izquierda en adcSetup()
//
//******************************************************************************

#include <system.h>

unsigned char adc16f_getConv(void)
   {
   adc16f_t.inProcessFlg=0;
   adc16f_t.completeFlg=0;
   return ADRESH;
//return 16;
   }

