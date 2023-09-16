//Protection from multiple declarations 
#ifndef PS_H_
#define PS_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"

//Define states
enum {
    PS_Waiting,
    PS_Reading
} PS_state_id;

//Declares state functions CA
STATE_define(PS_waiting);
STATE_define(PS_reading);

void PS_init(void);

//State Pointer to function
extern void (*PS_state)();

#endif
