//==============================================================================
// Archivo: eeprom_16f.h
// Autor: Federico Ramos
// Modificado: 16-11-2023 1636
//==============================================================================


#ifndef __EEPROM16F_H
#define __EEPROM16F_H


//==============================================================================
// ARCHIVO QUE DEBE CREAR EL USUARIO: MAPA DE MEMORIA DE EEPROM
#include <eeprom16f_memAddresses.h>
//==============================================================================


//==============================================================================
// MACROS PARA MANEJO DE EEPROM
#define EEPROM_WRITE_CHAR(addr,var) {                     \
                                  eeprom_write(addr,var); \
                                  }
// EEPROM:  +------------+
// Address: |    0x00    |
//          +------------+
// Data:    |    BYTE    |
//          +------------+

#define EEPROM_READ_CHAR(addr,var) {                     \
                                   var=eeprom_read(addr);\
                                   }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

#define EEPROM_WRITE_INT(addr,var) {                                \
                                 eeprom_write(addr,GET_NUM_BYTE(1,var)); \
                                 eeprom_write(addr+1,GET_NUM_BYTE(0,var));\
                                 }
// EEPROM:  +------------+----------+
// Address: |    0x00    |   0x01   |
//          +------------+----------+
// Data:    |  HIGH BYTE | LOW BYTE |
//          +------------+----------+

#define EEPROM_READ_INT(addr,var) {                           \
                                  var=0x00;                   \
                                  var|=eeprom_read(addr)<<8;  \
                                  var|=eeprom_read(addr+1)<<0;\
                                  }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

#define EEPROM_WRITE_LONG_INT(addr,n) {                                 \
                                 eeprom_write(addr+0,GET_NUM_BYTE(3,n));\
                                 eeprom_write(addr+1,GET_NUM_BYTE(2,n));\
                                 eeprom_write(addr+2,GET_NUM_BYTE(1,n));\
                                 eeprom_write(addr+3,GET_NUM_BYTE(0,n));\
                                 }
// EEPROM:  +------------+----------+------------+----------+
// Address: |    0x00    |   0x01   |    0x02    |   0x03   |
//          +------------+----------+------------+----------+
// Data:    |   BYTE 3   |  BYTE 2  |   BYTE 1   |  BYTE 0  |
//          +------------+----------+------------+----------+

#define EEPROM_READ_LONG_INT(addr,var) {                                \
                                  var=0x0000L;                          \
                                  var|=(long)eeprom_read(addr+0)<<(8*3);\
                                  var|=(long)eeprom_read(addr+1)<<(8*2);\
                                  var|=(long)eeprom_read(addr+2)<<(8*1);\
                                  var|=(long)eeprom_read(addr+3)<<(8*0);\
                                  }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.

#define EEPROM_WRITE_SHORTLONG_INT(addr,n) {                            \
                                 eeprom_write(addr+0,GET_NUM_BYTE(2,n));\
                                 eeprom_write(addr+1,GET_NUM_BYTE(1,n));\
                                 eeprom_write(addr+2,GET_NUM_BYTE(0,n));\
                                 }
// EEPROM:  +------------+----------+------------+----------+
// Address: |    0x00    |   0x01   |    0x02    |   0x03   |
//          +------------+----------+------------+----------+
// Data:    |   BYTE 3   |  BYTE 2  |   BYTE 1   |  BYTE 0  |
//          +------------+----------+------------+----------+

#define EEPROM_READ_SHORTLONG_INT(addr,var) {                           \
                                  var=0x0000L;                          \
                                  var|=(long)eeprom_read(addr+0)<<(8*2);\
                                  var|=(long)eeprom_read(addr+1)<<(8*1);\
                                  var|=(long)eeprom_read(addr+2)<<(8*0);\
                                  }
// La variable que fue escrita con "EEPROM_WRITE_INT" puede ser recuperada con
// "EEPROM_READ_INT" y medida en una variable en RAM.


#endif // __EEPROM16F_H