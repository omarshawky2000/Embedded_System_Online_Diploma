//Protection from multiple declarations 
#ifndef CA_H_
#define CA_H_

#include "state.h"
#include "stdio.h"
#include "stdlib.h"
//Define states
enum {
    CA_Waiting,
    CA_Driving
} CA_state_id;

//Declares state functions CA
STATE_define(CA_waiting);
STATE_define(CA_driving);

void US_Get_distance(int * Distance);

//State Pointer to function
extern void (*CA_state)();

#endif
