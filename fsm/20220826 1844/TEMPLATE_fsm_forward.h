/////////////////////////////////////////////////////////////////////////
// FORWARD DECLARATION OF STATES (modificar para cada caso)            //
//                                                                     //
// Hay estados en la tabla de estados, que son referenciados antes de  //
// que los mismos sean definidos. Es por eso que antes de la creacion  //
// de la tabla de estados, se deben declarar todos los estados         //
// existentes.                                                         //
/////////////////////////////////////////////////////////////////////////

extern const t_state s_boot[];
extern const t_state s_esperaComienzo[];
extern const t_state s_seteoSentidoGiro[];
extern const t_state s_ingresoVelocidadAvance[];
extern const t_state s_seteoVelocidadRetroceso[];
extern const t_state s_ingresoCantidadVueltas[];
extern const t_state s_giroHorario[];
extern const t_state s_giroAntihorario[];
extern const t_state s_pausa[];
extern const t_state s_notificacionFinal[];
