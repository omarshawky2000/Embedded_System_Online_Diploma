#include <stdio.h>
#include <stdlib.h>

int power ( int num , int pow );
int power (int num , int pow ){
	if(pow == 0){return 1;}
	else{pow--; return( num* power(num ,pow));}
}
int main(void) {
	int num ;
	int pow ;
	printf("Enter the number: ");
	fflush(stdout);
	scanf("%d",&num);
	printf("Enter the power: ");
	fflush(stdout);
	scanf("%d",&pow);
	printf("The power is : %d \n",power(num,pow));
	fflush(stdout);
	return 0;
}
