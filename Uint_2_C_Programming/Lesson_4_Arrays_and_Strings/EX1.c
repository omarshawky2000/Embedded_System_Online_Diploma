
#include <stdio.h>
#include <stdlib.h>

#define sizeR 2
#define sizeC 2

void create_Mat(float **Mat, int rows , int coloumns){
	for(int i = 0 ; i < rows ; i++){
		for(int j = 0 ; j < coloumns ; j++){
			printf("Enter element (%d,%d) : ",i,j);
			fflush(stdout);
			scanf("%f",&(Mat[i][j]));
		}
	}
}

void print_Mat(float **Mat ,int rows , int coloumns){
	for(int i = 0 ; i < rows ; i++){
		for(int j = 0 ; j < coloumns ; j++){
			printf("%.2f ",Mat[i][j]);
		}
		printf("\n");
	}
}
void add_Mat(float **Mat ,float **Mat1 , float **Mat2 ,int rows , int coloumns){
	for(int i = 0 ; i < rows ; i++){
		for(int j = 0 ; j < coloumns ; j++){
			Mat[i][j] = Mat1[i][j] + Mat2[i][j];
		}
	}
}
int main(void) {
	float ** Matrix1 = malloc(sizeR*sizeof(float *));
	for(int i=0; i< sizeR; i++) Matrix1[i] = malloc(sizeC*sizeof(float));

	float ** Matrix2 = malloc(sizeR*sizeof(float *));
	for(int i=0; i< sizeR; i++) Matrix2[i] = malloc(sizeC*sizeof(float));

	float ** addMatrix = malloc(sizeR*sizeof(float *));
	for(int i=0; i< sizeR; i++) addMatrix[i] = malloc(sizeC*sizeof(float));

	create_Mat(Matrix1,sizeR,sizeC);

	printf("********************************\n");

	create_Mat(Matrix2,sizeR,sizeC);

	printf("********************************\n");

	add_Mat(addMatrix,Matrix1,Matrix2,sizeR,sizeC);

	print_Mat(addMatrix,sizeR,sizeC);

	return 0;
}