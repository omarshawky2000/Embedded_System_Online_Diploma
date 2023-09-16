
#include "AlarmActuator.h"


void AA_init()
{
	//initialize the Alarm Actuator
}

//STATE Pointer to function
void (*AA_state)();

STATE_define(AA_waiting)
{
	//State name
	AA_state_id = AAD_Waiting ;
	(AlarmFlag == 1)?( AA_state = STATE(AA_alarmON)):( AA_state = STATE(AA_alarmOFF));


}

STATE_define(AA_alarmON)
{
	//State name
	AA_state_id = AA_AlarmON ;
	Set_Alarm_actuator(turnON);
	AA_state = STATE(AA_waiting);


}

STATE_define(AA_alarmOFF)
{
	//State name
	AA_state_id = AA_AlarmOFF ;
	Set_Alarm_actuator(turnOFF);
	AA_state = STATE(AA_waiting);

}
