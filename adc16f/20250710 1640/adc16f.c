/*******************************************************************************
 * @file /adc16f/adc16f.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250708 1721
 ******************************************************************************/

 
#include <projectHeader.h>
#include <adc16f.h>


/* Globals ********************************************************************/

adc16f_struct adc16f_t;


/*******************************************************************************
 * @brief Inicia conversiones. Administra los distintos canales del ADC para que
 * se vayan procesando sus conversiones. Cada vez que corre la funciC3n, inicia u
 * na conversiC3n. No inicia si:
 * -- hay conversion pendiente para leer en el buffer.
 * -- esta haciendo una conversion que aC:n no finalizC3.
 *
 * Ubicar esta funcion fuera de las interrupciones, idealmente en un loop periC3d
 * ico de programa.
 ******************************************************************************/

void adc16f_driver(void) {           
    char ch2Cnv;

    if(adc16f_t.flgs2convert && !adc16f_t.inProcessFlg) {
        do {
            // Busca un flag seteado para iniciar conversiC3n
            ch2Cnv = adc16f_t.nx2convert;
            if(adc16f_t.nx2convert<=15) adc16f_t.nx2convert++;
            else adc16f_t.nx2convert=0;
        }
        while(!BIT_GETVAL_QUICK(adc16f_t.flgs2convert,ch2Cnv));

        // Originalmente implementado usando BIT_GETVAL_QUICK() pero en debugueo
        // ha saltado que no logra asignar correctamente los valores. Usando
        // BIT_GETVAL() lo hace bien. Se ha elegido de todos modos, la mejor
        // alternativa, que es usar una mascara.
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


/*******************************************************************************
 * @brief
 ******************************************************************************/

void adc16f_isr(void) {
    adc16f_t.chComp = CHS0 | CHS1 << 1 | CHS2 << 2 | CHS3 << 3;
    adc16f_t.completeFlg = 1;
    
    ADIF = 0;
}


/*******************************************************************************
 * @brief
 * @return ConversiC3n en 8 bits (seteo alineaciC3n izquierda en adcSetup()
 ******************************************************************************/

#include <system.h>

unsigned char adc16f_getConv(void) {
   adc16f_t.inProcessFlg=0;
   adc16f_t.completeFlg=0;
   return ADRESH;
    //return 16;
}

