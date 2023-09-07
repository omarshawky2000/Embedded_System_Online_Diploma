#include <stdio.h>
#include <stdlib.h>

#define sizeR 3
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
void Transpose_Mat(float **Mat1 , float **Mat2 ,int rows , int coloumns){
	for(int i = 0 ; i < rows ; i++){
		for(int j = 0 ; j < coloumns ; j++){
			Mat1[i][j] = Mat2[j][i];
		}
	}
}
int main(void) {

	float ** Matrix1 = malloc(sizeR*sizeof(float *));
	for(int i=0; i< sizeR; i++) Matrix1[i] = malloc(sizeC*sizeof(float));

	float ** Matrix2 = malloc(sizeC*sizeof(float *));
	for(int i=0; i< sizeC; i++) Matrix2[i] = malloc(sizeR*sizeof(float));


	create_Mat(Matrix1,sizeR,sizeC);

	printf("The original matrix : \n");
	print_Mat(Matrix1,sizeR,sizeC);

	printf("********************************\n");

	Transpose_Mat(Matrix2,Matrix1,sizeC,sizeR);

	printf("********************************\n");

	printf("The transposed matrix : \n");
	print_Mat(Matrix2,sizeC,sizeR);

	return 0;
}