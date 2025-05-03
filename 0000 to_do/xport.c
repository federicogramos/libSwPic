// xport.c                                                                    //
////////////////////////////////////////////////////////////////////////////////
#include <projectHeader.h>
#include <xport_lib.h>
#include <system.h>
#include <stdio.h>

char xportBuffer[XPORT_BUFSIZ]={0x00,0x00,0};//Null terminated {byte0,byte1,..}
FILE xportFile={
               _READ|_WRITE,
               &xportBuffer,
               &xportBuffer,
               &xportBuffer,
               XPORT_BUFSIZ,
               XPORT_BUFSIZ,
               XPORT_BUFSIZ
               };

void shiftChar(char c)
   {
   char i,aux;
   for(i=0;i<8;i++)
      {
      aux=c;
      DATA=BIT_GETVAL(aux,i);
      DATACLK=1;
      DATACLK=0;
      }
   }

void shiftOutputBytes()
   {
   char i,c;
   for(i=0;i<XPORT_BYTES;i++)
      {
      c=fgetc(&xportFile);
      shiftChar(c);
      }
   }

void xportDriver()
   {
   rewind(&xportFile);
   shiftOutputBytes();
   FFCLK=1;//muestra el nuevo valor en salidas
   FFCLK=0;
   }
