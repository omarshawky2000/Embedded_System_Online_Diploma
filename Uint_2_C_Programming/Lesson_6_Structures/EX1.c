#include <stdio.h>
#include <stdlib.h>
#define StringMAXSIZE 100

struct student
{
	char name [StringMAXSIZE] ;
	int roll;
	int marks;
};
struct student s;
void display_data(struct student *ptr){
	printf("Student Name is: %s \n",ptr->name);
	printf("Student Roll is: %d \n",ptr->roll);
	printf("Student Mark is: %d \n",ptr->marks);
}


int main(void) {
	struct student *ptr = &s;
	printf("Enter the Name: ");
	fflush(stdout);
	gets(s.name);
	printf("Enter the Roll: ");
	fflush(stdout);
	scanf("%d",&(s.roll));
	printf("Enter the Marks: ");
	fflush(stdout);
	scanf("%d",&(s.marks));
	display_data(ptr);
	return 0;
}