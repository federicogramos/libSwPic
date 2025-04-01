//==============================================================================
// ARCHIVO: kPin.c
// AUTOR: Federico Ramos
// ULT. MODIF: 03-11-2023
//==============================================================================


//==============================================================================
// INCLUDE
#include <projectHeader.h>
#include <kPin.h>
//==============================================================================


//==============================================================================
// DEFINICION DE VARIABLES GLOBALES
t_kEvent kPinBuffer;
//==============================================================================


//==============================================================================
// INCLUDE
#include <system.h>
//==============================================================================


//==============================================================================
// FUNCTION: kPin_driverDc()
// char pi: kPinAlias. Constante que toma valores de 0..(K_PIN_CANT-1). Normalme
//     nte se invocará utilizando el nombre del pulsador (segun definicion kPin_
//     aliases.h/e_kPinAlias)
// char flanco: FLANCO_P/FLANCO_N
// char kCurrentState: K_i
// COMENTARIO: pulsador dc
//==============================================================================
void kPin_driverDc(char pi, char flanco, char kCurrentState)
    {
    if(kPin[pi].timer) kPin[pi].timer--;
    else
        {
        kPin[pi].state = kCurrentState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco)
            {
            kPin[pi].timer = KPIN__N_ANTIREBOTE;
            kPinBuffer.kId = pi;
            kPinBuffer.flag = 1;
            }
        kPin[pi].prevState = kPin[pi].state;
        }
    }


//==============================================================================
// FUNCTION: pulsador_dc_driver()
// COMENTARIO:
//FGR IN_FN (USADO PARA DISPARAR ENTRADA)
//FGR: VERSION COMPATIBLE CON AC/DC
//==============================================================================
void kPin_driverAcFn(char pi, char flanco, char kCurrentState)
    {
    if(kPin[pi].timer)
        {
        kPin[pi].timer--;
        kPin[pi].state=kCurrentState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
        kPin[pi].prevState=kPin[pi].state;
        }
    else
        {
        kPin[pi].state=kCurrentState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco)
            {
            kPin[pi].timer=KPIN__N_ANTIREBOTE;
            kPinBuffer.kId=pi;
            kPinBuffer.flag=1;
            }
        kPin[pi].prevState=kPin[pi].state;
        }
    }


//==============================================================================
//FGR IN_FP (USADO PARA DISPARAR ENTRADA)
//FGR: VERSION COMPATIBLE CON AC/DC
//==============================================================================
void kPin_driverAcFp(char pi, char flanco, char kCurrentState)
    {
    if(kPin[pi].timer)
        {
        kPin[pi].timer--;
        if(kPin[pi].timer==0) kPinBuffer.flag=1;//FGR:SETEA EL FLAG AL FINAL DEL ANTIREBOTE PARA COMPATIBILIZAR CON 220V
        kPin[pi].state=kCurrentState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
        kPin[pi].prevState=kPin[pi].state;
        }
    else
        {
        kPin[pi].state=kCurrentState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco)
            {
            kPin[pi].timer=KPIN__N_ANTIREBOTE;
            kPinBuffer.kId=pi;
            }
        kPin[pi].prevState=kPin[pi].state;
        }
    }

