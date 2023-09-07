//Learn in depth
//Copyrights Omar Shawky
#include "CA.h"

void setup(void){
	//initialize all the drivers
	//initialize IRQs
	//initialize US_Drive DC_Driver
	//initialize the blocks
	//Set state pointers for each block
	CA_state = STATE(CA_waiting);
}

void main(void)
{	
	setup();

	while(1){
		// Call state for each block
		CA_state();
	}
}
