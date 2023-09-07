/*
 *  main.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */
 #include "FIFO.c"
 #include "stdlib.h"

 #define BUFFSIZE 5

element_type Buffer[BUFFSIZE] ;			//Static allocation of 5*(sizeof(unsigned int)) = 20 byte

void main(void)
{
	FIFO_Buf_t	uart_fifo , I2C_fifo ;
	//static allocation
	FIFO_Init(&(uart_fifo) , Buffer , BUFFSIZE);
	//Dynamic allocation
	element_type * Buffer2 = (element_type *) malloc (BUFFSIZE * sizeof(element_type));
	FIFO_Init(&(I2C_fifo) , Buffer2 , BUFFSIZE);
	for(int i = 0 ; i < 3 ; i++){
		if( FIFO_enqueue_item( &(uart_fifo) , i) == FIFO_no_error ) {
		printf("UART add item : %d \n",i);
		}
		else{
		printf("enqueue failed \n");
		}
	}

	FIFO_Print(&(uart_fifo));
	
	element_type var = 0 ;
	for(int i = 0 ; i < 3 ; i++){
		if( FIFO_dequeue_item( &(uart_fifo) , &var) == FIFO_no_error ) {
		printf("UART get item : %d \n",var);
		}
		else{
		printf("dequeue failed \n");
		}
	}
	
	printf("==================================\n");

	for(int i = 0 ; i < 5 ; i++){
		if( FIFO_enqueue_item( &(uart_fifo) , i) == FIFO_no_error ) {
		printf("UART add item : %d \n",i);
		}
		else{
		printf("enqueue failed \n");
		}
	}
	FIFO_Print(&(uart_fifo));

	for(int i = 0 ; i < 3 ; i++){
		if( FIFO_dequeue_item( &(uart_fifo) , &var) == FIFO_no_error ) {
		printf("UART get item : %d \n",var);
		}
		else{
		printf("dequeue failed \n");
		}
	}

	FIFO_Print(&(uart_fifo));
}
