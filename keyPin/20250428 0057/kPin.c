//==============================================================================
// Archivo: kPin.c
// Autor: Federico Ramos
// Modificado: 20250401 1654
//==============================================================================


//==============================================================================
// Headers
//==============================================================================

#include <project.h>
#include <kPin.h>


//==============================================================================
// Globals
//==============================================================================

t_kEvent kPinBuffer;


//==============================================================================
// Headers
//==============================================================================

//#include <system.h>


//==============================================================================
// Maneja un pin: pulsador conectado a dc.
// Recibe:
// - char pi: kPinAlias. Constante que toma valores de 0..(K_PIN_CANT-1). Normal
// mente se invocará utilizando el nombre del pulsador (segun definicion kPin_al
// iases.h/e_kPinAlias).
// - char kCurrLogState: K_i
//==============================================================================

void kPin_driverDc(char pi, char kCurrLogState)
    {
    if(kPin[pi].timer) kPin[pi].timer--;
    else
        {
        kPin[pi].state = kCurrLogState;

        if(kPin[pi].state==FLANCO_P && kPin[pi].prevState==!FLANCO_P)
            {
            kPinBuffer.flag = 1;
            kPinBuffer.flanco = FLANCO_P;
            kPin[pi].timer = KPIN__N_ANTIREBOTE;// Importantisimo: estos siguien
            // tes 2 renglones, si bien son comunes a ambos, no se deben sacar c
            // omo factor com�n porque si lo hago y uso kPinBuffer.flag para dis
            // tinguirlos, se confunde el driver en el momento en que aprietan o
            // tro boton (kPinBuffer.flag accionado por otro) y entonces funcion
            // a mal (mucho tiempo para darme cuenta).
            kPinBuffer.kId = pi;
            }
        else if(kPin[pi].state==FLANCO_N && kPin[pi].prevState==!FLANCO_N)
            {
            kPinBuffer.flag = 1;
            kPinBuffer.flanco = FLANCO_N;
            kPin[pi].timer = KPIN__N_ANTIREBOTE;
            kPinBuffer.kId = pi;
            }

        kPin[pi].prevState = kPin[pi].state;
        }
    }


//==============================================================================
// Version compatible con AC/DC. Para flanco negativo.
// IN_FN (USADO PARA DISPARAR ENTRADA)
//==============================================================================

void kPin_driverAcFn(char pi, char flanco, char kCurrLogState)
    {
    if(kPin[pi].timer)
        {
        kPin[pi].timer--;
        kPin[pi].state=kCurrLogState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
        kPin[pi].prevState=kPin[pi].state;
        }
    else
        {
        kPin[pi].state=kCurrLogState;
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
// Version compatible con AC/DC. Para flanco positivo.
//FGR IN_FP (USADO PARA DISPARAR ENTRADA)
//==============================================================================

void kPin_driverAcFp(char pi, char flanco, char kCurrLogState)
    {
    if(kPin[pi].timer)
        {
        kPin[pi].timer--;
        if(kPin[pi].timer==0) kPinBuffer.flag=1;//FGR:SETEA EL FLAG AL FINAL DEL ANTIREBOTE PARA COMPATIBILIZAR CON 220V
        kPin[pi].state=kCurrLogState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco) kPin[pi].timer=KPIN__N_ANTIREBOTE;
        kPin[pi].prevState=kPin[pi].state;
        }
    else
        {
        kPin[pi].state=kCurrLogState;
        if(kPin[pi].state==flanco && kPin[pi].prevState==!flanco)
            {
            kPin[pi].timer=KPIN__N_ANTIREBOTE;
            kPinBuffer.kId=pi;
            }
        kPin[pi].prevState=kPin[pi].state;
        }
    }

