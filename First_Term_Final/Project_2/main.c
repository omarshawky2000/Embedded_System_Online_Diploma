/*
 *  main.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */
 #include "FIFO.h"


 extern element_type Buffer[BUFFSIZE];
 extern FIFO_Buf_t student_fifo;


void main(void)
{	int choice  = 1;
    char temp_text [10];
	FIFO_Init(&(student_fifo) , Buffer , BUFFSIZE);

	while(choice)
	{
		DPRINTF("===================Welcome to the program====================\n");
		DPRINTF("Choose the number corresponding to the required option:\n");
		DPRINTF("=============================================================\n");
		DPRINTF("1- Add New Student Manually\n");
		DPRINTF("2- Add New Student/s From Text File\n");
		DPRINTF("3- Find Student by Roll Number\n");
		DPRINTF("4- Find Student by First Name\n");
		DPRINTF("5- Find Student by Course ID\n");
		DPRINTF("6- Total Number of Students\n");
		DPRINTF("7- Delete Student by Roll Number\n");
		DPRINTF("8- Update Student by Roll Number\n");
		DPRINTF("9- View All Students Info\n");
		DPRINTF("0- Exit program\n");
		DPRINTF("=============================================================\n");
		DPRINTF("Please Enter your choice: ");
		gets(temp_text);
		choice = atoi(temp_text);
		DPRINTF("=============================================================\n");
		switch (choice)
		{
		case 0:
			break;
		case 1:
			Add_student_manual();
			break;
		case 2:
			Add_student_file();
			break;
		case 3:
			Find_Student_RollN();
			break;
		case 4:
			Find_Student_FName();
			break;
		case 5:
			Find_Student_C_ID();
			break;
		case 6:
			Student_count();
			break;
		case 7:
            DLT_Student_RollN();
			break;
		case 8:
			UPDT_Student_RollN();
			break;
		case 9:
			View_All();
			break;
		default:
			printf("Incorrent entry please try again\n");
			break;
		}
		printf("=============================================================\n");
	}
}
