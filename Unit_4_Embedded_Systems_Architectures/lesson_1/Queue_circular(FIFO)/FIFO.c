/*
 *  LIFO.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

 #include "FIFO.h"
 #include "stdio.h"
 #ifndef NULL
 #define NULL 0
 #endif

// APIS
/*Basic APIS*/
FIFO_Status_t  FIFO_enqueue_item   ( FIFO_Buf_t * fbuf , element_type  item )              //Add element to the buffer (Arguements: The buffer , the item to be added)
{
	//Check if the FIFO is valid
	if ( ! fbuf->head || ! fbuf->base || ! fbuf->tail  ){
		return FIFO_Null;
	}
	//Check if the LIFO is full
	if (  fbuf->count ==  fbuf->length ){
		return FIFO_full;
	}
	//queue the value (Cicular Queue)
	*(fbuf->head)	= item;
	fbuf->count ++; 

	if(fbuf->head == (fbuf->base + fbuf->length))
	{
		fbuf->head = fbuf->base;
	}
	else{
	fbuf->head ++;
	}

	return FIFO_no_error ;
}

FIFO_Status_t  FIFO_dequeue_item    ( FIFO_Buf_t * fbuf , element_type* item )              //Get element to the buffer (Arguements: The buffer , the item to be gotten)
{
	//Check if the LIFO is valid
	if ( ! fbuf->head || ! fbuf->base || ! fbuf->tail  ){
		return FIFO_Null;
	}
	//Check if the LIFO is empty
	if (  fbuf->count ==  0 ){
		return FIFO_empty;
	}
	//dequeue the value (Cicular Queue)
	*(item)	= *(fbuf->tail);
	fbuf->count --;
	if(fbuf->tail == (fbuf->base + fbuf->length))
	{
		fbuf->tail = fbuf->base;
	}
	else{
	fbuf->tail ++;
	}

	return FIFO_no_error ;
}


FIFO_Status_t  FIFO_Init        ( FIFO_Buf_t * fbuf , element_type* buff , unsigned int size)              //Initialize the buffer
{
	if( buff == NULL ) {
		return FIFO_Null;
	}

	fbuf->base = buff;
	fbuf->head = buff;
	fbuf->tail = buff;
	fbuf->length = size;
	fbuf->count = 0;

	return FIFO_no_error ;
}

FIFO_Status_t  FIFO_IS_FULL        ( FIFO_Buf_t * fbuf )                                                      //check if buffer is full
{
	if ( ! fbuf->head || ! fbuf->base || ! fbuf->tail  ){
		return FIFO_Null;
	}
	//Check if the LIFO is full
	if (  fbuf->count ==  fbuf->length ){
		return FIFO_full;
	}
	else{
		return FIFO_no_error;
	}
}

FIFO_Status_t  FIFO_IS_EMPTY       ( FIFO_Buf_t * fbuf )                                                      //check if buffer is empty
{
	if ( ! fbuf->head || ! fbuf->base || ! fbuf->tail  ){
		return FIFO_Null;
	}
	//Check if the LIFO is empty
	if (  fbuf->count ==  0 ){
		return FIFO_empty;
	}
	else{
		return FIFO_no_error;
	}
}


/*Extra APIS*/
unsigned int   FIFO_Read_item   ( FIFO_Buf_t * fbuf )                                   //Read the last item in the buffer
{
	//Check if the LIFO is valid
	if ( ! fbuf->head || ! fbuf->base ){
		return FIFO_Null;
	}
	//Check if the LIFO is empty
	if (  fbuf->count ==  0 ){
		return FIFO_empty;
	}

	return (unsigned int)*(fbuf->head) ;
}

void   			FIFO_Print	    ( FIFO_Buf_t * fbuf )                                   //Read the last item in the buffer
{
	element_type * temp ;
	int i ;
	//Check if the FIFO is empty
	if (  fbuf->count ==  0 ){
		printf("Fifo is empty \n");
	}
	else {
		temp = fbuf->tail ;
		printf("=========fifo print=========\n");
		for(i=0;i<(fbuf->count);i++)
		{
			printf("%d \n",*temp);
		if( temp == (fbuf->base + fbuf->length))
			{
				temp = fbuf->base;
			}
		else{
				temp++;
			}
		}
		printf("==========fifo end==========\n");
	}
}
