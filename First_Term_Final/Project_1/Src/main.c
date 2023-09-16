#include <stdint.h>
#include <stdio.h>

#include "driver.h"
#include "AlarmActuator.h"
#include "AlarmMonitor.h"
#include "Algorithm.h"
#include "PressureSensor.h"

void setup()
{
	//initialzations
	GPIO_INITIALIZATION();
	PS_init();
	AA_init();
	AM_init();
	PS_state = STATE(PS_reading);
	Al_state = STATE(Al_waiting);
	AM_state = STATE(AM_alarmOFF);
	AA_state = STATE(AA_waiting);
}

int main (){
	setup();
	while (1)
	{
	 	PS_state();
		Al_state();
		AM_state();
		AA_state();
	}

}
