/*
 *  FIFO.h
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"

//User configuartions
//select element type (uint8_t , uint16_t , uint32_t ......)
#define element_type uint32_t
//create buffer 1
#define width1 5
element_type buffer [width1];

// type definitions
typedef struct{

    element_type * head ;                           //Pointer to the head (last element enqueued)
    element_type * base ;                           //Pointer to the base (start of the buffer)
    element_type * tail ;                           //Pointer to the tail (last element dequeued)
    uint32_t  length ;                              //Total length of the buffer
    uint32_t  count  ;                              //Total length of the buffer
} FIFO_Buf_t;

typedef enum{

    FIFO_no_error,                                  //No error return from the calling the api
    FIFO_full,                                      //Buffer is full
    FIFO_empty,                                     //Buffer is empty
    FIFO_Null                                       //Buffer is destroyed or not found

} FIFO_Status_t;


// APIS
/*Basic APIS*/
FIFO_Status_t  FIFO_Enqueue_item   ( FIFO_Buf_t * fbuf , element_type  item );                                //Add element to the buffer (Arguements: The buffer , the item to be added)
FIFO_Status_t  FIFO_Dequeue_item   ( FIFO_Buf_t * fbuf , element_type* item );                                //Get element to the buffer (Arguements: The buffer , the item to be gotten)
FIFO_Status_t  FIFO_Init           ( FIFO_Buf_t * fbuf , element_type* buff , unsigned int size);             //Initialize the buffer
FIFO_Status_t  FIFO_IS_FULL        ( FIFO_Buf_t * fbuf );                                                     //check if buffer is full
FIFO_Status_t  FIFO_IS_EMPTY       ( FIFO_Buf_t * fbuf );                                                     //check if buffer is empty



/*Extra APIS*/
unsigned int   FIFO_Read_item   ( FIFO_Buf_t * fbuf );                                                      //Read the last item in the buffer
void           FIFO_Print       ( FIFO_Buf_t * fbuf );                                                      //Read the last item in the buffer


#endif  /* FIFO_H_ */