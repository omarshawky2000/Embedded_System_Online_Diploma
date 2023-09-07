/*
 *  main.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */
 #include "LIFO.c"
 #include "stdlib.h"
 #include "stdio.h"

 #define BUFFSIZE 5

element_type Buffer[BUFFSIZE] ;			//Static allocation of 5*(sizeof(unsigned int)) = 20 byte

void main(void)
{
	LIFO_Buf_t	uart_lifo , I2C_lifo ;
	//static allocation
	LIFO_Init(&(uart_lifo) , Buffer , BUFFSIZE);
	//Dynamic allocation
	element_type * Buffer2 = (element_type *) malloc (BUFFSIZE * sizeof(element_type));
	LIFO_Init(&(I2C_lifo) , Buffer2 , BUFFSIZE);

	for(element_type i = 0 ; i < 5 ; i++){
		if( LIFO_Push_item( &(uart_lifo) , i) == LIFO_no_error ) {
		printf("UART add item : %d \n",i);
		}
	}
	
	element_type var = 0 ;
	for(int i = 0 ; i < 5 ; i++){
		if( LIFO_Pop_item( &(uart_lifo) , &var) == LIFO_no_error ) {
		printf("UART get item : %d \n",var);
		}
	}
}
