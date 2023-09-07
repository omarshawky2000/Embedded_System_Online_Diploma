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


int search_Arr(float *arr, int number ){
	for(int i = 0 ; i < ArrSize ; i++){
		if(arr[i] == number){return i;}
	}
	return -1;
}

void print_Arr(float *arr){
	printf("The Array is :[ ");
	for(int i = 0 ; i < ArrSize ; i++){
		if(i==ArrSize-1){
		printf("%.2f", arr[i]);
		}
		else{
		printf("%.2f ,",arr[i]);
		}
	}
	printf("]\n");
}

int main(void) {
	int index = 0;
	int number = 0;
	float * Array = malloc(ArrSize*sizeof(float ));
	create_Arr(Array,ArrSize);
	print_Arr(Array);
	printf("Enter the number to look for:");
	fflush(stdout);
	scanf("%d",&number);
	index = search_Arr(Array,number);
	if(index == -1 ){printf("number wasn't found \n");}
	else{
		printf("number was found at index %d \n",index);
	}
	return 0;
}
