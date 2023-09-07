#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char number [10] ;
	printf("Enter a number : ");
	fflush(stdout);
	gets(number);
	printf("the number is : ");
	printf("%s",number);
	return 0;
}