
#include "CA.h"

//Variables
int CA_speed = 0 ;
int CA_distance = 0 ;
int CA_threshold = 4 ;

//STATE Pointer to function
void (*CA_state)();

STATE_define(CA_waiting)
{
	//State name
	CA_state_id = CA_Waiting ;

	//State Action
	CA_speed = 0 ;

	//Event Check
	US_Get_distance(&CA_distance);
	(CA_distance <= CA_threshold) ? ( CA_state = STATE(CA_waiting)) : ( CA_state = STATE(CA_driving));
	printf("CA_waiting state : distance = %d , speed = %d \n", CA_distance , CA_speed );

}

STATE_define(CA_driving)
{
	//State name
	CA_state_id = CA_Driving ;

	//State Action
	CA_speed = 10 ;

	//Event Check
	US_Get_distance(&CA_distance);
	(CA_distance <= CA_threshold) ? ( CA_state = STATE(CA_waiting)) : ( CA_state = STATE(CA_driving));

	printf("CA_waiting state : distance = %d , speed = %d \n", CA_distance , CA_speed );
}

int US_Get_distance_random(int l , int r , int count)
{
	//this will generate random number in range l and r
	int i;
	int rand_num = 0;
	for( i = 0 ; i < count ; i++ ){
		rand_num = ( rand() % (r - l + 1) ) + 1 ;
	} 
	return rand_num ;
	
} 

void US_Get_distance(int * Distance)
{
	* Distance = US_Get_distance_random( 0 , 10 , 4);
} 
