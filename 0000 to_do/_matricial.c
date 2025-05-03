/******************************************************************************/
/* ARCHIVO:     matricial.c                                                   */
/* AUTOR:       Federico Ramos                                                */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  La presente librer�a implementa una funci�n kbhit(), la cual  */
/* tiene un comportamiento similar a la funci�n con mismo nombre de la        */
/* librer�a "conio.h". El prototipo de la funci�n kbhit() aqu� implementada,  */
/* se encuentra en "matricial.h".                                             */
/******************************************************************************/

/******************************************************************************/
/* ARCHIVOS DE ENCABEZAMIENTO UTILIZADOS                                      */
/******************************************************************************/

#include <projectHeader.h>

//#include "puertos.h"

// La inclusi�n de "matricial.h" debe ser siempre posterior a la de "puertos.h",
// ya que esta �ltima contiene la definici�n del tipo de dato PUERTO, el cual
// el cual se utiliza para declarar algunas variables externas contenidas en
// "matricial.h".
#include <matricial.h>

#include <stdio.h>

//#include "lcd.h"
//#include "delay.h"

#include <system.h>


/******************************************************************************/
/* DEFINICI�N DE VARIABLES GLOBALES SETEADAS POR EL USUARIO                   */
/******************************************************************************/
char tecBuffer[TEC_BUFSIZ];

FILE tecFile={
              _READ|_WRITE,
              &tecBuffer,
              &tecBuffer,
              &tecBuffer,
              0,
              0,
              TEC_BUFSIZ
              };


// Registro de las medidas anteriores del teclado. El teclado comienza con los
// botones sin apretar.
//char tec[FILS][COLS]={
//                     {-1,-1,-1,-1},
  //                   {-1,-1,-1,-1},
    //                 {-1,-1,-1,-1},
      //               {-1,-1,-1,-1}
        //             };

t_4bit_tec tec={-1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1,
                -1,-1,-1,-1
               };



/******************************************************************************/
/* DEFINICI�N DE VARIABLES GLOBALES                                           */
/******************************************************************************/

// Lecturas actuales del teclado.
//char med[FILS][COLS]=0;
t_bit_tec med;

// Incrementos para cuentas regresivas.
//char minc[FILS][COLS]=0;            
t_4bit_tec minc;

// Contiene la cantidad de teclas acumuladas en stdin.
char kbHitFlg;

/* Utilizada en las funciones para botones         */
/////////////////------> Eliminar, ya que no pertenece al teclado matricial.
//unsigned char buzzerDelay;


/******************************************************************************/
/* FUNCI�N:     initMatricial()                                               */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  Filas: salidas, columnas: entradas.                           */
/*              No es necesario que establezca el sentido de las salidas, ya  */
/*              que lo hace en cada invocaci�n del driver del teclado.        */
/******************************************************************************/

void initMatricial(void)
  {
  // Se habilitan los pulls en las columnas.
   RBPU=0;
   rewind(&tecFile);
  }

/******************************************************************************/
/* FIN FUNCI�N: initMatricial()                                               */
/******************************************************************************/

/******************************************************************************/
/* FUNCI�N:     procesarBoton()                                               */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

void procesarBoton(char i,char j)
  {
   char tecVal,medVal,mincVal;

   tecVal=getTec(i,j);
   medVal=getMed(i,j);
   mincVal=getMinc(i,j);

  // Si al bot�n lo soltaron � si lo apretaron.
    if(((tecVal==1)&&(medVal==1))||((tecVal==(char)-1)&&(medVal==0)))
    {

    // Si lo apretaron.
    if(medVal==!PULL_TYPE)
      {
      putTec(i,j,tecVal+(N_REBOTE+2));
      putMinc(i,j,-1);
//setBit(&buzzer,bitBuzzer);
//      buzzerDelay=15;

      // Carga en el stream el caracter apretado.
//      fputc(j<<4|i<<0,&tecFile);
      fputc(tec2ascii(i,j),&tecFile);




      // Se contabiliza una tecla m�s almacenada en el stream stdin.
      kbHitFlg++;
      }

    // Si lo soltaron.
    else
      {
      putTec(i,j,tecVal-(N_REBOTE+2));
      putMinc(i,j,1);
      }
    }
  }

/******************************************************************************/
/* FIN FUNCI�N: procesarBoton()                                               */
/******************************************************************************/

/******************************************************************************/
/* FIN FUNCI�N: kbhit()                                                       */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  Retorna siempre la cantidad de teclas almacenadas en el stdin */
/* que a�n no han sido recogidas por el usuario. Es decir, que retornar� 0    */
/* �nicamente en el caso en que no haya teclas nuevas para leer.              */
/* Inmediatamente luego de la consulta, decrementa el contador que            */
/* contabiliza los caracteres le�dos, por lo que el usuario, luego de un      */
/* kbhit() que retorne un valor no nulo, debe hacer la lectura de dicho       */
/* caracter (haciendo un fgetc()) ya que de otro modo se obtendr�a un         */
/* comportamiento erroneo. Una vez que kbhit() retorna 0, no hay problema con */
/* las siguientes invocaciones a kbhit().                                     */
/******************************************************************************/

int kbhit(void) {return (kbHitFlg>0)?kbHitFlg--:0;}

/******************************************************************************/
/* FIN FUNCI�N: kbhit()                                                       */
/******************************************************************************/

/******************************************************************************/
/* FUNCI�N:     analizarBoton()                                               */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

void analizarBoton(char i,char j)
  {
   char tecVal,mincVal;

   tecVal=getTec(i,j);
   mincVal=getMinc(i,j);

  // Si el bot�n se encuentra "quieto".
  if(mincVal==0)
    {

    // Directamente ya puede procesarlo.
    procesarBoton(i,j);
    }

  // Si a�n no se queda quieto.
  else
    {

    // Hace funcionar la cuenta regresiva.
    putTec(i,j,tecVal+mincVal);

    // Si la cuenta regresiva se pas�.
    if(tecVal==0)
      {

      // Reestablece el valor del bot�n quieto.
      putTec(i,j,tecVal-mincVal);

      // Desactiva la cuenta regresiva.
      putMinc(i,j,0);

      // Ahora con el bot�n quieto, procesa el bot�n.
      procesarBoton(i,j);
      }
    }
  }

/******************************************************************************/
/* FIN FUNCI�N: analizarBoton()                                               */
/******************************************************************************/

/******************************************************************************/
/* FUNCI�N:     driverTeclado()                                               */
/* PAR�METROS:  -                                                             */
/* DEVUELVE:    -                                                             */
/* DESCRIPCI�N: -                                                             */
/* �LT. MODIF:  14-09-2008                                                    */
/* COMENTARIO:  -                                                             */
/******************************************************************************/

void driverTeclado(void)
  {
  char aux,i,j;

  //Afuera del driver se lee, y adentro se escribe, por lo que el driver debe
  // estar encerrado entre 2 instrucciones "fflush()".
//  (void)fflush(stdin);

  // Si no existen caracteres pendientes para leer.
  if(kbHitFlg==0)
    {
    // Vuelve al inicio todos los punteros del buffer, ya que los datos que conten�a fueron le�dos.
    rewind(&tecFile);
    }

  // Recorre las filas.
  for(i=0;i<FILS;i++)
    {

    
   DDR_TEC=ALL_INPUT;
   // Fila i excita, el resto son entradas.
   BIT_CLR(DDR_TEC,i+4);//La fila que excita, la hago salida
   BIT_CLR(TEC,i+4);//La fila que excita, la pongo en 0
   asm("nop");//Es necesario, no creo que por error del compilador, pero si no es por eso, es para darle tiempo a cambiar las se�ales.

    // Toma muestra de las columnas de la fila i.
    aux=TEC;

    // Recorre las columnas.
    for(j=0;j<COLS;j++)         
      {
      // Coloca los elementos en la matr�z.
      putMed(i,j,BIT_GETVAL(aux,j)); 
      analizarBoton(i,j);
      }
    }

  // Dejo las filas en Hi-Z.
   DDR_TEC=ALL_INPUT;

  // Esto tiene que estar para que al hacer fgetc() levante del segmento la
  // informaci�n que antes de hacer fflush() se encontraba en el buffer.
//  (void)fflush(stdin); 
  }




char getTec(char i,char j)
{
char nElem,aux;

nElem=i*4+j;
switch(nElem)
   {
   case 0: aux=tec.f1c1; break;
   case 1: aux=tec.f1c2; break;
   case 2: aux=tec.f1c3; break;
   case 3: aux=tec.f1c4; break;
   case 4: aux=tec.f2c1; break;
   case 5: aux=tec.f2c2; break;
   case 6: aux=tec.f2c3; break;
   case 7: aux=tec.f2c4; break;
   case 8: aux=tec.f3c1; break;
   case 9: aux=tec.f3c2; break;
   case 10: aux=tec.f3c3; break;
   case 11: aux=tec.f3c4; break;
   case 12: aux=tec.f4c1; break;
   case 13: aux=tec.f4c2; break;
   case 14: aux=tec.f4c3; break;
   case 15: aux=tec.f4c4; break;
   }

return (BIT_GETVAL(aux,3)?(0xF0|aux):aux);
}

void putTec(char i,char j,char val)
{
char nElem;

nElem=i*4+j;
switch(nElem)
   {
   case 0: tec.f1c1=val; break;
   case 1: tec.f1c2=val; break;
   case 2: tec.f1c3=val; break;
   case 3: tec.f1c4=val; break;
   case 4: tec.f2c1=val; break;
   case 5: tec.f2c2=val; break;
   case 6: tec.f2c3=val; break;
   case 7: tec.f2c4=val; break;
   case 8: tec.f3c1=val; break;
   case 9: tec.f3c2=val; break;
   case 10: tec.f3c3=val; break;
   case 11: tec.f3c4=val; break;
   case 12: tec.f4c1=val; break;
   case 13: tec.f4c2=val; break;
   case 14: tec.f4c3=val; break;
   case 15: tec.f4c4=val; break;
   }
}

char getMed(char i,char j)
{
char nElem,aux;

nElem=i*4+j;
switch(nElem)
   {
   case 0: aux=med.f1c1; break;
   case 1: aux=med.f1c2; break;
   case 2: aux=med.f1c3; break;
   case 3: aux=med.f1c4; break;
   case 4: aux=med.f2c1; break;
   case 5: aux=med.f2c2; break;
   case 6: aux=med.f2c3; break;
   case 7: aux=med.f2c4; break;
   case 8: aux=med.f3c1; break;
   case 9: aux=med.f3c2; break;
   case 10: aux=med.f3c3; break;
   case 11: aux=med.f3c4; break;
   case 12: aux=med.f4c1; break;
   case 13: aux=med.f4c2; break;
   case 14: aux=med.f4c3; break;
   case 15: aux=med.f4c4; break;
   }

return (BIT_GETVAL(aux,3)?(0xF0|aux):aux);
}

void putMed(char i,char j,char val)
{
char nElem;

nElem=i*4+j;
switch(nElem)
   {
   case 0: med.f1c1=val; break;
   case 1: med.f1c2=val; break;
   case 2: med.f1c3=val; break;
   case 3: med.f1c4=val; break;
   case 4: med.f2c1=val; break;
   case 5: med.f2c2=val; break;
   case 6: med.f2c3=val; break;
   case 7: med.f2c4=val; break;
   case 8: med.f3c1=val; break;
   case 9: med.f3c2=val; break;
   case 10: med.f3c3=val; break;
   case 11: med.f3c4=val; break;
   case 12: med.f4c1=val; break;
   case 13: med.f4c2=val; break;
   case 14: med.f4c3=val; break;
   case 15: med.f4c4=val; break;
   }
}

char getMinc(char i,char j)
{
char nElem,aux;

nElem=i*4+j;
switch(nElem)
   {
   case 0: aux=minc.f1c1; break;
   case 1: aux=minc.f1c2; break;
   case 2: aux=minc.f1c3; break;
   case 3: aux=minc.f1c4; break;
   case 4: aux=minc.f2c1; break;
   case 5: aux=minc.f2c2; break;
   case 6: aux=minc.f2c3; break;
   case 7: aux=minc.f2c4; break;
   case 8: aux=minc.f3c1; break;
   case 9: aux=minc.f3c2; break;
   case 10: aux=minc.f3c3; break;
   case 11: aux=minc.f3c4; break;
   case 12: aux=minc.f4c1; break;
   case 13: aux=minc.f4c2; break;
   case 14: aux=minc.f4c3; break;
   case 15: aux=minc.f4c4; break;
   }

return (BIT_GETVAL(aux,3)?(0xF0|aux):aux);
}

void putMinc(char i,char j,char val)
{
char nElem;

nElem=i*4+j;
switch(nElem)
   {
   case 0: minc.f1c1=val; break;
   case 1: minc.f1c2=val; break;
   case 2: minc.f1c3=val; break;
   case 3: minc.f1c4=val; break;
   case 4: minc.f2c1=val; break;
   case 5: minc.f2c2=val; break;
   case 6: minc.f2c3=val; break;
   case 7: minc.f2c4=val; break;
   case 8: minc.f3c1=val; break;
   case 9: minc.f3c2=val; break;
   case 10: minc.f3c3=val; break;
   case 11: minc.f3c4=val; break;
   case 12: minc.f4c1=val; break;
   case 13: minc.f4c2=val; break;
   case 14: minc.f4c3=val; break;
   case 15: minc.f4c4=val; break;
   }
}


char tec2ascii(char i,char j)
{
char nElem,aux;

nElem=i*4+j;
switch(nElem)
   {
   case 0: aux='1'; break;
   case 1: aux='2'; break;
   case 2: aux='3'; break;
   case 3: aux='A'; break;
   case 4: aux='4'; break;
   case 5: aux='5'; break;
   case 6: aux='6'; break;
   case 7: aux='B'; break;
   case 8: aux='7'; break;
   case 9: aux='8'; break;
   case 10: aux='9'; break;
   case 11: aux='C'; break;
   case 12: aux='*'; break;
   case 13: aux='0'; break;
   case 14: aux='#'; break;
   case 15: aux='D'; break;
   }

return aux;
}



/******************************************************************************/
/* FIN FUNCI�N: driverTeclado()                                               */
/******************************************************************************/