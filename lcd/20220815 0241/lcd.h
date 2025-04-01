//****************************************************************************
// ARCHIVO: lcd_lib.h
// AUTOR: Federico Ramos
// ULT. MODIF: 28-08-2022
//****************************************************************************


#ifndef __LCD_LIB_H
#define __LCD_LIB_H


//****************************************************************************
// INCLUDES
#include <stdio.h>
//****************************************************************************


//****************************************************************************
// CONSTANTES LIBRERÍA
//****************************************************************************
#define LCD_BUFSIZ (LCD_LINES*LCD_LENGTH+1)
#define LCD_NIBBLE_SEND_INSTR 0
#define LCD_NIBBLE_SEND_DATA 1


//****************************************************************************
// USER DEFINITIONS
#include <lcd_user_definitions.h>
//****************************************************************************

//****************************************************************************
// DECLARACIÓN DE FUNCIONES
void lcdFsmInit(void);
void lcdFsmParser(void);
void lcdNibbleSend(char mode,char command);
//****************************************************************************


//****************************************************************************
// LCD EVENTOS
//****************************************************************************
// No event se usa por defecto para enviar a la fsm, en el caso de que no ocurra
// nada. Dado que NO_EVENT es distinto a cualquier otro evento que pueda
// ocurrir en cualquier circunstancia, indefectiblemente la fsm llegará a
// TABLE_END y ejecutará esa acción, es decir, justo lo que se quería hacer.
enum e_lcdEvent
    {
    LCD_EVENT_UNFINISHED,
    LCD_EVENT_TIMEOUT_30MS,
    LCD_EVENT_TIMEOUT_30MS_SKIP_DISPLAY_REFRESH,
    LCD_EVENT_REFRESH_FINISHED,
    LCD_EVENT_FIRST_LINE_FINISHED,
    LCD_EVENT_TABLE_END
    };


//****************************************************************************
// LCD ESTADOs
//****************************************************************************
enum e_lcdState
    {
    LCD_STATE_WAIT_TO_SET_DATA_LENGTH,
    LCD_STATE_WAIT_TO_CLEAR_DISPLAY,
    LCD_STATE_WAIT_TO_SET_ENTRY_MODE,
    LCD_STATE_WAIT_TO_SET_VISIBILITY,
    LCD_STATE_WAIT_FOR_REFRESH,
    LCD_STATE_COMMAND_FIRST_LINE,
    LCD_STATE_COMMAND_SECOND_LINE,
    LCD_STATE_CANT_STATES
    };


//****************************************************************************
// LCD ACCIONES
//****************************************************************************
enum e_lcdAction
    {
    LCD_ACTION_SET_DATA_LENGTH,
    LCD_ACTION_CLEAR_DISPLAY,
    LCD_ACTION_SET_ENTRY_MODE,
    LCD_ACTION_SET_VISIBILITY,
    LCD_ACTION_REWIND,
    LCD_ACTION_SEND_CHARACTER,
    LCD_ACTION_INIT_TMR_30MS,
    LCD_ACTION_START_LCD_SECOND_LINE,
    LCD_ACTION_SET_CURSOR_POSITION,
    LCD_ACTION_DO_NOTHING
    };

//****************************************************************************
// COMANDOS LCD
//****************************************************************************
#define LCD_CMD_FUNCTION 0x20 /* Comando functionSet (con las opciones=0)     */
#define LCD_CMD_VIS      0x08 /* Comando displayControl (con las opciones=0)  */
#define LCD_CMD_ENTRYM   0x04 /* Comando entryModeSet (con las opciones=0)    */
#define LCD_CMD_CLRDISP  0x01 /* Comando clearDisplay                         */
#define LCD_CMD_RETHOME  0x02 /* Comando returnHome                           */
#define LCD_CMD_SETDDRAM 0x80 /* Comando para establecer address de la DDRAM  */
#define LCD_8B_IF        0x10 /* Opción de functionSet: 8 bit interface       */
#define LCD_4B_IF        0x00 /* Opción de functionSet: 4 bit interface       */
#define LCD_2_DL         0x08 /* Opción de functionSet: 2 display lines       */
#define LCD_1_DL         0x00 /* Opción de functionSet: 1 line display        */
#define LCD_5X10D        0x04 /* Opción de functionSet: 5x10 dot font         */
#define LCD_5X8D         0x00 /* Opción de functionSet: 5x8 dot font          */

//****************************************************************************
// DEFINICION ESTRUCTURAS
//****************************************************************************
typedef const struct t_lcdTransition
//typedef struct t_lcdTransition
    {
    char event;
    char action;
    char nextState;
    }t_lcdState;

typedef struct
    {
    unsigned visibility:1;              //Seteo Visibility: display visibility
    unsigned cursorVisibility:1;        //Seteo Visibility: cursor visibility
    unsigned cursorBlink:1;             //Seteo Visibility: position blinking
    unsigned cursorDirection:1;         //Seteo Entry Mode: cursor direction
    unsigned shift:1;                   //Seteo Entry Mode: display shift
    unsigned visibility_refresh:1;      //Flag Seteo Visibility: cursor visibility
    unsigned cursorVisibility_refresh:1;//Flag Seteo Visibility: cursor visibility
    unsigned cursorBlink_refresh:1;     //Flag Seteo Visibility: position blinking
    unsigned cursorDirection_refresh:1; //Flag Seteo Entry Mode: cursor direction
    unsigned shift_refresh:1;           //Flag Seteo Entry Mode: display shift
    unsigned display_refresh:1;         //Flag display dirty (texto)

    unsigned cursor_position_refresh:1; //Cursor dirty flag
    unsigned cursor_position_x;         //Cursor column
    unsigned cursor_position_y;         //Cursor line
    }t_lcdSettings;


//****************************************************************************
// LCD MACROS
//****************************************************************************
#define LCD_SEND_COMMAND(comm)\
    {\
    lcdNibbleSend(LCD_NIBBLE_SEND_INSTR,(comm)>>4);\
    lcdNibbleSend(LCD_NIBBLE_SEND_INSTR,(comm)>>0);\
    }

#define LCD_SEND_DATA(data)\
    {\
    lcdNibbleSend(LCD_NIBBLE_SEND_DATA,(data)>>4);\
    lcdNibbleSend(LCD_NIBBLE_SEND_DATA,(data)>>0);\
    }

#define LCD_SET_DDRAM_ADDR(addr) LCD_SEND_COMMAND(LCD_CMD_SETDDRAM|addr)

#define DISP_VIS_ON()\
    {\
    lcdSettings.visibility=1;\
    lcdSettings.visibility_refresh=1;\
    }

#define LCD_CURSOR_VISIBILITY_ON()\
    {\
    lcdSettings.cursorVisibility=1;\
    lcdSettings.cursorVisibility_refresh=1;\
    }

#define LCD_CURSOR_VISIBILITY_OFF()\
    {\
    lcdSettings.cursorVisibility=1;\
    lcdSettings.cursorVisibility_refresh=1;\
    }

#define LCD_CURSOR_BLINK_ON()\
    {\
    lcdSettings.cursorBlink=1;\
    lcdSettings.cursorBlink_refresh=1;\
    }

#define LCD_CURSOR_BLINK_OFF()\
    {\
    lcdSettings.cursorBlink=1;\
    lcdSettings.cursorBlink_refresh=1;\
    }

#define LCD_CURSOR_POSITION(x,y)\
    {\
    lcdSettings.cursor_position_x=x;\
    lcdSettings.cursor_position_y=y;\
    lcdSettings.cursor_position_refresh=1;\
    }

//#define lcdSettings.curVis                   /* Seteo Visibility: cursorVisibility                       */
//#define lcdSettings.blink                   /* Seteo Visibility: positionBlinking                       */
//#define lcdSettings.incDec                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.shift                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.bkLight                   /* Seteo Backlight*/

//#define DISP_VIS_OFF() lcdSettings.dispVis=0                   /* Seteo Visibility: displayVisibility                      */
//#define lcdSettings.curVis                   /* Seteo Visibility: cursorVisibility                       */
//#define lcdSettings.blink                   /* Seteo Visibility: positionBlinking                       */
//#define lcdSettings.incDec                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.shift                   /* Seteo Entry Mode: displayShifts                          */
//#define lcdSettings.bkLight                   /* Seteo Backlight*/


extern char lcdBuffer[LCD_BUFSIZ];
extern FILE lcdFile;
extern t_lcdSettings lcdSettings;

#endif // __LCD_LIB_H