//Protection from multiple declarations 
#ifndef ALG_H_
#define ALG_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"
//Define states
enum {
    Waiting,
    Comparing
} Al_state_id;

//Declares state functions CA
STATE_define(Al_waiting);
STATE_define(Al_comparing);

//State Pointer to function
extern void (*Al_state)();

#endif
