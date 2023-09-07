#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define StringMAXSIZE 100

void reverse_recur(char * s , int size);

void reverse_recur(char * s , int size){
	printf("%c",s[size-1]);
	if(size==1){}
	else{size--; reverse_recur(s ,  size);}
}

int main(void) {
	printf("Enter the string:");
	fflush(stdout);
	char String[StringMAXSIZE];
	gets(String);
	int size = strlen(String);
	reverse_recur(String , size);
	printf("\n");
	fflush(stdout);
	return 0;
}
