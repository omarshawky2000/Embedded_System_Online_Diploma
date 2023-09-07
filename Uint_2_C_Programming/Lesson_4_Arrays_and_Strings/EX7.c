#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StringMAXSIZE 100

int main(void) {
	printf("Enter the string:");
	fflush(stdout);
	char String[StringMAXSIZE];
	gets(String);
	printf("the length of the strings is %d",(int)(strlen(String)));
	fflush(stdout);
	return 0;
}
