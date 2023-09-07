//Learn in depth
//Copyrights Omar Shawky
#include "CA.h"
#include "US.h"
#include "DC.h"

void setup(void){
	//initialize all the drivers
	US_init();
	DC_init();
	//initialize IRQs
	//initialize US_Drive DC_Driver
	//initialize the blocks
	//Set state pointers for each block
	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}

void main(void)
{
	setup();

	while(1){
		// Call state for each block
		US_state();
		CA_state();
		DC_state();
	}
}
