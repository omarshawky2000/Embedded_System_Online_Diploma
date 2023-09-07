#include <stdio.h>
#include <stdlib.h>

void print_primes_range (int min , int max );

void print_primes_range (int min , int max ){
	unsigned char prime = 0;
	printf("The prime numbers between %d and %d are : \n",min,max);
	for(int i = min ; i<max ; i++){
		prime = 1;
		for(int j = 2 ; j< i; j++){
			if(i%j == 0) {prime = 0;  break;}
			}
		if(prime){ printf("%d \n",i);}
	}
};
int main(void) {
	int min;
	int max;
	printf("Enter the Minimum number:");
	fflush(stdout);
	scanf("%d",&min);
	printf("Enter the Maximum number:");
	fflush(stdout);
	scanf("%d",&max);
	print_primes_range ( min ,  max );
	printf("\n");
	fflush(stdout);
	return 0;
}
