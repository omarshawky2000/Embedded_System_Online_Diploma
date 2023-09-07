
#include "DC.h"

//Variables
int DC_speed = 0 ;

//STATE Pointer to function
void (*DC_state)();

void DC_init(void){
	//init the motor required registers
	printf("DC motor is ready \n");
}

void DC_motor(int s){
	DC_speed = s;
	DC_state = STATE(DC_busy);
	printf("CA ----SPEED=%d----> DC \n", DC_speed);

}

STATE_define(DC_idle)
{
	//State name
	DC_state_id = DC_Idle ;

	//State Action
	//Call PWM Function

	printf("DC_idle state : speed = %d \n", DC_speed );

}

STATE_define(DC_busy)
{
	//State name
	DC_state_id = DC_Busy ;

	//State Action
	//Call PWM Function

	printf("DC_busy state : speed = %d \n", DC_speed );
	//Return to idle
	DC_state = STATE(DC_idle);
}
