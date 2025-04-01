


#ifndef __STRING_H
#define __STRING_H



//********************************************************************************
// CREADA PORQUE LA FUNCIÓN STRLEN INDICABA QUE "POSSIBLE STACK OVERFLOW"
// INVOCACIÓN DE MACRO DEBE SER AL TOPE DE LA FUNCIÓN, PORQUE TIENE DEFINICIÓN DE VARIABLES LOCALES.
// Lo que hace es lo siguiente: result=strlen(string)
// USADA EN disp7segMux_scroll_charString() PORQUE USANDO LA FSM INDICA "POSSIBLE STACK OVERFLOW"
//********************************************************************************

#undef STRLEN   //Evita: 107 redefining preprocessor macro "STRLEN"

#define STRLEN(string,result) \
    char *s=string, result;   \
    while(*s) s++;            \
    result=(int)s-(int)string;\
//casteo porque ha tirado siguiente error en un caso: pointer operands to "-" must reference the same array



//********************************************************************************
// MACRO
// num: ojo, macro dice uchar to str pero n=num la crea como char.
// num es nro a dejar en p2str, que puede ser puntero o &array[]
// n=num de modo de no alterar num sino la variable temporal n
//********************************************************************************
#define UCHAR_TO_STR(num,p2str,strLen)  \
	{                                   \
    char i,n=num,*s=p2str;              \
	s+=strLen-1;                        \
	for(i=0;i<strLen;i++)               \
		{                               \
		*(s--)='0'+(n%10);              \
		n/=10;                          \
		}                               \
	}                                   \

#define UCHAR_TO_STR_V2(num,p2str,strLen)  \
	{                                   \
    char i,n=num,*s=p2str;              \
	s+=strLen-1;                        \
	for(i=0;i<strLen;i++)               \
		{                               \
		*(s--)='0'+(n%10);              \
		n/=10;                          \
		}                               \
	}                                   \




#endif // __STRING_H