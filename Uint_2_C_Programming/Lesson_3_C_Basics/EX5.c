#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char character ;
	printf("Enter Char : ");
	fflush(stdout);
	scanf("%c",&character);
	printf("the ASCII code for %c is :  %d",character , character);
	return 0;
}