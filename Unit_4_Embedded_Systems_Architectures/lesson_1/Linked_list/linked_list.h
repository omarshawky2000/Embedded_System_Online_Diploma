/*
 * linked_list.h for Linked List Student DB
 * Eng. Ahmed Essam
*/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


struct S_Data{
	int ID;
	char name[40];
	float height;
};
struct S_Student
{
	struct S_Data	Student;
	struct S_Student * P_nextStudent;

};

extern struct S_Student * g_P_FirstStudent ;

//Main APIs
void Add_student();
int Delete_student();
void View_All();
void DeleteALL();
void NthNode();
void NthNodeFromEnd();
void LenghtList();
int Lenght();
void MiddleList();
void ReverseList();


#endif /* LINKED_LIST_H_ */
