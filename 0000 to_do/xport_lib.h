// xport_lib.h
////////////////////////////////////////////////////////////////////////////////
#ifndef __XPORT_LIB_H
#define __XPORT_LIB_H

#include <stdio.h>

// DEFINICIONES
#define XPORT_BYTES 2
#define XPORT_BUFSIZ (XPORT_BYTES+1)

char xportBuffer[XPORT_BUFSIZ] @ (unsigned)0x000;
bit lcdLight @ (unsigned)(&xportBuffer+0)*8+0;
bit lcdRs @ (unsigned)(&xportBuffer+1)*8+0;
bit lcdRw @ (unsigned)(&xportBuffer+1)*8+7;
bit lcdEn @ (unsigned)(&xportBuffer+1)*8+1;
bit lcdDat4 @ (unsigned)(&xportBuffer+1)*8+5;
bit lcdDat5 @ (unsigned)(&xportBuffer+1)*8+4;
bit lcdDat6 @ (unsigned)(&xportBuffer+1)*8+3;
bit lcdDat7 @ (unsigned)(&xportBuffer+1)*8+2;

// DECLARACIÓN DE VARIABLES
extern char xportBuffer[XPORT_BUFSIZ];
extern FILE xportFile;

// DECLARACIÓN DE FUNCIONES
void xportDriver();
void shiftOutputBytes();
void shiftChar(char c);

#endif//__XPORT_LIB_H