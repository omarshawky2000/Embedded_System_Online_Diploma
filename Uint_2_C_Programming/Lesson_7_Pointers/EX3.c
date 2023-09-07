#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StringMAXSIZE 100

int main(void) {
	printf("Enter the string:");
	fflush(stdout);
	char String[StringMAXSIZE];
	gets(String);
	char * ptr = String;
	int size = strlen(String);
	for(int i=0 ; i <size ; i ++ ){
		printf("%c",*(ptr+size-i-1));
	}
	printf("\n");
	fflush(stdout);
	return 0;
}