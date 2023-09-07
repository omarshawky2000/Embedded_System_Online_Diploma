#include <stdio.h>
#include <stdlib.h>

struct distance
{
	int real;
	int img;
};
struct distance d1;
struct distance d2;
void display_sum(struct distance *ptr , struct distance *ptr2){
	if(ptr->img+ptr2->img > 0){
	printf("sum is (%d+%dj) \n",ptr->real+ptr2->real,ptr->img+ptr2->img);
	}
	else{
	printf("sum is (%d%dj) \n",ptr->real+ptr2->real,ptr->img+ptr2->img);
	}
}


int main(void) {
	struct distance *ptr = &d1;
	struct distance *ptr2 = &d2;
	printf("Enter the first number (real,img): ");
	fflush(stdout);
	scanf("%d,%d",&(d1.real),&(d1.img));
	printf("Enter the second number (real,img): ");
	fflush(stdout);
	scanf("%d,%d",&(d2.real),&(d2.img));
	display_sum(ptr,ptr2);
	return 0;
}