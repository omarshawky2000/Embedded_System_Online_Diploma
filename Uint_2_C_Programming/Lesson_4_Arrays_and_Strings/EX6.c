#include <stdio.h>
#include <stdlib.h>
#define StringMAXSIZE 100

int main(void) {
	printf("Enter the string:");
	fflush(stdout);
	char String[StringMAXSIZE];
	gets(String);
	printf("Enter the character to count:");
	fflush(stdout);
	char character = 0;
	int counter = 0;
	scanf("%c",&character);
	for (int i = 0 ; i <= StringMAXSIZE ; i++){
		if(String[i]== character){counter++;}
		if(String[i]== 0){break;}
	}
	printf("Enter the character '%c' was found %d times",character,counter);
	return 0;
}