//******************************************************************************
// ARCHIVO: timerEeprom_lib.h
//******************************************************************************


#ifndef __TIMEREEPROM_LIB_H
#define __TIMEREEPROM_LIB_H


//******************************************************************************
// NOMBRES DE TIMERS POR PARTE DEL USUARIO Y OTROS SETEOS
#include <timerEeprom_user_settings.h>
#include <timerEeprom_aliases.h>
//******************************************************************************


//******************************************************************************
// ESTRUCTURA PARA CONTROL DE TIEMPO
typedef struct
   {
   type_timerEepromSize prescaler;
   unsigned char loop:1;//timer circular
   unsigned char flag:1;//timeout
   unsigned char pause:1;//inhabilita decremento del contador
   }t_timerEeprom;
//******************************************************************************


//******************************************************************************
// DECLARACIÓN DE VARIABLES
extern t_timerEeprom timerEepromMem[CANT_TIMERS_EEPROM];//Siempre inicializado a cero, por global
extern type_timerEepromDelayConstant timerEepromDelayConstant[CANT_TIMERS_EEPROM];

// MACROS
#define TMREEPROM_START(i) {                                           \
                     timerEepromMem[i].flag=0;                         \
                     timerEepromMem[i].prescaler=timerEepromDelayConstant[i];\
                     timerEepromMem[i].pause=0;                        \
                     }

#define TMREEPROM_INIT_LOOP(i) {                                             \
                         timerEepromMem[i].flag=0;                            \
                         timerEepromMem[i].prescaler=timerEepromDelayConstant[i];\
                         timerEepromMem[i].pause=0;                           \
                         timerEepromMem[i].loop=1;                            \
                         }

#define TMREEPROM_TIMEOUT(i) (timerEepromMem[i].flag?!(timerEepromMem[i].flag=0):0)

#define TMREEPROM_RUNNING(i) (!timerEepromMem[i].pause && timerEepromMem[i].prescaler!=0)
#define TMREEPROM_PAUSED(i) (timerEepromMem[i].pause)
#define TMREEPROM_STOP(i) {                           \
                         timerEepromMem[i].prescaler=0;\
                         }
//se necesita porque si esta en loop, el stop comun no quita el loop, y si se hace TMR_START, va a empezar como loop, cuando la intencion no hubiera sido esa.
#define TMREEPROM_STOP_LOOP(i) {                           \
                         timerEepromMem[i].prescaler=0;\
                         timerEepromMem[i].pause=1;    \
                         timerEepromMem[i].loop=0;                            \
                         }

#define TMREEPROM_PAUSE(i) (timerEepromMem[i].pause=1)
#define TMREEPROM_UNPAUSE(i) (timerEepromMem[i].pause=0)
#define TMREEPROM_STOPPED(i) (timerEepromMem[i].prescaler==0 && !timerEepromMem[i].flag)

// DECLARACION DE FUNCIONES
void timerEepromDriver(char i);

#endif//__TIMEREEPROM_LIB_H