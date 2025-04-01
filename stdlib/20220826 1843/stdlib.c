//******************************************************************************
//
// Archivo: stdlib.h
// Autor: Federico Ramos
// Modificado: 2023-04-21
//
//******************************************************************************



//******************************************************************************
// INCLUDE HEADERS

#include <stdlib.h>
#include <stdio.h>// Define NULL

//******************************************************************************



//******************************************************************************
//
// FUNCTION atoi(char *s)
//
//******************************************************************************

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

    // Error del compilador: sin los parentesis, la funcion anda mal.
    for(;s[i]!=NULL;++i) res=(res*10)+(s[i]-'0');

   return sign*res;
   }



//******************************************************************************
//
// FUNCTION atol(char *s)
//
//******************************************************************************

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



//*****************************************************************************
// FUNCTION ucharToStr(unsigned char num,char *str,char strLen)
//
// Recibe:
// - num: número a convertir
// - str: puntero a string donde quedará escrita la conversión
// - strLen: longitud del string que se quiere escribir (rellena con '0')
//
// Retorna: void
//
// Escribe unsigned num en string.
// - Alinea a la izquierda al número escrito.
// - Completa con ceros el espacio sobrante a la izquierda.
// - El string que escribe, no es NULL terminated.
//
// Ejemplo:
//               +--------+--------+--------+--------+--------+--------+
//               |    ?   |    ?   |    6   |    7   |    8   |    9   |
// num = 6789 => +--------+--------+--------+--------+--------+--------+
// strLen = 6    | str[0] | str[1] | str[2] | str[3] | str[4] | str[5] |
//               +--------+--------+--------+--------+--------+--------+
//*****************************************************************************

void ucharToStr(unsigned char num, char *str, char strLen)
	{
	char i;
	
	str+=strLen-1;
	for(i=0; i<strLen; i++)
		{
		*(str--)='0'+(num%10);
		num/=10;
		}
	}



//*****************************************************************************
//
// FUNCTION uToStr(unsigned int num, char *str, char strLen)
//
//*****************************************************************************

char *uToStr(unsigned int num, char *str, char strLen)
    {
    str+=strLen-1;
    *str=0;// NULL terminated

    do *(--str)='0'+(num%10);
    while((num/=10)!=0);

    return str;// return strcpy(strBack,str); Pasa en limpio el número convertido
    }