/*
 *  LIFO.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

 #include "LIFO.h"
 #ifndef NULL
 #define NULL 0
 #endif

// APIS
/*Basic APIS*/
LIFO_Status_t  LIFO_Push_item   ( LIFO_Buf_t * lbuf , element_type  item )              //Add element to the buffer (Arguements: The buffer , the item to be added)
{
	//Check if the LIFO is valid
	if ( ! lbuf->head || ! lbuf->base ){
		return LIFO_Null;
	}
	//Check if the LIFO is full
	if (  lbuf->count ==  lbuf->length ){
		return LIFO_full;
	}
	//Push the value
	*(lbuf->head)	= item;
	lbuf->head ++;
	lbuf->count ++; 

	return LIFO_no_error ;
}

LIFO_Status_t  LIFO_Pop_item    ( LIFO_Buf_t * lbuf , element_type* item )              //Get element to the buffer (Arguements: The buffer , the item to be gotten)
{
	//Check if the LIFO is valid
	if ( ! lbuf->head || ! lbuf->base ){
		return LIFO_Null;
	}
	//Check if the LIFO is empty
	if (  lbuf->count ==  0 ){
		return LIFO_empty;
	}
	//Push the value
	lbuf->head --;
	*(item)	= *(lbuf->head);
	lbuf->count --; 
	
	return LIFO_no_error ;
}


LIFO_Status_t  LIFO_Init        ( LIFO_Buf_t * lbuf , element_type* buff , unsigned int size)              //Initialize the buffer
{
	if( buff == NULL ) {
		return LIFO_Null;
	}

	lbuf->base = buff;
	lbuf->head = buff;
	lbuf->length = size;
	printf("%d\n",lbuf->length);
	lbuf->count = 0;

	return LIFO_no_error ;
}


LIFO_Status_t  LIFO_IS_FULL        ( LIFO_Buf_t * lbuf )                                                      //check if buffer is full
{
	//Check if the LIFO is full
		//Check if the LIFO is valid
	if ( ! lbuf->head || ! lbuf->base ){
		return LIFO_Null;
	}

	if (  lbuf->count ==  lbuf->length ){
		return LIFO_full;
	}
	else{
		return LIFO_no_error;
	}
}


LIFO_Status_t  LIFO_IS_EMPTY       ( LIFO_Buf_t * lbuf )                                                      //check if buffer is empty
{
	if ( ! lbuf->head || ! lbuf->base ){
		return LIFO_Null;
	}
	//Check if the LIFO is empty
	if (  lbuf->count ==  0 ){
		return LIFO_empty;
	}
	else{
		return LIFO_no_error;
	}
}


/*Extra APIS*/
element_type   LIFO_Read_item   ( LIFO_Buf_t * lbuf )                                   //Read the last item in the buffer
{
	//Check if the LIFO is valid
	if ( ! lbuf->head || ! lbuf->base ){
		return LIFO_Null;
	}
	//Check if the LIFO is empty
	if (  lbuf->count ==  0 ){
		return LIFO_empty;
	}

	return (element_type)*(lbuf->head) ;
}
