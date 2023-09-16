
#include "PressureSensor.h"

//Variables
int PSD_pVal = 0 ;
const int PSD_Timer = 1000 ;
int CA_threshold = 4 ;


void PS_init (void) {

  	//Initialize the Pressure Sensor
}

//STATE Pointer to function
void (*PS_state)();

STATE_define(PS_reading)
{
	//State name
	PS_state_id = PS_Reading ;
	PSD_pVal = getPressureVal();
	setPressureVal(PSD_pVal);
	PS_state = STATE(PS_waiting);


}

STATE_define(PS_waiting)
{
	PS_state_id = PS_Waiting ;
	Delay(PSD_Timer);
	PS_state = STATE(PS_reading);

}



