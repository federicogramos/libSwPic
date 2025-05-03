//******************************************************************************
// ARCHIVO: disp7segStatic.c
// AUTOR: Federico Ramos
// ÚLT. MODIF: 15-10-2021 1631
// COMENTARIO: -
//******************************************************************************

//******************************************************************************
// INCLUDES
#include <projectHeader.h>
#include <disp7segStatic_lib.h>
#include <system.h>
//******************************************************************************




//******************************************************************************
// VARIABLES GLOBALES
t_disp7segStatic disp;
//******************************************************************************

//******************************************************************************
// FUNCTION: disp7segStatic_char2pins()
// COMENTARIO: Segmentos = minusculas / Letras = mayusculas
//******************************************************************************
void disp7segStatic_char2pins(char c)
	{
	//D7S_S_DP=1;
	//switch(c)
        {
        /*case '-':D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=1;D7S_S_E=1;D7S_S_F=1;D7S_S_G=0;break;
        case 'O':
        case '0':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
        case 'I':
        case '1':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=1;D7S_S_F=1;D7S_S_G=1;break;
        case '2':D7S_S_A=0;D7S_S_B=0;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case '3':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=1;D7S_S_F=1;D7S_S_G=0;break;
		case '4':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;
        case '5':D7S_S_A=0;D7S_S_B=1;D7S_S_C=0;D7S_S_D=0;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;
        case 'G':
        case '6':D7S_S_A=0;D7S_S_B=1;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case '7':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=1;D7S_S_F=0;D7S_S_G=1;break;
        case '8':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case '9':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;
        case 'a':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case 'A':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'b':D7S_S_A=1;D7S_S_B=1;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'c':D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case 'C':D7S_S_A=0;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
        case 'D':
        case 'd':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case 'e':D7S_S_A=0;D7S_S_B=0;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'E':D7S_S_A=0;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'F':D7S_S_A=0;D7S_S_B=1;D7S_S_C=1;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'H':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'i':D7S_S_A=1;D7S_S_B=1;D7S_S_C=0;D7S_S_D=1;D7S_S_E=1;D7S_S_F=1;D7S_S_G=1;break;
        case 'J':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=1;break;
        case 'L':D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
        case 'm':
        case 'n':D7S_S_A=1;D7S_S_B=1;D7S_S_C=0;D7S_S_D=1;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case 'M':
        case 'N':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
        case 'P':D7S_S_A=0;D7S_S_B=0;D7S_S_C=1;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'q':D7S_S_A=0;D7S_S_B=0;D7S_S_C=0;D7S_S_D=1;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;
        case 'r':D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=1;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case 'R':D7S_S_A=0;D7S_S_B=1;D7S_S_C=1;D7S_S_D=1;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
        case 's':
        case 'S':D7S_S_A=0;D7S_S_B=1;D7S_S_C=0;D7S_S_D=0;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;
		case 'T':        
		case 't':D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=0;break;
        case 'v':
        case 'u':D7S_S_A=1;D7S_S_B=1;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=1;break;
        case 'U':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=0;D7S_S_F=0;D7S_S_G=1;break;
		case 'y':
        case 'Y':D7S_S_A=1;D7S_S_B=0;D7S_S_C=0;D7S_S_D=0;D7S_S_E=1;D7S_S_F=0;D7S_S_G=0;break;  
		case 'Z':D7S_S_A=0;D7S_S_B=0;D7S_S_C=1;D7S_S_D=0;D7S_S_E=0;D7S_S_F=1;D7S_S_G=0;break;
        case '#':D7S_S_A=0;D7S_S_B=1;D7S_S_C=1;D7S_S_D=0;D7S_S_E=1;D7S_S_F=1;D7S_S_G=0;break;      
        default:D7S_S_A=1;D7S_S_B=1;D7S_S_C=1;D7S_S_D=1;D7S_S_E=1;D7S_S_F=1;D7S_S_G=1;break;
*/
        }
	}
