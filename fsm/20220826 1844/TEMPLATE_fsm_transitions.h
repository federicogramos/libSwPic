///////////////////////////////////////////////////////////////////////////////
// TABLAS DE ESTADO (modificar para cada caso)                               //
//                                                                           //
// La maquina de estados es un puntero a una de estas tablas, que son        //
// recorridas en busca de un evento, hasta el final de la tabla.             //
//                                                                           //
// Tal como tambien se indica en la seccion "forward declaration of          //
// states", la cantidad "y" de elementos de cada array "sxxx[y]", debe       //
// ser modificada para cada fsm distinta que se haga, debido a que el        //
// compilador da error si se deja la cantidad de elementos indefinida.       //
//                                                                           //
// Acerca de las prioridades en la maquina de estados: no tiene              //
// sentido hablar de prioridades de transicion, debido a que para la         //
// maquina de estados, no ocurren simultaneamente 2 eventos, sino que        //
// siempre se da 1 evento por vez, y esto queda asegurado debido a que       //
// el evento ocurrente es el valor retornado por la invocacion a la          //
// funcion "getEvent()". Por lo tanto, es la funcion "getEvent()" la         //
// la que debera manejar el comportamiento frente a eventos                  //
// simultaneos.                                                              //
///////////////////////////////////////////////////////////////////////////////

const t_state s_boot[]=
   {
   {FSM_ALWAYS,s_esperaComienzo,DISPLAY_ESPERA_COMIENZO},
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING}
   };

const t_state s_esperaComienzo[]=
   {
   {E_INICIO_HORARIO,s_giroHorario,FSM_DO_NOTHING},
   {E_INICIO_ANTIHORARIO,s_giroAntihorario,FSM_DO_NOTHING},
   {E_SET_VUELTAS,s_esperaComienzo,INGRESAR_CANT_VUELTAS},
   {E_SET_AVANCE,s_esperaComienzo,INGRESAR_VEL_AVANCE},
   {E_SET_RETROCESO,s_esperaComienzo,INGRESAR_VEL_RETROCESO},
   {E_SET_GIRO,s_esperaComienzo,CAMBIAR_SENTIDO_GIRO},
   {FSM_TABLE_END,s_esperaComienzo,FSM_DO_NOTHING}
   };

const t_state s_seteoSentidoGiro[]=
   {
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING},
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING}
   };

const t_state s_ingresoVelocidadAvance[]=
   {
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING},
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING}
   };

const t_state s_seteoVelocidadRetroceso[]=
   {
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING},
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING}
   };

const t_state s_ingresoCantidadVueltas[]=
   {
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING},
   {FSM_TABLE_END,s_boot,FSM_DO_NOTHING}
   };

const t_state s_giroHorario[]=
   {
   {E_FIN,s_notificacionFinal,NOTIFICAR_FINAL},
   {E_PAUSE,s_esperaComienzo,CLEAN_TECLADO},
   {FSM_TABLE_END,s_giroHorario,REFRESH_N_VUELTAS}
   };

const t_state s_giroAntihorario[]=
   {
   {E_FIN,s_notificacionFinal,NOTIFICAR_FINAL},
   {E_PAUSE,s_esperaComienzo,CLEAN_TECLADO},
   {FSM_TABLE_END,s_giroAntihorario,REFRESH_N_VUELTAS}
   };

const t_state s_notificacionFinal[]=
   {
   {E_ACEPTAR,s_esperaComienzo,DISPLAY_ESPERA_COMIENZO},
   {FSM_TABLE_END,s_notificacionFinal,FSM_DO_NOTHING}
   };


