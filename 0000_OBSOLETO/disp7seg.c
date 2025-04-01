// disp7seg.c
////////////////////////////////////////////////////////////////////////////////
#include <projectHeader.h>
#include <disp7seg_lib.h>
#include <system.h>

#define DISP7SEG_LENGTH 3
#define DISP7SEG_MAX_LENGTH 10

typedef struct
	{
	char string[DISP7SEG_MAX_LENGTH];
	char *p2s;
	char mux_state;
	}t_disp7seg;

t_disp7seg disp;

void disp7seg_driver(void)
	{
	DISP7SEG_MULTIPLEX_NEXT();
	}

void disp7seg_refresh(void)
	{
	
	
	}

void disp7seg_char2pins(char c)
	{
	DISP_DP=1;
	switch(c)
		{
		case 'O':
		case '0':DISP_A=0;DISP_B=0;DISP_C=0;DISP_D=0;DISP_E=0;DISP_F=0;DISP_G=1;break;
		case 'I':
		case '1':DISP_A=1;DISP_B=0;DISP_C=0;DISP_D=1;DISP_E=1;DISP_F=1;DISP_G=1;break;
		case '2':DISP_A=0;DISP_B=0;DISP_C=1;DISP_D=0;DISP_E=0;DISP_F=1;DISP_G=0;break;
		case '3':DISP_A=0;DISP_B=0;DISP_C=0;DISP_D=0;DISP_E=1;DISP_F=1;DISP_G=0;break;
		case '4':DISP_A=1;DISP_B=0;DISP_C=0;DISP_D=1;DISP_E=1;DISP_F=0;DISP_G=0;break;
		case '5':DISP_A=0;DISP_B=1;DISP_C=0;DISP_D=0;DISP_E=1;DISP_F=0;DISP_G=0;break;
		case '6':DISP_A=0;DISP_B=1;DISP_C=0;DISP_D=0;DISP_E=0;DISP_F=0;DISP_G=0;break;
		case '7':DISP_A=0;DISP_B=0;DISP_C=0;DISP_D=1;DISP_E=1;DISP_F=0;DISP_G=1;break;
		case '8':DISP_A=0;DISP_B=0;DISP_C=0;DISP_D=0;DISP_E=0;DISP_F=0;DISP_G=0;break;
		case '9':DISP_A=0;DISP_B=0;DISP_C=0;DISP_D=0;DISP_E=1;DISP_F=0;DISP_G=0;break;
		case 'H':DISP_A=1;DISP_B=0;DISP_C=0;DISP_D=1;DISP_E=0;DISP_F=0;DISP_G=0;break;
		case 'n':DISP_A=1;DISP_B=1;DISP_C=0;DISP_D=1;DISP_E=0;DISP_F=1;DISP_G=0;break;
		case 'S':DISP_A=0;DISP_B=1;DISP_C=0;DISP_D=0;DISP_E=1;DISP_F=0;DISP_G=0;break;
		default:DISP_A=1;DISP_B=1;DISP_C=1;DISP_D=1;DISP_E=1;DISP_F=1;DISP_G=1;break;
		}
	}