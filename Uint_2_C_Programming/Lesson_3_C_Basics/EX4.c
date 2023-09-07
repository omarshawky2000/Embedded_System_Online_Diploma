
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float number1 ;
	float number2   ;
	printf("Enter two numbers : ");
	fflush(stdout);
	scanf("%f",&number1);
	scanf("%f",&number2);
	printf("the product is :  %.2f",number1*number2);
	return 0;
}