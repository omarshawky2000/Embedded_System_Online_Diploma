
#include "Algorithm.h"

//Variables
int PVal = 0 ;
const int PVal_threshold = 20 ;

//STATE Pointer to function
void (*Al_state)();

void setPressureVal(int s){
	PVal = s;
}

STATE_define(Al_waiting)
{
	Al_state_id = Waiting ;
	Al_state = STATE(Al_comparing);

}

STATE_define(Al_comparing)
{

	Al_state_id = Comparing ;
	if(PVal > PVal_threshold) {
		alarmON();
	}
	else{alarmOFF();}
	Al_state = STATE(Al_waiting);
}
