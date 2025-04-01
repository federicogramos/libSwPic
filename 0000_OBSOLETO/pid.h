// pid.h

struct _pid
{
int *pv; /*pointer to an integer that contains the process value*/
int *sp; /*pointer to an integer that contains the set point*/ 
float integral;
float pgain;
float igain;
float dgain;
int deadband;
int last_error;
};
