#include <stdio.h>
#include <stdlib.h>

struct distance
{
	int feet;
	int inches;
};
struct distance d1;
struct distance d2;
void display_sum(struct distance *ptr , struct distance *ptr2){
	if(ptr->inches+ptr2->inches >= 12){printf("sum is %d feet and %d inches \n",ptr->feet+ptr2->feet+1,ptr->inches+ptr2->inches-12);}
	else{printf("sum is %d feet and %d inches \n",ptr->feet+ptr2->feet,ptr->inches+ptr2->inches);}
}


int main(void) {
	struct distance *ptr = &d1;
	struct distance *ptr2 = &d2;
	printf("Enter the first Distance (feet,inches): ");
	fflush(stdout);
	scanf("%d,%d",&(d1.feet),&(d1.inches));
	printf("Enter the second Distance (feet,inches): ");
	fflush(stdout);
	scanf("%d,%d",&(d2.feet),&(d2.inches));
	display_sum(ptr,ptr2);
	return 0;
}
