
#include "AlarmMonitor.h"

//Variables
const int ATimer = 60000;
int AlarmFlag = 0 ;

void alarmON (void) {
	AlarmFlag = 1;
	AM_state = STATE(AM_alarmON);
}
void alarmOFF (void) {
	AlarmFlag = 0;
	AM_state = STATE(AM_alarmOFF);
}
//STATE Pointer to function
void (*AM_state)();

void AM_init(void){
	//init the Alarm Monitor required registers
}


STATE_define(AM_alarmOFF)
{
	//State name
	AM_state_id = AM_AlarmOFF ;

}

STATE_define(AM_alarmON)
{
	//State name
	AM_state_id = AM_AlarmON ;
	AM_state = STATE(AM_waiting);
}

STATE_define(AM_waiting)
{
	//State name
	AM_state_id = AM_Waiting ;
	Delay(ATimer);
	AM_state = STATE(AM_alarmOFF);
}
