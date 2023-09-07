#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int number1 ;
	int number2   ;
	printf("Enter two numbers : ");
	fflush(stdout);
	scanf("%d",&number1);
	scanf("%d",&number2);
	printf("the sum is :  %d",number1+number2);
	return 0;
}