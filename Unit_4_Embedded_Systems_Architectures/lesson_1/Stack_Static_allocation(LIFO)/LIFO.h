/*
 *  LIFO.h
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

#ifndef LIFO_H_
#define LIFO_H_

#include "stdint.h"

//User configuartions
//select element type (uint8_t , uint16_t , uint32_t ......)
#define element_type uint32_t

// type definitions
typedef struct{

    element_type * head ;                           //Pointer to the head (last element of the buffer)
    element_type * base ;                           //Pointer to the base (first element of the buffer)
    uint32_t  length ;                          //Total length of the buffer
    uint32_t  count  ;                          //Counter that counts the elements currently in buffer

} LIFO_Buf_t;

typedef enum{

    LIFO_no_error,                                  //No error return from the calling the api
    LIFO_full,                                      //Buffer is full
    LIFO_empty,                                     //Buffer is empty
    LIFO_Null                                       //Buffer is destroyed or not found

} LIFO_Status_t;


// APIS
/*Basic APIS*/
LIFO_Status_t  LIFO_Push_item   ( LIFO_Buf_t * lbuf , element_type  item );                                 //Add element to the buffer (Arguements: The buffer , the item to be added)
LIFO_Status_t  LIFO_Pop_item    ( LIFO_Buf_t * lbuf , element_type* item );                                 //Get element to the buffer (Arguements: The buffer , the item to be gotten)
LIFO_Status_t  LIFO_Init        ( LIFO_Buf_t * lbuf , element_type* buff , uint32_t size);                  //Initialize the buffer
LIFO_Status_t  LIFO_IS_FULL     ( LIFO_Buf_t * lbuf );                                                      //check if buffer is full
LIFO_Status_t  LIFO_IS_EMPTY    ( LIFO_Buf_t * lbuf );                                                      //check if buffer is empty


/*Extra APIS*/
element_type   LIFO_Read_item   ( LIFO_Buf_t * lbuf );                                                      //Read the last item in the buffer

#endif  /* LIFO_H_ */