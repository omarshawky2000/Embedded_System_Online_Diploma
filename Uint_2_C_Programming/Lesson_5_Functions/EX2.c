#include <stdio.h>
#include <stdlib.h>

int factorial ( int num );

int factorial (int num  ){
	if(num == 1){return 1;}
	else{return( num* factorial(num-1));}
}
int main(void) {
	int num ;
	printf("Enter the number: ");
	fflush(stdout);
	scanf("%d",&num);
	printf("The factorial is : %d \n",factorial(num));
	fflush(stdout);
	return 0;
}