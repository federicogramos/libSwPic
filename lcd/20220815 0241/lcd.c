//****************************************************************************
// ARCHIVO: lcd.c
// AUTOR: Federico Ramos
// LT. MODIF: 28-08-2022
// COMENTARIO: ORIGINALMENTE, LA FSM DE ESTA LIBRERÍA ESTABA ESCRITA CON
// PUNTEROS. TUVE ALGUNOS PROBLEMAS PORQUE USABA LOS ADDRESSES PARA DETERMINAR
// ESTADOS, Y A VECES SEGÚN LA ZONA DE MEMORIA DONDE SE UBICABA EL CÓDIGO
// CUANDO LA TABLA DE ESTADO SE PONÍA COMO "CONST" GENERABA ERRORES CUANDO
// HACÍA COMPARACIONES CON PUNEROS. POR ESO, YA NO SE USAN PUNTEROS, SINO
// ARRAYS.
//****************************************************************************


//****************************************************************************
// INCLUDES
#include <projectHeader.h>
#include <timer_lib.h>// La función getEvent utiliza timers.
#include <system.h>// Definición de nombres de puertos.
#include <lcd_lib.h>
//****************************************************************************


//****************************************************************************
// DEFINICION DE VARIABLES GLOBALES
//****************************************************************************
char estadoLcd;
const char LCD_linAddr[2]={0x00,0x40};// Para inicializar la estructura del LCD, es necesario crear un arreglo que tenga los address (interno al lcd) del primer caracter de cada renglón.


FILE lcdFile={
              _READ|_WRITE,
              &lcdBuffer,
              &lcdBuffer,
              &lcdBuffer,
              LCD_BUFSIZ,
              LCD_BUFSIZ,
              LCD_BUFSIZ
              };

t_lcdSettings lcdSettings=
    {
    1,//Seteo Visibility: display visibility
    0,//Seteo Visibility: cursor visibility
    0,//Seteo Visibility: position blinking
    1,//Seteo Entry Mode: cursor direction
    0,//Seteo Entry Mode: display shift
    1,//Dirty Flag Visibility: cursor visibility
    1,//Dirty Flag Visibility: cursor visibility
    1,//Dirty Flag Visibility: position blinking
    1,//Dirty Flag Entry Mode: cursor direction
    1,//Dirty Flag Entry Mode: display shift
    1,//Dirty Flag (display completo)

    0,//Cursor position dirty flag
    0,//Cursor column
    0 //Cursor line
    };


//******************************************************************************
// TABLAS DE ESTADO
//******************************************************************************
// EL COMPILADOR TIENE POBLEMAS CON LOS PUNTEROS, EN EL SENTIDO DE QUE AL ASIGNAR VALORES DE ARREGLOS "CONST" DEFINIDOS EN
// MEMORIA DEL PROGRAMA, Y LUEGO QUERER BUSCAR VALORES DE LOS ADDRESS PARA ASIGNAR A UN PUNTERO A ESTRUCTURAS, GENERA ERROR
// Y ENTREGA UN VALOR DE ADDRESS EQUIVOCADO. PARA EVITAR ESE INCONVENIENTE, VOY A TRABAJAR CON IX DE ARREGLOS DIRECTAMENTE
// PARA IDENTIFICAR ESTADOS Y TRANSICIONES.

// ESTAS CONSTANTES QUE INDICAN LA CANTIDAD DE TRANSICIONES PARA CADA ESTADO, LAS COMPLETA EL USUARIO
#define E0_N_TRANS  2//ESTADO 0: LCD_STATE_WAIT_TO_SET_DATA_LENGTH
#define E1_N_TRANS  2//ESTADO 1: LCD_STATE_WAIT_TO_CLEAR_DISPLAY
#define E2_N_TRANS  2//ESTADO 2: LCD_STATE_WAIT_TO_SET_ENTRY_MODE
#define E3_N_TRANS  2//ESTADO 3: LCD_STATE_WAIT_TO_SET_VISIBILITY
#define E4_N_TRANS  3//ESTADO 4: LCD_STATE_WAIT_FOR_REFRESH
#define E5_N_TRANS  3//ESTADO 5: LCD_STATE_COMMAND_FIRST_LINE
#define E6_N_TRANS  3//ESTADO 6: LCD_STATE_COMMAND_SECOND_LINE

// CONTIENE EN CADA ELEMENTO, EL IX DE LA "lcdStateTable[]". EJEMPLO:
// lcdStateTable[lcdStateIndex[0]]=INICIO DE TABLA DE ESTADO DEL "ESTADO 0"
// lcdStateTable[lcdStateIndex[1]]=INICIO DE TABLA DE ESTADO DEL "ESTADO 1"
// ESTE ARRAY SE LLENA AUTOMATICAMENTE CON LAS CONSTANTES DEFINIDAS ARRIBA
const char lcdStateIndex[]=
    {
    0, //ESTADO 0: LCD_STATE_WAIT_TO_SET_DATA_LENGTH
    E0_N_TRANS, //ESTADO 1: LCD_STATE_WAIT_TO_CLEAR_DISPLAY
    E0_N_TRANS+E1_N_TRANS, //ESTADO 2: LCD_STATE_WAIT_TO_SET_ENTRY_MODE
    E0_N_TRANS+E1_N_TRANS+E2_N_TRANS, //ESTADO 3: LCD_STATE_WAIT_TO_SET_VISIBILITY
    E0_N_TRANS+E1_N_TRANS+E2_N_TRANS+E3_N_TRANS, //ESTADO 4: LCD_STATE_WAIT_FOR_REFRESH
    E0_N_TRANS+E1_N_TRANS+E2_N_TRANS+E3_N_TRANS+E4_N_TRANS,//ESTADO 5: LCD_STATE_COMMAND_FIRST_LINE
    E0_N_TRANS+E1_N_TRANS+E2_N_TRANS+E3_N_TRANS+E4_N_TRANS+E5_N_TRANS //ESTADO 6: LCD_STATE_COMMAND_SECOND_LINE
    };


//******************************************************************************
// TABLA DE ESTADOS
//******************************************************************************
// EL ORDEN DE ELEMENTOS DE LA TABLA ES: EVENT, ACTION, NEXT_STATE
t_lcdState lcdStateTable[]=
    {
    {LCD_EVENT_TIMEOUT_30MS,LCD_ACTION_SET_DATA_LENGTH,LCD_STATE_WAIT_TO_CLEAR_DISPLAY},//IX0: LCD_STATE_WAIT_TO_SET_DATA_LENGTH
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_WAIT_TO_SET_DATA_LENGTH},

    {LCD_EVENT_TIMEOUT_30MS,LCD_ACTION_CLEAR_DISPLAY,LCD_STATE_WAIT_TO_SET_ENTRY_MODE},//IX2: LCD_STATE_WAIT_TO_CLEAR_DISPLAY
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_WAIT_TO_CLEAR_DISPLAY},

    {LCD_EVENT_TIMEOUT_30MS,LCD_ACTION_SET_ENTRY_MODE,LCD_STATE_WAIT_TO_SET_VISIBILITY},//IX4: LCD_STATE_WAIT_TO_SET_ENTRY_MODE
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_WAIT_TO_SET_ENTRY_MODE},

    {LCD_EVENT_TIMEOUT_30MS,LCD_ACTION_SET_VISIBILITY,LCD_STATE_WAIT_FOR_REFRESH},//IX6: LCD_STATE_WAIT_TO_SET_VISIBILITY
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_WAIT_TO_SET_VISIBILITY},

    {LCD_EVENT_TIMEOUT_30MS,LCD_ACTION_REWIND,LCD_STATE_COMMAND_FIRST_LINE},//IX8: LCD_STATE_WAIT_FOR_REFRESH
    {LCD_EVENT_TIMEOUT_30MS_SKIP_DISPLAY_REFRESH,LCD_ACTION_SET_CURSOR_POSITION,LCD_STATE_WAIT_TO_SET_ENTRY_MODE},
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_WAIT_FOR_REFRESH},

    {LCD_EVENT_UNFINISHED,LCD_ACTION_SEND_CHARACTER,LCD_STATE_COMMAND_FIRST_LINE},//IX11: LCD_STATE_COMMAND_FIRST_LINE
    {LCD_EVENT_FIRST_LINE_FINISHED,LCD_ACTION_START_LCD_SECOND_LINE,LCD_STATE_COMMAND_SECOND_LINE},
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_COMMAND_FIRST_LINE},

    {LCD_EVENT_UNFINISHED,LCD_ACTION_SEND_CHARACTER,LCD_STATE_COMMAND_SECOND_LINE},//IX14: LCD_STATE_COMMAND_SECOND_LINE
    {LCD_EVENT_REFRESH_FINISHED,LCD_ACTION_INIT_TMR_30MS,LCD_STATE_WAIT_TO_SET_ENTRY_MODE},
    {LCD_EVENT_TABLE_END,LCD_ACTION_DO_NOTHING,LCD_STATE_COMMAND_SECOND_LINE}
    };


//******************************************************************************
// ACCIONES PARA LA FSM
//******************************************************************************

void lcdAction000_set_data_length(void)
    {
    LCD_SEND_COMMAND(LCD_CMD_FUNCTION|LCD_4B_IF|LCD_2_DL);
    TMR_START(TMR_LCD);
    }

void lcdAction001_clear_display(void)
    {
    LCD_SEND_COMMAND(LCD_CMD_CLRDISP);
    TMR_START(TMR_LCD);
    }

void lcdAction002_set_entry_mode(void)
    {
    if(lcdSettings.cursorDirection_refresh|lcdSettings.shift_refresh)
        {
        lcdSettings.cursorDirection_refresh=0;
        lcdSettings.shift_refresh=0;
        LCD_SEND_COMMAND(LCD_CMD_ENTRYM|(lcdSettings.cursorDirection<<1)|(lcdSettings.shift<<0));
        }
    TMR_START(TMR_LCD);
    }

void lcdAction003_set_visibility(void)
    {
    if(lcdSettings.visibility_refresh|lcdSettings.cursorVisibility_refresh|lcdSettings.cursorBlink_refresh)
        {
        lcdSettings.visibility_refresh=0;
        lcdSettings.cursorVisibility_refresh=0;
        lcdSettings.cursorBlink_refresh=0;
        LCD_SEND_COMMAND(LCD_CMD_VIS|(lcdSettings.visibility<<2)| (lcdSettings.cursorVisibility<<1)| (lcdSettings.cursorBlink<<0));
        }
    TMR_START(TMR_LCD);
    }

void lcdAction004_rewind(void)
    {
    lcdFile.flg&=~_EOF; 
    (lcdFile.nxr)=lcdFile.bas;
    (lcdFile.nr)=lcdFile.bufsiz;
    
    LCD_SET_DDRAM_ADDR(LCD_linAddr[0]);
    }

void lcdAction005_send_character(void)
    {
    char c;
    
    c=fgetc(&lcdFile);
    LCD_SEND_DATA(c);
    }

void lcdAction006_init_tmr_30ms(void)
    {
    TMR_START(TMR_LCD);
    }

void lcdAction007_lcd_second_line(void)
    {
    LCD_SET_DDRAM_ADDR(LCD_linAddr[1]);
    }

void lcdAction008_set_cursor_position(void)
    {
    if(lcdSettings.cursor_position_refresh)
        {
        lcdSettings.cursor_position_refresh=0;
        LCD_SET_DDRAM_ADDR(LCD_linAddr[lcdSettings.cursor_position_y]+lcdSettings.cursor_position_x);
        TMR_START(TMR_LCD);
        LCD_SET_DDRAM_ADDR(LCD_linAddr[0]+lcdSettings.cursor_position_x);
        }
    }


//****************************************************************************
// EJECUCION DE ACCION PARA LA FSM
//****************************************************************************
void lcdRunAction(char action)
    {
    switch(action)
        {
        case LCD_ACTION_SET_DATA_LENGTH:lcdAction000_set_data_length();break;
        case LCD_ACTION_CLEAR_DISPLAY:lcdAction001_clear_display();break;
        case LCD_ACTION_SET_ENTRY_MODE:lcdAction002_set_entry_mode();break;
        case LCD_ACTION_SET_VISIBILITY:lcdAction003_set_visibility();break;
        case LCD_ACTION_REWIND:lcdAction004_rewind();break;
        case LCD_ACTION_SEND_CHARACTER:lcdAction005_send_character();break;
        case LCD_ACTION_INIT_TMR_30MS:lcdAction006_init_tmr_30ms();break;
        case LCD_ACTION_START_LCD_SECOND_LINE:lcdAction007_lcd_second_line();break;
        case LCD_ACTION_SET_CURSOR_POSITION:lcdAction008_set_cursor_position();break;
        default:break;
        }
    }


//****************************************************************************
// EJECUCION DE ACCION PARA LA FSM
//****************************************************************************
char lcdGetEvent(void)
    {
    char event=LCD_EVENT_TABLE_END;//SI DENTRO DEL ESTADO CORRESPONDIENTE, NO OCURRE UN EVENTO ESPECIFICO, OCURRIÓ TABLE END PORO DEFECTO

    if(estadoLcd==lcdStateIndex[LCD_STATE_WAIT_TO_SET_DATA_LENGTH])
        if(TMR_TIMEOUT(TMR_LCD))
            event=LCD_EVENT_TIMEOUT_30MS;

    if(estadoLcd==lcdStateIndex[LCD_STATE_WAIT_TO_CLEAR_DISPLAY])
        if(TMR_TIMEOUT(TMR_LCD))
            event=LCD_EVENT_TIMEOUT_30MS;

    if(estadoLcd==lcdStateIndex[LCD_STATE_WAIT_TO_SET_ENTRY_MODE])
        if(TMR_TIMEOUT(TMR_LCD))
            event=LCD_EVENT_TIMEOUT_30MS;

    if(estadoLcd==lcdStateIndex[LCD_STATE_WAIT_TO_SET_VISIBILITY])
    
        if(TMR_TIMEOUT(TMR_LCD))
            event=LCD_EVENT_TIMEOUT_30MS;

    if(estadoLcd==lcdStateIndex[LCD_STATE_WAIT_FOR_REFRESH])
        if(TMR_TIMEOUT(TMR_LCD))
            {
            if(lcdSettings.display_refresh)
                {
                //lcdSettings.display_refresh=0;//EL RESET DE REFRESH LO HACE EN LA ACCIÓN
                event=LCD_EVENT_TIMEOUT_30MS;
                }
            else
                event=LCD_EVENT_TIMEOUT_30MS_SKIP_DISPLAY_REFRESH;
            }
    
    if(estadoLcd==lcdStateIndex[LCD_STATE_COMMAND_FIRST_LINE])
        {
        if(fgetc(&lcdFile)=='\n')
            event=LCD_EVENT_FIRST_LINE_FINISHED;
        else
            {
            unget(&lcdFile);
            event=LCD_EVENT_UNFINISHED;
            }
        }
    if(estadoLcd==lcdStateIndex[LCD_STATE_COMMAND_SECOND_LINE])
        {
        if(fgetc(&lcdFile)==(char)EOF)
            event=LCD_EVENT_REFRESH_FINISHED;
        else
            {
            unget(&lcdFile);
            event=LCD_EVENT_UNFINISHED;
            }
        }

    return event;
    }


//****************************************************************************
// FUNCTION
//****************************************************************************
void lcdFsmParser(void)
    {
    char event;

    event=lcdGetEvent();
    while(lcdStateTable[estadoLcd].event!=LCD_EVENT_TABLE_END && lcdStateTable[estadoLcd].event!=event) estadoLcd++;

    lcdRunAction(lcdStateTable[estadoLcd].action);
    estadoLcd=lcdStateIndex[lcdStateTable[estadoLcd].nextState];//SIEMPRE SE ASIGNA UNO DE LOS ESTADOS DE LCD STATE IX, QUE SON LOS ESTADOS PRINCIPALES. LOS OTROS ELEMENTOS DE STATE TABLE[] SON LAS TRANSICIONES
    }


//****************************************************************************
// FUNCTION
//****************************************************************************
void lcdFsmInit(void)
    {
    LCD_EN=0;
    LCD_RW=0;
    TMR_START(TMR_LCD);
    
    estadoLcd=lcdStateIndex[LCD_STATE_WAIT_TO_SET_DATA_LENGTH];
    }


//****************************************************************************
// FUNCTION
//****************************************************************************
void lcdNibbleSend(char mode,char lowerNibble)
    {
    LCD_RS=mode;
    LCD_DAT7=BIT_GETVAL(lowerNibble,3);
    LCD_DAT6=BIT_GETVAL(lowerNibble,2);
    LCD_DAT5=BIT_GETVAL(lowerNibble,1);
    LCD_DAT4=BIT_GETVAL(lowerNibble,0);
    LCD_EN=1;
    LCD_EN=0;
     }
