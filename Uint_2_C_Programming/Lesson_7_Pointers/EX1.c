#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int m = 29;
	int *ab = &m;
	printf("the address of the pointer ab is 0X%x and the value stored in it is %d\n", (unsigned int)ab , *ab);
	*ab = 34;
	printf("the address of the pointer ab is 0X%x and the value stored in it is %d\n", (unsigned int)ab , *ab);
	printf("the address of the variable m is 0X%x and the value stored in it is %d\n", (unsigned int)&m , m);
	return 0;
}