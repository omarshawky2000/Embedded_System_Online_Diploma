/*
 *  LIFO.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

 #include "FIFO.h"

 #ifndef NULL
 #define NULL 0
 #endif


 element_type Buffer[BUFFSIZE] ;			//Static allocation of 5*(sizeof(unsigned int)) = 20 byte
 FIFO_Buf_t	student_fifo;

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

FIFO_Status_t  FIFO_dequeue_item    ( FIFO_Buf_t * fbuf , element_type item )              //Get element to the buffer (Arguements: The buffer , the item to be gotten)
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
	(item)	= *(fbuf->tail);
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


FIFO_Status_t  FIFO_Init        ( FIFO_Buf_t * fbuf , element_type buff[] , unsigned int size)              //Initialize the buffer
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
element_type   FIFO_Read_item   ( FIFO_Buf_t * fbuf )                                   //Read the last item in the buffer
{
	//Check if the LIFO is valid
	if ( ! fbuf->head || ! fbuf->base ){
		//return FIFO_Null;
	}
	//Check if the LIFO is empty
	if (  fbuf->count ==  0 ){
		//return FIFO_empty;
	}

	return (element_type)*(fbuf->head) ;
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

void Add_student_manual(void)
{
	Student_t s ;
	char temp_text [40];
	DPRINTF("Enter the student's first Name:\n");
	gets(temp_text);
	//DPRINTF("%s\n",temp_text);
	strcpy(s.first_name , temp_text);

	DPRINTF("Enter the student's last Name:\n");
	gets(temp_text);
	strcpy(s.second_name , temp_text);

	DPRINTF("Enter the student's Roll number:\n");
	gets(temp_text);
	s.Roll_num = atoi(temp_text);

	DPRINTF("Enter the student's GPA:\n");
	gets(temp_text);
	s.GPA = atof(temp_text);

	for(int i=0 ; i<5 ; i++)
	{
		DPRINTF("Enter the student's registered course number %d:\n",i+1);
		gets(temp_text);
		strcpy(s.courses[i] , temp_text);

	}
	DPRINTF("#######Data filled successfully########\n");
	FIFO_enqueue_item ( &student_fifo ,   s );
}

void Add_student_file()
{

    FILE *fp;
    fp = fopen("StudentFile.txt", "r");

    if(fp == NULL){
        DPRINTF("\n[ERROR] Failed to open file");
        return;
    }

    char line[100];
    char *token;

    while(fgets(line, sizeof(line), fp)){

        int counter = 1;
        int course = 0;
        Student_t new_s;
        token = strtok(line, " ");

        while(token != NULL){
            switch(counter){
            case 1:
                new_s.Roll_num = atoi(token);
                break;
            case 2:
                strcpy(new_s.first_name, token);
                break;
            case 3:
                strcpy(new_s.second_name, token);
                break;
            case 4:
                new_s.GPA = atof(token);
                break;
            case 5:
                strcpy(new_s.courses[course],token);
                course++;
                counter--;
                break;
            }
            token = strtok(NULL, " ");
            counter++;
        }
        *(student_fifo.head) = new_s;
        student_fifo.count++;

        if(student_fifo.head == (student_fifo.base + (student_fifo.length)))
            student_fifo.head = student_fifo.base;
        else
            student_fifo.head++;
    }
    fclose(fp);
    DPRINTF("\n[INFO] Student Info added successfully\n");
}


void Student_count(void)
{
	DPRINTF("DataBase size is %d students\n",student_fifo.count);
}

void View_All(void)
{
	int size = student_fifo.count;
	for(int i = 0 ; i<size;i++)
	{
		DPRINTF("the student's first Name:\n");
		DPRINTF("%s\n",Buffer[i].first_name);
		DPRINTF("the student's second Name:\n");
		DPRINTF("%s\n",Buffer[i].second_name);
		DPRINTF("the student's Roll number:\n");
		DPRINTF("%d\n",Buffer[i].Roll_num);
		DPRINTF("the student's GPA:\n");
		DPRINTF("%.2lf\n",Buffer[i].GPA);
		DPRINTF("the student's registered courses are:[");
		for	(int j = 0 ; j<5; j++)
		{
			if(j==4){ DPRINTF("%s]\n",Buffer[i].courses[j]); }
			else{ DPRINTF("%s,",Buffer[i].courses[j]); }
		}
		DPRINTF("=======================================\n");
	}
}


void Find_Student_FName(void)
{
	uint32_t size = student_fifo.count;
	char temp_text [40];
	DPRINTF("SEARCH : Enter the student's first Name:\n");
	gets(temp_text);
	DPRINTF("=======================================\n");
	char foundflag = 0;

	for(int i = 0 ; i<size;i++)
	{
	    if(strcmp(temp_text,Buffer[i].first_name)==0){
		DPRINTF("the student's first Name:\n");
		DPRINTF("%s\n",Buffer[i].first_name);
		DPRINTF("the student's second Name:\n");
		DPRINTF("%s\n",Buffer[i].second_name);
		DPRINTF("the student's Roll number:\n");
		DPRINTF("%d\n",Buffer[i].Roll_num);
		DPRINTF("the student's GPA:\n");
		DPRINTF("%.2lf\n",Buffer[i].GPA);
		DPRINTF("the student's registered courses are:[");
		for	(int j = 0 ; j<5; j++)
		{
			if(j==4){ DPRINTF("%s]\n",Buffer[i].courses[j]); }
			else{ DPRINTF("%s,",Buffer[i].courses[j]); }
		}
		foundflag = 1;
		DPRINTF("=======================================\n");
		}
	}
	if(foundflag == 0) {DPRINTF("Couldn't find a match\n");}
}

void Find_Student_RollN(void)
{
	uint32_t size = student_fifo.count;
	char temp_text [40];
	DPRINTF("SEARCH : Enter the student's Roll Number:\n");
	gets(temp_text);
	uint32_t ID = atoi(temp_text);
	DPRINTF("=======================================\n");
	char foundflag = 0;

	for(int i = 0 ; i<size;i++)
	{
	    if(ID == Buffer[i].Roll_num){
		DPRINTF("the student's first Name:\n");
		DPRINTF("%s\n",Buffer[i].first_name);
		DPRINTF("the student's second Name:\n");
		DPRINTF("%s\n",Buffer[i].second_name);
		DPRINTF("the student's Roll number:\n");
		DPRINTF("%d\n",Buffer[i].Roll_num);
		DPRINTF("the student's GPA:\n");
		DPRINTF("%.2lf\n",Buffer[i].GPA);
		DPRINTF("the student's registered courses are:[");
		for	(int j = 0 ; j<5; j++)
		{
			if(j==4){ DPRINTF("%s]\n",Buffer[i].courses[j]); }
			else{ DPRINTF("%s,",Buffer[i].courses[j]); }
		}
		foundflag = 1;
		DPRINTF("=======================================\n");
		}
	}
	if(foundflag == 0) {DPRINTF("Couldn't find a match\n");}
}

void Find_Student_C_ID(void)
{
	uint32_t size = student_fifo.count;
	char temp_text [40];
	DPRINTF("SEARCH : Enter the student's Course:\n");
	gets(temp_text);
	DPRINTF("=======================================\n");
	char foundflag = 0;

	for(int i = 0 ; i<size;i++)
	{
	    for(int z = 0 ; z < 5 ; z++){
            if(strcmp(temp_text,Buffer[i].courses[z]) == 0)
            {
                DPRINTF("the student's first Name:\n");
                DPRINTF("%s\n",Buffer[i].first_name);
                DPRINTF("the student's second Name:\n");
                DPRINTF("%s\n",Buffer[i].second_name);
                DPRINTF("the student's Roll number:\n");
                DPRINTF("%d\n",Buffer[i].Roll_num);
                DPRINTF("the student's GPA:\n");
                DPRINTF("%.2lf\n",Buffer[i].GPA);
                DPRINTF("the student's registered courses are:[");
                for	(int j = 0 ; j<5; j++)
                {
                    if(j==4){ DPRINTF("%s]\n",Buffer[i].courses[j]); }
                    else{ DPRINTF("%s,",Buffer[i].courses[j]); }
                }
                foundflag = 1;
                DPRINTF("=======================================\n");
            }
	    }
	}
	if(foundflag == 0) {DPRINTF("Couldn't find a match\n");}
}


void UPDT_Student_RollN(void)
{
	uint32_t size = student_fifo.count;
	char temp_text [40];
	DPRINTF("SEARCH : Enter the student's Roll Number:\n");
	gets(temp_text);
	uint32_t ID = atoi(temp_text);
	DPRINTF("=======================================\n");
	char foundflag = 0;

	for(int i = 0 ; i<size;i++)
	{
	    if(ID == Buffer[i].Roll_num){
		DPRINTF("the student's first Name:\n");
		DPRINTF("%s\n",Buffer[i].first_name);
		DPRINTF("the student's second Name:\n");
		DPRINTF("%s\n",Buffer[i].second_name);
		DPRINTF("the student's Roll number:\n");
		DPRINTF("%d\n",Buffer[i].Roll_num);
		DPRINTF("the student's GPA:\n");
		DPRINTF("%.2lf\n",Buffer[i].GPA);
		DPRINTF("the student's registered courses are:[");
		for	(int j = 0 ; j<5; j++)
		{
			if(j==4){ DPRINTF("%s]\n",Buffer[i].courses[j]); }
			else{ DPRINTF("%s,",Buffer[i].courses[j]); }
		}
		foundflag = 1;
		DPRINTF("=======================================\n");
        DPRINTF("UPDATING INFO PLEASE FILL THE FOLLOWING:\n");
        DPRINTF("=======================================\n");
        DPRINTF("Enter the student's first Name:\n");
        gets(temp_text);
        //DPRINTF("%s\n",temp_text);
        strcpy(Buffer[i].first_name , temp_text);
        DPRINTF("Enter the student's last Name:\n");
        gets(temp_text);
        strcpy(Buffer[i].second_name , temp_text);

        DPRINTF("Enter the student's Roll number:\n");
        gets(temp_text);
        Buffer[i].Roll_num = atoi(temp_text);

        DPRINTF("Enter the student's GPA:\n");
        gets(temp_text);
        Buffer[i].GPA = atof(temp_text);
        for(int i=0 ; i<5 ; i++)
            {
                DPRINTF("Enter the student's registered course number %d:\n",i+1);
                gets(temp_text);
                strcpy(Buffer[i].courses[i] , temp_text);

            }

		}
	}
	if(foundflag == 0) {DPRINTF("Couldn't find a match\n");}
}


void DLT_Student_RollN(void)
{
    char temp_text [40];
    DPRINTF("SEARCH : Enter the student's Roll Number:\n");
	gets(temp_text);
	uint32_t ID = atoi(temp_text);

	uint32_t size = student_fifo.count;

    Student_t * s ;
    Student_t * curr_s ;
    Student_t * next_s ;
    s = student_fifo.tail;
	DPRINTF("=======================================\n");
	char foundflag = 0;

	for(int i = 0 ; i<size;i++)
	{
	    if(ID == Buffer[i].Roll_num){
            for(int j = i ; j<size;j++)
            {
                curr_s = s;
                next_s = ++s;
                *curr_s = *next_s;
            }
            student_fifo.count-- ;
            if(student_fifo.head == student_fifo.base)
            {
                student_fifo.head = student_fifo.base + student_fifo.length;
            }
            else
            {
                student_fifo.head--;
            }
            foundflag = 1;
            DPRINTF("DELETED SUCCESSFULLY\n");
        }
        s++;
	}
	if(foundflag == 0) {DPRINTF("Couldn't find a match\n");}
}
