/*
 *  main.c
 *  Created on 20-8-2023
 *  Author: Omar Shawky
 */

#include "linked_list.h"

#define DPRINTF(...) 	{fflush(stdout); \
						fflush(stdin); \
						printf(__VA_ARGS__); \
						fflush(stdout); \
						fflush(stdin);}

struct S_Student * g_P_FirstStudent = NULL;

void main(void)
{	int choice  = 1;
    char temp_text [10];
	while(choice)
	{
		DPRINTF("===================Welcome to the program====================\n");
		DPRINTF("Choose the number corresponding to the required option:\n");
		DPRINTF("=============================================================\n");
		DPRINTF("1- Add Student\n");
		DPRINTF("2- Delete Student\n");
		DPRINTF("3- view All\n");
		DPRINTF("4- Delete All\n");
		DPRINTF("5- view student with reference number\n");
		DPRINTF("6- view student with reference number from the end\n");
		DPRINTF("7- view database size\n");
		DPRINTF("8- view student with reference number at the middle of database\n");
		DPRINTF("9- reverse the list\n");
		DPRINTF("0- Exit program\n");
		gets(temp_text);
		choice = atoi(temp_text);
		switch (choice)
		{
		case 0:
			break;
		case 1:
			Add_student();
			break;
		case 2:
			Delete_student();
			break;
		case 3:
			View_All();
			break;
		case 4:
			DeleteALL();
			break;
		case 5:
			NthNode();
			break;
		case 6:
			NthNodeFromEnd();
			break;
		case 7:
			LenghtList();
			break;
		case 8:
			MiddleList();
			break;
		case 9:
			ReverseList();
			break;
		default:
			printf("Incorrent entry please try again\n");
			break;
		}
		printf("=============================================================\n");
	}
}
