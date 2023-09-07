
#include "US.h"

//Variables
int US_distance = 0 ;

//STATE Pointer to function
void (*US_state)();

void US_init(void){
	//init the ultrasonic required registers
	printf("Ultrasonic sensor is ready \n");
}
STATE_define(US_busy)
{
	//State name
	US_state_id = US_Busy ;

	//State action
	US_Get_distance(&US_distance);
	US_Set_distance(US_distance);
	US_state = STATE(US_busy);
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

