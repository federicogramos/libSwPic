//******************************************************************************
// ARCHIVO:     x1w_lib.h
// AUTOR:       Federico Ramos
// ÚLT. MODIF:  10-12-2021 1507
// COMENTARIO:  Librería para comunicación 1 wire
//******************************************************************************


#ifndef __X1_WIRE_LIB_H
#define __X1_WIRE_LIB_H


//******************************************************************************
//PARA DHT11
//******************************************************************************
#define DHT11_RESPONSE_BYTES 5
#define DHT11_WAIT_FP()   while(X1_WIRE_1==0);
#define DHT11_WAIT_FN() while(X1_WIRE_1==1);

extern char dht11_mem[DHT11_RESPONSE_BYTES];

#define DHT_XX_CHECKSUM() (dht11_mem[0]+dht11_mem[2]==dht11_mem[4])



/////////////////////




//******************************************************************************
//PARA DS18B20
//******************************************************************************
#define X1W_DS18B20_SKIP 0xCC
#define X1W_DS18B20_CONVERT 0x44
#define X1W_DS18B20_READTEMP 0xBE


//******************************************************************************
//DEFINICION DE USUARIOS
//******************************************************************************
volatile bit X1_WIRE_0 @ ((unsigned)&GPIO*8)+5;
volatile bit X1_WIRE_0_DDR @ ((unsigned)&GPIO*8)+5;
//volatile bit X1_WIRE_1 @ ((unsigned)&PORTA*8)+3;
//volatile bit X1_WIRE_1_DDR @ ((unsigned)&TRISA*8)+3;


//volatile bit X1_WIRE_0 @ ((unsigned)&GPIO*8)+5;
//volatile bit X1_WIRE_0_DDR @ ((unsigned)&TRISIO*8)+5;


#define X1_WIRE_BUFLEN 8




//******************************************************************************
// DECLARACIÓN DE FUNCIONES
char x1w_rst(void);
void x1w_write_bit(char b);
char x1w_read_bit(void);
void x1w_write_byte(char data);
char x1w_read_byte(void);
char OWTouchByte(char data);
void OWBlock(unsigned char *data, char data_len);
char ReadPageMAC(void);
char x1w_dht11_get(void);
//******************************************************************************

#endif // __1WIRE_LIB_H