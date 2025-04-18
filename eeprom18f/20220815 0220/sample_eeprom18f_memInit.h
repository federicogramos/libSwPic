//==============================================================================
// Archivo: eeprom18f_memInit.h
// Autor: Federico Ramos
// Modificado: 20250402 0554
//
// Este archivo de inicialización, se pone separadamente fuera de la librería, j
// unto con la invocacion de #include <eeprom18f.h>, porque cuando se pone adent
// ro de la .h, se produce duplicacion de la reserva de memoria por cada vez que
// se invoca la libreria .h en otros archivos, por ejemplo, cuando se la requier
// e en interrupts.c u otro.
//==============================================================================


#ifndef __EEPROM18F_MEM_INIT_H
#define __EEPROM18F_MEM_INIT_H


// Init eeprom =================================================================
// Nota: usa doble espacio en identificadores.
// EEADDR__XX_YY
// XX: orden de arriba a abajo de cada byte EEPROM (address fisico real)
// YY: nro de byte de una variable cuyo sizeof es mayor a 1, ejemplo: int va a t
// ener 00 Y 01.
//==============================================================================

__EEPROM_DATA(
	0x00,// EEADDR__00_00__INPUT
	0x00,// EEADDR__01_00__VISOR_PARPADEO
	0x02,// EEADDR__02_00__NMEM (VALOR INICIAL = 2 MEMORIAS) (TON_0 + TOFF_0)
	0x00,// EEADDR__03_00__INTERMITENCIA_OUTPUT
	0x01,// EEADDR__04_00__FIRST
	0x00,// EEADDR__05_00__UNUSED
	0x00,// EEADDR__06_00__UNUSED
	0x00 // EEADDR__07_00__UNUSED
	);

__EEPROM_DATA(
	0x00,// EEADDR__08_00__UNUSED
	0x00,// EEADDR__09_00__UNUSED
	0x00,// EEADDR__10_00__UNUSED
	0x00,// EEADDR__11_00__UNUSED
	0x00,// EEADDR__12_00__UNUSED
	0x00,// EEADDR__13_00__UNUSED
	0x00,// EEADDR__14_00__UNUSED
	0x00 // EEADDR__15_00__UNUSED
	);


// Init eeprom =================================================================
// Comienza otra zona del mapa.
// Nota: usa doble espacio en identificadores.
//==============================================================================

__EEPROM_DATA(
	0x00,//EEADDR__16_00__TON0 (VALOR INICIAL = 8 SEGUNDOS)
	0x00,//EEADDR__17_01__TON0
	0x20,//EEADDR__18_02__TON0
	0x00,//EEADDR__19_00__OFF0 (VALOR INICIAL = 10 SEGUNDOS)
	0x00,//EEADDR__20_01__OFF0
	0x28,//EEADDR__21_02__OFF0
	0x00,//EEADDR__22_00
	0x00 //EEADDR__23_00
	);

    
// Init eeprom =================================================================
// Comienza otra zona del mapa.
// Blanqueo toda le eeprom para que inicialice tiempos = 0
//==============================================================================

__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);
__EEPROM_DATA(0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00);


#endif // __EEPROM18F_MEM_INIT_H