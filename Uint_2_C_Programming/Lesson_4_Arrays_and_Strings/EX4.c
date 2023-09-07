#include <stdio.h>
#include <stdlib.h>

int ArrSize =5;


void create_Arr(float *arr, int size){
	for(int i = 0 ; i < size ; i++){
			printf("Enter element (%d) : ",i);
			fflush(stdout);
			scanf("%f",&(arr[i]));
	}
}


void insert_Arr(float *arr, int number , int index){
	ArrSize ++;
	arr =  realloc(arr ,ArrSize*sizeof(float ));
	float temp1 = 0;
	float temp2 = 0;
	char startcounting = 0;
	int counter = 0;
	for(int i = 0 ; i < ArrSize ; i++){
		if(i == (index-1)){temp1 = arr[i]; arr[i] = number ;startcounting = 1;}
		if(startcounting){
			if(counter%2==0){
				temp2 = arr[i+1];
				arr[i+1]=temp1;
			}
			else{
				temp1 = arr[i+1];
				arr[i+1]= temp2;
			}
			counter++;
	    }
	}
}

void print_Arr(float *arr){
	printf("The Array is :[ ");
	for(int i = 0 ; i < ArrSize ; i++){
		if(i==ArrSize-1){
		printf("%f", arr[i]);
		}
		else{
		printf("%f ,",arr[i]);
		}
	}
	printf("]\n");
}

int main(void) {

	float * Array = malloc(ArrSize*sizeof(float ));
	create_Arr(Array,ArrSize);
	print_Arr(Array);
	insert_Arr(Array,33,1);
	printf("After insertion \n");
	print_Arr(Array);
	return 0;
}