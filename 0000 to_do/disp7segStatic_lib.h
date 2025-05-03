//******************************************************************************
// ARCHIVO: disp7segStatic_lib.c
// AUTOR: Federico Ramos
// ÚLT. MODIF: 15-10-2021 1712
// COMENTARIO: -
//******************************************************************************


#ifndef __DISP7SEG_LIB_H
#define __DISP7SEG_LIB_H


//******************************************************************************
// INCLUDES
#include <disp7segStatic_pindef.h>
//******************************************************************************


//******************************************************************************
// DEFINICION DE PINES POR PARTE DEL USUARIO (ejemplo C:\0000 FEDE\16GB\0000 INTERIOR\PFP_TMP_11\sw main\0003 pwm\0000 pulsos)
//FGR: REQUISITOS, DEFINIR CONSTANTES
#define DISP7SEG_LENGTH 4
#define OFF_PERIODS 12 //FGR: CUANTO MAS GRANDE, MAS ATENUA BRILLO
#define DISP7SEG_NPREFIX 4
#define DISP7SEG_NSUFIX 4
//******************************************************************************


//******************************************************************************
//FGR: CONTABILIZA 1 CHAR MAS PARA EL NULL
#define DISP7SEG_MAX_STRING 14
//******************************************************************************


//******************************************************************************
//FGR: ESTRUCTURAS
typedef struct
	{
	char *str;
	char strOffs;
	char strLen;
	char mux_state;
	char titila_D0;
	char titila_D1;
	char titila_D2;
	char titila_D3;
	char d0_dp;
	char d1_dp;
	char d2_dp;
	char d3_dp;
	}t_disp7segStatic;
//******************************************************************************


//******************************************************************************
//FGR: GLOBALS
extern t_disp7segStatic disp;
//******************************************************************************


//******************************************************************************
// MACROS
//******************************************************************************


//******************************************************************************
//FGR: MACROS CONDICIONALES DEPENDIENDO N
// BASICAMENTE HACE LO MISMO QUE UN SWITCH CASE
#ifdef D7S_A_5
	#define DISP7SEG_IRQ_DRIVER()\
	{\
	D7S_A_0=0;
	D7S_A_1=0;
	D7S_A_2=0;
	D7S_A_3=0;
	D7S_A_4=0;
	D7S_A_5=0;
#else
	#ifdef D7S_A_4
		#define DISP7SEG_IRQ_DRIVER()\
		{\
		D7S_A_0=0;
		D7S_A_1=0;
		D7S_A_2=0;
		D7S_A_3=0;
		D7S_A_4=0;
		}
	#else
		#ifdef D7S_A_3
			#define DISP7SEG_IRQ_DRIVER()\
			{\
			D7S_A_0=0;\
			D7S_A_1=0;\
			D7S_A_2=0;\
			D7S_A_3=0;\
			if(disp.mux_state==(DISP7SEG_LENGTH+OFF_PERIODS)) disp.mux_state=0;\
			if(disp.mux_state<DISP7SEG_LENGTH)\
				{\
				if(disp.strOffs+disp.mux_state<4 || disp.strOffs+disp.mux_state>disp.strLen+3) disp7seg_char2pins(' ');\
				else disp7seg_char2pins(*(char*)(disp.str+disp.strOffs+disp.mux_state-4));\
				switch(disp.mux_state)\
					{\
					case 3: if(!(disp.titila_D0 && bitTitila)) {D7S_S_DP=!disp.d0_dp;D7S_A_0=1;} break;\
					case 2: if(!(disp.titila_D1 && bitTitila)) {D7S_S_DP=!disp.d1_dp;D7S_A_1=1;} break;\
					case 1: if(!(disp.titila_D2 && bitTitila)) {D7S_S_DP=!disp.d2_dp;D7S_A_2=1;} break;\
					case 0: if(!(disp.titila_D3 && bitTitila)) {D7S_S_DP=!disp.d3_dp;D7S_A_3=1;} break;\
					default: break;\
					}\
				}\
			disp.mux_state++;\
			}
		#else
			#ifdef D7S_A_2
				#define DISP7SEG_IRQ_DRIVER()\
				{\
				D7S_A_0=0;\
				D7S_A_1=0;\
				D7S_A_2=0;\
				if(disp.mux_state>(DISP7SEG_LENGTH+OFF_PERIODS)) disp.mux_state=0;\
				disp7seg_char2pins(*(disp.string+disp.strOffs+disp.mux_state));\
				switch(disp.mux_state)\
					{\
					case 0: D7S_A_0=1; break;\
					case 1: D7S_A_1=1; break;\
					case 2: D7S_A_2=1; break;\
					default: break;\
					}\
				disp.mux_state++;\
				}
			#else
				#ifdef D7S_A_1
					#define DISP7SEG_IRQ_DRIVER()\
					{\
					D7S_A_0=0;\
					D7S_A_1=0;\
					}
				#else
					#ifdef D7S_A_0
						#define DISP7SEG_IRQ_DRIVER()\
						{\
						D7S_A_0=0;\
						}
					#endif
				#endif
			#endif
		#endif
	#endif
#endif

//******************************************************************************
// DECLARACION DE FUNCIONES
void disp7seg_char2pins(char c);
//******************************************************************************


#endif//__DISP7SEG_LIB_H