#include<stdio.h>
#include<stdlib.h>

int* genRandArray(int size, int maxValue)
{
	int* array = new int[size+1];
	array[0]=size;
	for(int i=1;i<=size;i++)
	{
		array[i]=rand()%maxValue+1;
	}
	return array;
}

int** genRandMatrix(int size, int maxValue)
{
	int** matrix = new int*[size+1];
	int size_array;
	matrix[0] = new int;
	matrix[0][0] = size;
	for(int i=1;i<=size;i++)
	{
		size_array = rand()%15;
		matrix[i]=genRandArray(size_array,maxValue);
	}
	return matrix;
}

void printArray(int* arr)
{
	printf("%i: ",arr[0]);
	for(int i=1;i<=arr[0];i++)
	{
		printf("%i ",arr[i]);
	}
	printf("\n");
}

void printMatrix(int** matrix)
{
	printf("%i\n",matrix[0][0]);
	for(int i=1;i<=*matrix[0];i++)
	{
		printArray(matrix[i]);
	}
	printf("\n");
}

int main()
{
	srand(5);
	system("color 02");
	system("chcp 1251>nul");
	printf("Лабораторная №1.2 \n\n");
	int size = rand()%10;
	int maxValue = 100;
	int** matrix = genRandMatrix(size, maxValue);
	printMatrix(matrix);
	for(int i=0;i<size;i++)
	{
		delete []matrix[i];
	}
	delete []matrix;
	system("pause>nul");
	return 0;
}
