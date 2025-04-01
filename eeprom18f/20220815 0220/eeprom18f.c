/******************************************************************************/
/* ARCHIVO:     eeprom_18f_lib.c                                              */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  10-06-2019 1632                                               */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/
#include <projectHeader.h>
#include <eeprom_18f_lib.h>


/******************************************************************************/
/* ARCHIVOS QUE DEBE CREAR EL USUARIO: RESERVA EEPROM                         */
/* NOTA: Debe ir aqui, dentro de "eeprom_18f_lib.h" duplica reserva.          */
/******************************************************************************/
#include <eeprom_18f_reserva.h>


/******************************************************************************/
/* FUNCIÓN:     fgetc(FILE*)                                                  */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:                                                                */
/******************************************************************************/
void ee_write_byte(unsigned char address, unsigned char _data)
	{
	EEDATA = _data;
	EEADR = address;
	// start write sequence as described in datasheet, page 91
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.WREN = 1; // enable writes to data EEPROM
	INTCONbits.GIE = 0;  // disable interrupts
	EECON2 = 0x55;
	EECON2 = 0x0AA;
	EECON1bits.WR = 1;   // start writing
	while(EECON1bits.WR) asm("nop");
	//if(EECON1bits.WRERR) printf("ERROR: writing to EEPROM failed!n");
	EECON1bits.WREN = 0;
	INTCONbits.GIE = 1;  // enable interrupts
	}

/******************************************************************************/
/* FUNCIÓN:     fgetc(FILE*)                                                  */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:                                                                */
/******************************************************************************/
unsigned char ee_read_byte(unsigned char address)
	{
	EEADR = address;
	EECON1bits.CFGS = 0;
	EECON1bits.EEPGD = 0;
	EECON1bits.RD = 1;
	return EEDATA;
	}
