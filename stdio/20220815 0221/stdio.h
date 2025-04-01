/******************************************************************************/
/* ARCHIVO:     stdio.h                                                       */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


#ifndef __STDIO_H
#define __STDIO_H


/******************************************************************************/
/* DEFINICI�N DE CONSTANTES                                                   */
/******************************************************************************/
#define _FFULL    (1<<0)      /* Notifica error: trat� de meter datos en un   */
                              /* archivo que alcanz� su capacidad m�xima      */
#define _FEMPTY   (1<<1)      /* Notifica error: intent� extraer datos de un  */
                              /* archivo vac�o                                */
#define _FERR     (1<<2)      /* Notifica error: error                        */

enum e_mode_fseek{SEEK_END,SEEK_CUR,SEEK_SET}; //Modo para la funci�n fseek()

#define EOF       (-1)
#define NULL      0

#define _READ     (1<<0)      /* FILE flag: archivo abierto para lectura      */
#define _WRITE    (1<<1)      /* FILE flag: archivo abierto para escritura    */
#define _UNBUF    (1<<2)      /* FILE flag: archivo sin buffer                */
#define _EOF      (1<<3)      /* FILE flag: ocurri� fin de archivo (EOF)      */
#define _ERR      (1<<4)      /* FILE flag: ocurri� un error en este archivo  */

//#define MAX_FPRINTF_INT 7 //16bit: 5char + signo + NULL
//#define MAX_FPRINTF_INT 10 //24bit: 8char + signo + NULL
#define MAX_FPRINTF_INT 12 //32bit: 10char + signo + NULL

/******************************************************************************/
/* ESTRUCTURA:  FILE                                                          */
/* DESCRIPCI�N: Contiene variables que se necesitan para implementar una      */
/*              cola, y otras variables accesorias.                           */
/* �LT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/
typedef struct
  {
  char flg;  /* Modo de acceso al archivo                                     */
  char *nxr; /* Address donde escribir� del buffer                            */
  char *nxw; /* Address que leer� del buffer                                  */
  char *bas; /* Apunta al primer byte de la memoria reservada para buffer     */
  char nr;    /* Cantidad de bytes que existen para leer en el buffer          */
  char nw;    /* Cantidad de bytes que restan para escribir en el buffer       */
  char bufsiz;
  }FILE;


/******************************************************************************/
/* DECLARACI�N DE VARIABLES EXTERNAS                                          */
/******************************************************************************/


/******************************************************************************/
/* DECLARACI�N DE FUNCIONES                                                   */
/******************************************************************************/
char fputc(char c, FILE *stream);
char fgetc(FILE *stream);
void fseek(FILE *fp,int offset,int mode);
void unget(FILE *stream);

//char ferror(FILE *stream);
//char feof(FILE *stream);

void fprintf(FILE *fp,char *fmt,...);
void fprinti(FILE *fp,char *str);

char *intToStr(int num,char *str,char strLen);
char *longToStr(long num,char *str,char strLen);


/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

#define rewind(fp) fseek(fp,0,SEEK_SET)

//#define getchar()  fgetc(stdin)
//#define putchar(c) fputc((c),stdout)




#endif /* __STDIO_H                                                           */
