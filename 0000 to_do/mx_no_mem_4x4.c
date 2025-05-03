/******************************************************************************/
/* ARCHIVO:     matricial.c                                                   */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  10-08-2016                                                    */
/* COMENTARIO:  La presente librería implementa una función kbhit(), la cual  */
/* tiene un comportamiento similar a la función con mismo nombre de la        */
/* librería "conio.h". El prototipo de la función kbhit() aquí implementada,  */
/* se encuentra en "matricial.h".                                             */
/******************************************************************************/

/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/

#include <projectHeader.h>
#include <system.h> //Contiene definicion de OUTPUT usada en mx_no_mem_4x4
#include <mx_no_mem_4x4.h>
#include <stdarg.h>
#include <ctype.h>
#include <lcd_lib.h>
#include<string.h>
#include<stdlib.h>

#define MAX_SCANF_STRING 9 //max field width
#define SCANF_WHITESPACE_CHAR '#'
#define SCANF_BACKSPACE_CHAR '*'
#define SCANF_NEGATIVE_CHAR '-'

#define SCANF_MAX_DEFAULT_WIDTH 9

#define SCANF_ECHO_STREAM lcdFile
//Echo stream nunca es de lectura porque lo leen en la interrupcion para refrescar la pantalla del usuario, pero siempre al salir lo deja como de escritura.
//scanf usa el puntero de escritura, pero no modifica el de lectura.

/******************************************************************************/
/* DEFINICIÓN DE VARIABLES GLOBALES                                           */
/******************************************************************************/
char i=1,j=1; //Necesario para indicar que primera tecla a chequear es 1,1
char antirebote;
char kbHitFlg; //Valor de la tecla si se presiono algo. 0=ninguna

/******************************************************************************/
/* FIN FUNCIÓN: kbhit()                                                       */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  14-09-2008                                                    */
/* COMENTARIO: 
/******************************************************************************/

char kbhit(void) {return kbHitFlg;}
//Solo se borra luego de hacer getchar()

/******************************************************************************/
/* FIN FUNCIÓN: kbhit()                                                       */
/******************************************************************************/


/******************************************************************************/
/* FUNCIÓN:     driverTeclado()                                               */
/* PARÁMETROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

void driverTeclado(void)
   {
   char aux;

   if(antirebote) antirebote--;
   else
      {
      aux=TEC_COL(j);
      TEC_DDR_FIL(INPUT,i); //La fila que excita, la pongo en Hi-Z

      if(!aux) //Boton apretado es aux=0
         {
         kbHitFlg=i<<4|j;
         antirebote=ANTIREBOTE_COUNT;
         }

      if(++j>NCOLS)
         {
         j=1;
         if(++i>NFILS) i=1;
         }

      //Fila i excita, el resto son entradas. Prepara siguiente boton.
      TEC_DDR_FIL(OUTPUT,i);//La fila que excita, la hago salida
      TEC_FIL_CLR(i);//La fila que excita, la pongo en 0 porque hay pull-ups
      }
   }

char tec2ascii(char tecla)
{
char aux;

switch(tecla)
   {
   case 0x11: aux=TEC_11; break;
   case 0x12: aux=TEC_12; break;
   case 0x13: aux=TEC_13; break;
   case 0x14: aux=TEC_14; break;
   case 0x21: aux=TEC_21; break;
   case 0x22: aux=TEC_22; break;
   case 0x23: aux=TEC_23; break;
   case 0x24: aux=TEC_24; break;
   case 0x31: aux=TEC_31; break;
   case 0x32: aux=TEC_32; break;
   case 0x33: aux=TEC_33; break;
   case 0x34: aux=TEC_34; break;
   case 0x41: aux=TEC_41; break;
   case 0x42: aux=TEC_42; break;
   case 0x43: aux=TEC_43; break;
   case 0x44: aux=TEC_44; break;
   default: aux='?';
   }
return aux;
}

char ascii2tec(char ascii)
{
char aux;

switch(ascii)
   {
   case TEC_11: aux=0x11; break;
   case TEC_12: aux=0x12; break;
   case TEC_13: aux=0x13; break;
   case TEC_14: aux=0x14; break;
   case TEC_21: aux=0x21; break;
   case TEC_22: aux=0x22; break;
   case TEC_23: aux=0x23; break;
   case TEC_24: aux=0x24; break;
   case TEC_31: aux=0x31; break;
   case TEC_32: aux=0x32; break;
   case TEC_33: aux=0x33; break;
   case TEC_34: aux=0x34; break;
   case TEC_41: aux=0x41; break;
   case TEC_42: aux=0x42; break;
   case TEC_43: aux=0x43; break;
   case TEC_44: aux=0x44; break;
   }
return aux;
}

//Lee del stdin
char getchar(void)
   {
   char aux;

   while(kbHitFlg==0);
   aux=tec2ascii(kbHitFlg);
   kbHitFlg=0;

   return aux;
   }

void ungetchar(char c)
   {
   kbHitFlg=ascii2tec(c);
   }

/******************************************************************************/
/* FIN FUNCIÓN: driverTeclado()                                               */
/******************************************************************************/


//Always outputs to stdout and also saves the formatted input according to the format specifiers.
// In contrast to standard function, it does not return the total number of items filled



char scanf(char *fmt, ...)
   {
   va_list ap; //Puntero de argumentos
   char str[MAX_SCANF_STRING],n=0,widthCounter;
   char width;
   char *p2str,*p;

   va_start(ap, fmt); //Se hace que ap apunte al primer argumento sin nombre
   for(p=fmt;*p;p++)
      {
      if(*p!='%')
         {
         //tendria que comparar que el fmt sea igual al ingreso
         continue;
         }
      if(isdigit(*++p)) width=*p-'0';
      else
         {
         width=SCANF_MAX_DEFAULT_WIDTH;
         p--;
         }
      widthCounter=0;
      switch(*++p)
         {
         case 'l':
         case 'd':
         case 'i':
            p2str=str;
            while((*p2str=getchar())!=SCANF_WHITESPACE_CHAR)
               {
               if(*p2str==SCANF_BACKSPACE_CHAR && widthCounter>0)
                  {
                  fseek(&SCANF_ECHO_STREAM,-1,SEEK_CUR);
                  fputc(' ',&SCANF_ECHO_STREAM);
                  fseek(&SCANF_ECHO_STREAM,-1,SEEK_CUR);
                  widthCounter--;
                  p2str--;
                  }
               else if(isdigit(*p2str) && widthCounter<width)
                  {
                  fputc(*p2str,&SCANF_ECHO_STREAM);
                  widthCounter++;
                  p2str++;
                  }
               }
            *p2str=NULL;
            if(*p=='l')
               {
               p++;
               *va_arg(ap,long int*)=atol(str);
               }
            else
               {
               *va_arg(ap,int*)=atoi(str);
               }
            break;
         default:
            //(void)fputc(*p,fp);
            break;
         }
      }
   va_end(ap);
   return n;
   }


