//******************************************************************************
// ARCHIVO: thisProject.h
// AUTOR: Federico Ramos
// DESCRIPCI�N: Proyecto PFP_DRV_LED_STK_MAIN
// �LT. MODIF: 09-09-2022 14:33
//******************************************************************************


#ifndef __THIS_PROJECT_H
#define __THIS_PROJECT_H


/******************************************************************************/
/* CONSTANTES                                                                 */
/******************************************************************************/


/******************************************************************************/
/* MACROS QUE SINTETIZAN CONCEPTOS PARA HACER ALGO MAS CLARO EL CODIGO        */
/******************************************************************************/
#include <thisProjectMacros.h>


/******************************************************************************/
/* CONSTANTES ENUM                                                            */
/******************************************************************************/


/******************************************************************************/
/* ESTRUCTURAS                                                                */
/******************************************************************************/
typedef struct
	{
    char state;
    char pwmIncEncoder;//LO QUE LE VA A SUMAR O RESTAR, SEGUN SELECCION DE USUARIO: 1/10
	}t_handheld;


/******************************************************************************/
/* DECLARACION VARIABLES EXTERNAS                                             */
/******************************************************************************/
extern t_handheld handheld;


/******************************************************************************/
/* DECLARACI�N DE FUNCIONES                                                   */
/******************************************************************************/
void thisProjectInit(void);
void thisProject_driver(void);
void thisProject_get_event(void);

void showOnBoardDisplay(char digit,char timer);


/******************************************************************************/
/* FIN DE ARCHIVO                                                             */
/******************************************************************************/
#endif//__TIMER_DELAYS_H