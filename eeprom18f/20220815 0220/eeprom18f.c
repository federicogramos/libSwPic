/*
 * @file / libSwPic/eeprom_18f.c
 * @author Federico Ramos <federico.g.ramos@gmail.com>
 * @version  20250204 0116
 */


/*
 * Headers
 */
#include <projectHeader.h>
#include <eeprom18f.h>



/*
 * @brief Write one byte de la eeprom.
 * @param addr = direccion a escribir.
 * @param dat = dato a escribir.
 */
void ee_write_byte(unsigned char addr, unsigned char dat)
    {
    EEDATA = dat;
    EEADR = addr;

    // Start write sequence as described in datasheet, page 91.
    EECON1bits.EEPGD = 0;
    EECON1bits.CFGS = 0;
    EECON1bits.WREN = 1;// Enable writes to data EEPROM.
    INTCONbits.GIE = 0;// Disable interrupts.
    EECON2 = 0x55;
    EECON2 = 0x0AA;
    EECON1bits.WR = 1;// Start writing.
    while(EECON1bits.WR) asm("nop");
    //if(EECON1bits.WRERR) printf("ERROR: writing to EEPROM failed!n");
    EECON1bits.WREN = 0;
    INTCONbits.GIE = 1;// Enable interrupts.
    }


/*
 * @brief Read one byte de la eeprom.
 * @param addr = direccion a leer.
 * @return Read byte.
 */
unsigned char ee_read_byte(unsigned char addr)
    {
    EEADR = addr;
    EECON1bits.CFGS = 0;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    return EEDATA;
    }
    
    
