//==============================================================================
// Archivo: / libSwPic/eeprom_18f.c
// Autor: Federico Ramos
// Modificado:  20250204 0116
//==============================================================================


// Headers =====================================================================
//==============================================================================

#include <projectHeader.h>
#include <eeprom18f.h>

// Archivos que debe crear el usuario ==========================================
// Objetivo: diseñar mapa de memoria.
// Nota: se pone aqui porque dentro de "eeprom_18f_lib.h" duplica reserva.
//==============================================================================

//#include <eeprom_18f_reserva.h>
#include <eeprom18f_memMap.h>



//==============================================================================
//==============================================================================

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

//==============================================================================
//==============================================================================

unsigned char ee_read_byte(unsigned char address)
    {
    EEADR = address;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDATA;
    }
