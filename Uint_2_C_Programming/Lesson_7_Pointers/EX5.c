#include <stdio.h>
#include <stdlib.h>
#define StringMAXSIZE 100
#define studentNUM 3

struct student
{
	char name [StringMAXSIZE] ;
	int roll;
	int marks;
};

void display_data(struct student *ptr){
	printf("Student Name is: %s \n",ptr->name);
	printf("Student Roll is: %d \n",ptr->roll);
	printf("Student Mark is: %d \n",ptr->marks);
	printf("******************\n");
}


int main(void) {
	struct student s[studentNUM];
	struct student *ptr[studentNUM];
	for(int i = 0 ; i < studentNUM ; i++){
		printf("Enter the Name of student number(%d): ",i+1);
		fflush(stdout);
		scanf("%s",(s[i].name));
		fflush(stdout);
		printf("Enter the Roll of student number(%d): ",i+1);
		fflush(stdout);
		scanf("%d",&(s[i].roll));
		printf("Enter the Marks of student number(%d): ",i+1);
		fflush(stdout);
		scanf("%d",&(s[i].marks));
		fflush(stdout);
		printf("******************\n");
		ptr[i]=&s[i];
	}
	for(int i = 0 ; i < studentNUM ; i++){
		display_data(*(ptr+i));
	}
	return 0;
}