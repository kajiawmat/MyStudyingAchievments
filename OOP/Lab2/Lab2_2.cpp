#include<stdio.h>
#include<stdlib.h>

int** genRandMatrix(int size, int maxValue)
{
	int** matrix = new int*[size];
	int size_array;
	for(int i=0;i<size;i++)
	{
		size_array = rand()%15+1;
		//printf("\'%i\' ",size_array);
		matrix[i] = new int[size_array+1];
		for(int j=0;j<size_array;j++)
		{
			matrix[i][j] = rand()%maxValue+1;
		}
		matrix[i][size_array]='\0';
	}
	return matrix;
}

void printMatrix(int** matrix, int size)
{
	int j;
	for(int i=0;i<size;i++)
	{
		j=0;
		while(matrix[i][j]!='\0')
		{
			printf("%-4i",matrix[i][j]);
			j++;
		}
		printf("\n");
	}
	printf("\n");
}

int main()
{
	srand(5);
	system("color 02");
	system("chcp 1251>nul");
	printf("Лабораторная №2.2 \n\n");
	int size = rand()%10;
	int maxValue = 100;
	int** matrix = genRandMatrix(size,maxValue);
	printMatrix(matrix,size);
	system("pause>nul");
	return 0;
}
