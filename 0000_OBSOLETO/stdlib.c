/******************************************************************************/
/* ARCHIVO:     stdlib.c                                                       */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCIÓN: -                                                             */
/* ÚLT. MODIF:  -                                                             */
/* COMENTARIO:  -                                                             */
/******************************************************************************/


/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/
#include <stdlib.h>
#include <stdio.h> //requiere definicion de NULL


/******************************************************************************/
/* DEFINICIÓN DE VARIABLES GLOBALES                                           */
/******************************************************************************/



int atoi(char *s)
   {
   int res=0; //Initialize result
   char sign=1; //Initialize sign as positive
   char i=0;

   if(s[0]=='-')
      {
      sign = -1;  
      i++;
      }
    for(;s[i]!=NULL;++i)
      {
      res=(res*10)+(s[i]-'0'); //Error del compilador: sin los parentesis, la funcion anda mal.
      }
   return sign*res;
   }



long int atol(char *s)
   {
   long int res=0; //Initialize result
   char sign=1; //Initialize sign as positive
   char i=0;

   if(s[0]=='-')
      {
      sign = -1;  
      i++;
      }
    for(;s[i]!=NULL;++i)
      {
      res=(res*10)+(s[i]-'0'); //Error del compilador: sin los parentesis, la funcion anda mal.
      }
   return sign*res;
   }

