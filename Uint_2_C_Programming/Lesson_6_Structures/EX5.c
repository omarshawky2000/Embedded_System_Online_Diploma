#include <stdio.h>
#include <stdlib.h>
#define Area(r) 3.14*r*r


int main(void) {
	int r = 3;
	printf("Area of a circle of radius %d = %.3f\n", r , Area(r));
	return 0;
}
