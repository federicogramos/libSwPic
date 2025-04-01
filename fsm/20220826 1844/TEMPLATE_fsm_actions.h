////////////////////////////////////////////////////////////////////////////////
// fsm_actions
// ACCIONES PARA LA FSM                                                       //
////////////////////////////////////////////////////////////////////////////////

#include <lcd_lib.h>
//#include <auxiliar.h>

enum e_fsmAction{FSM_A000,FSM_A001,FSM_A002,FSM_A003,FSM_A004,FSM_A005,
                 FSM_A006,FSM_A007,FSM_A008,FSM_A009,FSM_A010,FSM_A011,
                 FSM_A012,FSM_A013,
                 FSM_DO_NOTHING};

#define DISPLAY_ESPERA_COMIENZO FSM_A000
#define CAMBIAR_SENTIDO_GIRO FSM_A001
#define INGRESAR_VEL_AVANCE FSM_A002
#define INGRESAR_VEL_RETROCESO FSM_A004
#define INGRESAR_CANT_VUELTAS FSM_A006
#define ACEPTAR_INGRESO_VUELTAS FSM_A007
#define REFRESH_N_VUELTAS FSM_A008
#define GIRAR_ANTIHORARIO FSM_A009
#define DETENER_GIRO FSM_A010
#define NOTIFICAR_FINAL FSM_A011
#define CLEAN_TECLADO FSM_A012


void fsmAction000(void)
   {
/*   LCD_SEND_COMMAND(LCD_CMD_CLRDISP);
   rewind(&lcdFile);
   if(bobinadora.sentidoGiro==SEN_GIR_HOR) fputc('H',&lcdFile);
   else fputc('A',&lcdFile);
   fprintf(&lcdFile,(char*)" N=%li V=%i/m",bobinadora.seteoVueltas,bobinadora.velAvance);
   fputc('\n',&lcdFile);
   fprintf(&lcdFile,(char*)"Tiempo=%imin   ",(int)(bobinadora.seteoVueltas/bobinadora.velAvance));
  */ }

void fsmAction001(void)
   {
   /*if(bobinadora.sentidoGiro==SEN_GIR_HOR)
      {
      bobinadora.sentidoGiro=SEN_GIR_ANTIHOR;
      SENTIDO_GIRO=SEN_GIR_ANTIHOR;
      }
   else
      {
      bobinadora.sentidoGiro=SEN_GIR_HOR;
      SENTIDO_GIRO=SEN_GIR_HOR;
      }
   fsmAction000(); //Refresh
   */}


void fsmAction002(void)
   {
   /*rewind(&lcdFile);
   fprintf(&lcdFile,(char*)"Vav[v/min]:     ");
   fputc('\n',&lcdFile);
   fprintf(&lcdFile,(char*)"                ");

   rewind(&lcdFile);
   fseek(&lcdFile,12,SEEK_CUR);
   scanf((char *)"%3li",&bobinadora.velAvance);

   fsmAction000(); //DISPLAY_ESPERA_COMIENZO
   */}

void fsmAction003(void)
   {
   }

void fsmAction004(void)
   {
   /*rewind(&lcdFile);
   fprintf(&lcdFile,(char*)"Vret[v/min]:    ");
   fputc('\n',&lcdFile);
   fprintf(&lcdFile,(char*)"                ");

   rewind(&lcdFile);
   fseek(&lcdFile,13,SEEK_CUR);
   scanf((char *)"%3li",&bobinadora.velRetroceso);

   fsmAction000(); //DISPLAY_ESPERA_COMIENZO
   */}

void fsmAction005(void)
   {
   }

void fsmAction006(void)
   {
   /*rewind(&lcdFile);
   fprintf(&lcdFile,(char*)"Nvueltas:       ");
   fputc('\n',&lcdFile);
   fprintf(&lcdFile,(char*)"                ");

   rewind(&lcdFile);
   fseek(&lcdFile,11,SEEK_CUR);
   scanf((char *)"%5li",&bobinadora.seteoVueltas);

   fsmAction000(); //DISPLAY_ESPERA_COMIENZO
   */}

void fsmAction007(void)
   {
   }

void fsmAction008(void)
   {

 /*     lcdFile.flg&=~_READ;//ya no es de lectura
      lcdFile.flg|=_WRITE;//es de escritura
      rewind(&lcdFile);

   if(bobinadora.estadoGiro==ESTADO_AVANCE)
      {
      fprintf(&lcdFile,(char*)"N=%li V=%iv/m",bobinadora.seteoVueltas,bobinadora.velAvance);
      fputc('\n',&lcdFile);
      fprintf(&lcdFile,(char*)"/%li AVANCE   ",(int)(bobinadora.pulsosActuales/PULSOS_POR_VUELTA));
      }
   else
      {
      fprintf(&lcdFile,(char*)"N=%li V=%iv/m",bobinadora.seteoVueltas,bobinadora.velAvance);
      fputc('\n',&lcdFile);
      fprintf(&lcdFile,(char*)"/%li RETROCESO",(int)(bobinadora.pulsosActuales/PULSOS_POR_VUELTA));
      }
  */ }

void fsmAction009(void)
   {
   }

void fsmAction010(void)
   {
   }

void fsmAction011(void)
   {
 /*  lcdFile.flg&=~_READ;//ya no es de lectura
   lcdFile.flg|=_WRITE;//es de escritura
   rewind(&lcdFile);

   if(bobinadora.pulsosActuales==0)
      {
      fprintf(&lcdFile,(char*)"N=%li V=%iv/m",bobinadora.seteoVueltas,bobinadora.velAvance);
      fputc('\n',&lcdFile);
      fprintf(&lcdFile,(char*)"/%li CERO     ",(int)(bobinadora.pulsosActuales/PULSOS_POR_VUELTA));
      }
   else
      {
      fprintf(&lcdFile,(char*)"N=%li V=%iv/m",bobinadora.seteoVueltas,bobinadora.velAvance);
      fputc('\n',&lcdFile);
      fprintf(&lcdFile,(char*)"/%li FIN     ",(int)(bobinadora.pulsosActuales/PULSOS_POR_VUELTA));
      }
  */ }

void fsmAction012(void)
   {
   //kbhit(); //limpia teclado, ahora ninguna tecla fue apretada
   }

////////////////////////////////////////////////////////////////////////////////
// EJECUCION DE ACCION PARA LA FSM
////////////////////////////////////////////////////////////////////////////////

void fsmRunAction(char action)
{
   switch(action)
   {
      case FSM_A000: fsmAction000(); break;
      case FSM_A001: fsmAction001(); break;
      case FSM_A002: fsmAction002(); break;
      case FSM_A003: fsmAction003(); break;
      case FSM_A004: fsmAction004(); break;
      case FSM_A005: fsmAction005(); break;
      case FSM_A006: fsmAction006(); break;
      case FSM_A007: fsmAction007(); break;
      case FSM_A008: fsmAction008(); break;
      case FSM_A009: fsmAction009(); break;
      case FSM_A010: fsmAction010(); break;
      case FSM_A011: fsmAction011(); break;
      default: break;
   }
}
