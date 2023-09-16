//Protection from multiple declarations 
#ifndef AA_H_
#define AA_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"
//Define states
enum {
    AA_AlarmOFF,
	AA_AlarmON,
	AAD_Waiting
} AA_state_id;

//Declares state functions CA
STATE_define(AA_waiting);
STATE_define(AA_alarmOFF);
STATE_define(AA_alarmON);

#define turnON 	0
#define turnOFF 1

void AA_init();

//State Pointer to function
extern void (*AA_state)();

#endif
