//Protection from multiple declarations 
#ifndef DC_H_
#define DC_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"
//Define states
enum {
    DC_Idle,
    DC_Busy
} DC_state_id;

//Declares state functions DC
STATE_define(DC_idle);
STATE_define(DC_busy);


void DC_init(void);

//State Pointer to function
extern void (*DC_state)();

#endif
