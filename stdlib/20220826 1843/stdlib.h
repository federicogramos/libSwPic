//******************************************************************************
//
// Archivo: stdlib.h
// Autor: Federico Ramos
// Modificado: 2023-04-21
//
//******************************************************************************



#ifndef __STDLIB_H
#define __STDLIB_H




//********************************************************************************
// MACRO
// num: ojo, macro dice uchar to str pero n=num la crea como char.
// num es nro a dejar en p2str, que puede ser puntero o &array[]
// n=num de modo de no alterar num sino la variable temporal n
//********************************************************************************
#define UCHAR_TO_STR(num, p2str, strLen)                                       \
    {                                                                          \
    char u2s_i, u2s_n=num, *u2s_s=p2str;                                       \
    u2s_s += strLen-1;                                                         \
    for(u2s_i=0; u2s_i<strLen; u2s_i++)                                        \
        {                                                                      \
        *(u2s_s--) = '0' + (u2s_n%10);                                         \
        u2s_n /= 10;                                                           \
        }                                                                      \
    }                                                                          \



//******************************************************************************
//
// INCLUDE HEADERS
//
//******************************************************************************

int atoi(char *s);
long int atol(char *s);
void ucharToStr(unsigned char num, char *str, char strLen);
char *uToStr(unsigned int num,char *str,char strLen);


#endif // __STDLIB_H