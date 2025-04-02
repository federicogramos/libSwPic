//==============================================================================
// Archivo: /libSwPic/eeprom_18f_lib.h
// Autor: Federico Ramos
// Modificado:  20250204 1243
//
// Manejo de eeprom.
//
// Cómo debe usarse esta librería. Archivos que debe crear el usuario para defin
// ir características (crear dentro del directorio del proyecto):
// - eeprom_18f_reserva.h
//==============================================================================


#ifndef __EEPROM_18F_H
#define __EEPROM_18F_H


// Macros ======================================================================
//==============================================================================

// Addr  Data
// 0x00: ?? ?? ?? ..
#define EEPROM_WRITE_CHAR(addr, n)                                             \
    {                                                                          \
    ee_write_byte(addr, n);                                                    \
    }

#define EEPROM_READ_CHAR(addr, var)                                            \
    {                                                                          \
    var = ee_read_byte(addr);                                                  \
    }

// La variable q fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con "EE
// PROM_READ_INT" y metida en una variable en RAM.
// Address: |    0x00    |   0x01   | ..
// Data:    |  HIGH BYTE | LOW BYTE | ..
#define EEPROM_WRITE_INT(addr, n)                                              \
    {                                                                          \
    ee_write_byte(addr, HIGH_BYTE(n));                                         \
    ee_write_byte(addr + 1, LOW_BYTE(n));                                      \
    }

// La variable q fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con "EE
// PROM_READ_INT" y medida en una variable en RAM.
#define EEPROM_READ_INT(addr, var)                                             \
    {                                                                          \
    var = 0x00;                                                                \
    var |= ee_read_byte(addr) << 8;                                            \
    var |= ee_read_byte(addr + 1) << 0;                                        \
    }

// Address: |    0x00    |   0x01   |    0x02    |   0x03   |
// Data:    |   BYTE 3   |  BYTE 2  |   BYTE 1   |  BYTE 0  |
#define EEPROM_WRITE_LONG_INT(addr, n)                                         \
    {                                                                          \
    eeprom_write(addr+0,GET_NUM_BYTE(3, n));                                   \
    eeprom_write(addr+1,GET_NUM_BYTE(2, n));                                   \
    eeprom_write(addr+2,GET_NUM_BYTE(1, n));                                   \
    eeprom_write(addr+3,GET_NUM_BYTE(0, n));                                   \
    }

// La variable q fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con "EE
// PROM_READ_INT" y medida en una variable en RAM.
#define EEPROM_READ_LONG_INT(addr, var)                                        \
    {                                                                          \
    var = 0x0000L;                                                             \
    var |= (long)eeprom_read(addr + 0) << (8 * 3);                             \
    var |= (long)eeprom_read(addr + 1) << (8 * 2);                             \
    var |= (long)eeprom_read(addr + 2) << (8 * 1);                             \
    var |= (long)eeprom_read(addr + 3) << (8 * 0);                             \
    }


// Mapa de memoria de eeprom ===================================================
// Esto lo debo pasar a un archivo dentro del proyecto particular.
//==============================================================================

#define EEADDR_BRILLO_MEM 0
#define EEADDR_ADV_MODE_MEM 1
#define EEADDR_XLO_MEM 2
#define EEADDR_XUP_MEM 4
#define EEADDR_ELO_MEM 6
#define EEADDR_EUP_MEM 8
#define EEADDR_VLO_MEM 10
#define EEADDR_VUP_MEM 12
#define EEADDR_ESC_ENT_MEM 14
#define EEADDR_ESC_DEC_MEM 16


// Declaración de funciones ====================================================
//==============================================================================

void ee_write_byte(unsigned char address, unsigned char _data);
unsigned char ee_read_byte(unsigned char address);


#endif
   // __EEPROM_18F_H