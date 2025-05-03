/******************************************************************************/
/* ARCHIVO:     matricial.h                                                   */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

#ifndef __MATRICIAL_H
#define __MATRICIAL_H

/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/


/******************************************************************************/
/* DEFINICIÓN DE CONSTANTES SETEABLES POR EL USUARIO                          */
/******************************************************************************/

#define F1_PIN PORTAbits.RA3
#define F2_PIN PORTAbits.RA4
#define F3_PIN PORTAbits.RA5
#define F4_PIN PORTEbits.RE0
#define C1_PIN PORTEbits.RE3
#define C2_PIN PORTAbits.RA0
#define C3_PIN PORTAbits.RA1
#define C4_PIN PORTAbits.RA2

#define F1_DDR_PIN TRISA3
#define F2_DDR_PIN TRISA4
#define F3_DDR_PIN TRISA5
#define F4_DDR_PIN TRISE0
#define C1_DDR_PIN TRISE3
#define C2_DDR_PIN TRISA0
#define C3_DDR_PIN TRISA1
#define C4_DDR_PIN TRISA2

//i,j = fila,columna
#define TEC_11 '1'
#define TEC_12 '2'
#define TEC_13 '3'
#define TEC_14 'A'
#define TEC_21 '4'
#define TEC_22 '5'
#define TEC_23 '6'
#define TEC_24 'B'
#define TEC_31 '7'
#define TEC_32 '8'
#define TEC_33 '9'
#define TEC_34 'C'
#define TEC_41 '*'
#define TEC_42 '0'
#define TEC_43 '#'
#define TEC_44 'D'


// CONSTANTES NO SETEABLES

#define NFILS 4
#define NCOLS 4

//Invocacion driver = 2.5ms
#define ANTIREBOTE_COUNT 80

// 1: pull-up, 0:pull-down.
#define PULL_TYPE 1

// Cantidad de períodos de muestreo ignorados por el rebote. Un número que de
// 0.15s ó 0.2s está bien.
#define N_REBOTE  0

/******************************************************************************/
/* DECLARACIÓN DE MACROS                                                   */
/******************************************************************************/

#define TEC_DDR_FIL(inOut,fil) {                                   \
                               switch(fil)                         \
                                   {                               \
                                   case 1: F1_DDR_PIN=inOut; break;\
                                   case 2: F2_DDR_PIN=inOut; break;\
                                   case 3: F3_DDR_PIN=inOut; break;\
                                   case 4: F4_DDR_PIN=inOut;       \
                                   }                               \
                               }


#define TEC_COL_READ(var,col) {                            \
                              switch(col)                  \
                                 {                         \
                                 case 1: var=C1_PIN; break;\
                                 case 2: var=C2_PIN; break;\
                                 case 3: var=C3_PIN; break;\
                                 case 4: var=C4_PIN;       \
                                 }                         \
                              }

#define TEC_COL(col) (col==1?C1_PIN:col==2?C2_PIN:col==3?C3_PIN:C4_PIN)

#define TEC_FIL_CLR(fil) {                          \
                         switch(fil)                \
                            {                       \
                            case 1: F1_PIN=0; break;\
                            case 2: F2_PIN=0; break;\
                            case 3: F3_PIN=0; break;\
                            case 4: F4_PIN=0;       \
                            }                       \
                         }



/******************************************************************************/
/* DECLARACIÓN DE FUNCIONES                                                   */
/******************************************************************************/


//void procesarBoton(char i,char j);
//void analizarBoton(char i,char j);
void driverTeclado(void);
char kbhit(void);

//char getTec(char i,char j);
//void putTec(char i,char j,char val);

//char getMed(char i,char j);
//void putMed(char i,char j,char val);

//char getMinc(char i,char j);
//void putMinc(char i,char j,char val);

char tec2ascii(char tecla);
char ascii2tec(char ascii);

char getchar(void);
void ungetchar(char c);

char scanf(char *fmt, ...);

// Change code section to DEFAULT.
//#pragma CODE_SEG DEFAULT

// __MATRICIAL_H
#endif
