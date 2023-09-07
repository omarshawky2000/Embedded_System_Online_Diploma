#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float number1 ;
	float number2 ;
	printf("Enter number 1 : ");
	fflush(stdout);
	scanf("%f",&number1);
	printf("Enter number 2 : ");
	fflush(stdout);
	scanf("%f",&number2);
	number1 = number1 + number2;
	number2 = number1 - number2;
	number1 = number1 - number2;

	printf("number 1 is :  %.2f \n",number1);
	printf("number 2 is :  %.2f \n",number2);
	return 0;
}