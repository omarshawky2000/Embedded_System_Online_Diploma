#include <stdio.h>
#include <stdlib.h>

#define ArrSize 3


void create_Arr(float *arr, int size){
	for(int i = 0 ; i < size ; i++){
			printf("Enter element (%d) : ",i);
			fflush(stdout);
			scanf("%f",&(arr[i]));
	}
}


int main(void) {

	float * Array = malloc(ArrSize*sizeof(float ));
	create_Arr(Array,ArrSize);
	float sum = 0;

	for(int i = 0 ; i <ArrSize ; i++){
		sum = sum + Array[i];
	}

	printf("The average of the array := %.2f \n",(sum/ArrSize));
	return 0;
}