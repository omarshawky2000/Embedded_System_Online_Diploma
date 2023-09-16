//Protection from multiple declarations 
#ifndef AM_H_
#define AM_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"
//Define states
enum {
   	AM_AlarmOFF,
	AM_AlarmON,
	AM_Waiting
} AM_state_id;

//Declares state functions DC
STATE_define(AM_alarmON);
STATE_define(AM_alarmOFF);
STATE_define(AM_waiting);


void AM_init(void);

//State Pointer to function
extern void (*AM_state)();

#endif
