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

void print(int* arr)
{
	printf("%i: ",arr[0]);
	for(int i=1;i<=arr[0];i++)
	{
		printf("%i ",arr[i]);
	}
	printf("\n");
}

int main()
{
	srand(5);
	system("chcp 1251>nul");
	printf("Лабораторная №1.1 \n\n");
	int size = rand()%10;
	int maxValue = 100;
	int* arr = genRandArray(size, maxValue);
	print(arr);
	delete []arr;
	system("pause>nul");
	return 0;
}
