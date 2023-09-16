/*
 *  FIFO.h
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

#ifndef FIFO_H_
#define FIFO_H_

#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <conio.h>


#define BUFFSIZE 200

 #define DPRINTF(...) 	{fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}




//User configuartions

typedef struct{

    char        first_name[50] ;                     //First Name of the student
    char        second_name[50] ;                    //Second Name of the student
    uint32_t    Roll_num;                            //Roll Num of the student
    float       GPA ;                                //GPA of the student
    char        courses[5][50]  ;                    //Courses registered by the student

} Student_t;


//select element type (uint8_t , uint16_t , uint32_t ......)
#define element_type Student_t

extern element_type Buffer[BUFFSIZE];
//create buffer 1
#define width1 5

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
FIFO_Status_t  FIFO_Enqueue_item   ( FIFO_Buf_t * fbuf , element_type item );                                 //Add element to the buffer (Arguements: The buffer , the item to be added)
FIFO_Status_t  FIFO_Dequeue_item   ( FIFO_Buf_t * fbuf , element_type item );                                 //Get element to the buffer (Arguements: The buffer , the item to be gotten)
FIFO_Status_t  FIFO_Init           ( FIFO_Buf_t * fbuf , element_type buff[] , unsigned int size);             //Initialize the buffer
FIFO_Status_t  FIFO_IS_FULL        ( FIFO_Buf_t * fbuf );                                                     //check if buffer is full
FIFO_Status_t  FIFO_IS_EMPTY       ( FIFO_Buf_t * fbuf );                                                     //check if buffer is empty



/*Extra APIS*/
element_type   FIFO_Read_item          ( FIFO_Buf_t * fbuf );                                                      //Read the last item in the buffer
void           FIFO_Print              ( FIFO_Buf_t * fbuf );                                                      //Read the last item in the buffer
element_type   Collect_Data            (void);
void           Add_student_manual      (void);
void           Add_student_file        (void);
void           Student_count           (void);
void           Find_Student_C_ID       (void);
void           Find_Student_FName      (void);
void           Find_Student_RollN      (void);
void           UPDT_Student_RollN      (void);
void           DLT_Student_RollN       (void);
void           View_ALL                (void);

#endif  /* FIFO_H_ */
