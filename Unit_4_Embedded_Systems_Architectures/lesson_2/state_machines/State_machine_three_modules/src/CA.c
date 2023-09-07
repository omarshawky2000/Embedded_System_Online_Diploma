
#include "CA.h"

//Variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 4 ;


void US_Set_distance (int d) {

  CA_distance = d;
 //Event Check
 (CA_distance <= CA_threshold) ? ( CA_state = STATE(CA_waiting)) : ( CA_state = STATE(CA_driving));
 printf("US ----DISTANCE=%d----> CA \n", CA_distance);
}

//STATE Pointer to function
void (*CA_state)();

STATE_define(CA_waiting)
{
	//State name
	CA_state_id = CA_Waiting ;
	printf("CA_waiting state : distance = %d , speed = %d \n", CA_distance , CA_speed );

	//State Action
	CA_speed = 0 ;

	DC_motor(CA_speed);



}

STATE_define(CA_driving)
{
	//State name
	CA_state_id = CA_Driving ;
	printf("CA_waiting state : distance = %d , speed = %d \n", CA_distance , CA_speed );

	//State Action
	CA_speed = 10 ;

	DC_motor(CA_speed);



}

