#include<stdio.h>
#include<stdlib.h>

int** genRandMatrix(int size, int maxValue)
{
	int** matrix = new int*[size];
	for(int i=0;i<size;i++)
	{
		matrix[i] = new int[size];
		for(int j=0;j<size;j++)
		{
			matrix[i][j] = rand()%maxValue+1;
		}
	}
	return matrix;
}

void printMatrix(int** matrix, int size)
{
	for(int i=0;i<size;i++)
	{
		for(int j=0;j<size;j++)
		{
			printf("%-4i",matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void printArray(int D[], int size_array)
{
	for(int i=0; i<size_array;i++)
	{
		printf("%i ",D[i]);
	}
	printf("\n");
}

void CopyRightDiagonal(int** matrix, int D[], int size)
{
	int i,j;
	int a,b;
	int count=0;
	for(j=size-1;j>=0;j--)
	{
		a=0;
		b=j;
		while(b<size)
		{
			D[count]=matrix[a][b];
			count++;
			a++;
			b++;
		}
	}
	for(i=1;i<size;i++)
	{
		a=i;
		b=0;
		while(a<size)
		{
			D[count]=matrix[a][b];
			count++;
			a++;
			b++;
		}
	}
}

void CopyLeftDiagonal(int** matrix, int D[], int size)
{
	int i,j;
	int a,b;
	int count=0;
	for(i=0;i<size;i++)
	{
		a=i;
		b=0;
		while(a>=0)
		{
			D[count]=matrix[a][b];
			count++;
			a--;
			b++;
		}
	}
	for(j=1;j<size;j++)
	{
		a=size-1;
		b=j;
		while(b<size)
		{
			D[count]=matrix[a][b];
			count++;
			a--;
			b++;
		}
	}
}


void CopySpiralEdge(int** matrix, int D[], int size)
{
	int i_min=0,i_max=size,j_min=0,j_max=size;
	int size_array=i_max*j_max;
	int count=0;
	int i=0,j=0;
	while(count<size_array)
	{
		i_min++;
		for(;j<j_max;j++)
		{
			D[count]=matrix[i][j];
			count++;
		}
		i++,j--;
		j_max--;
		for(;i<i_max;i++)
		{
			D[count]=matrix[i][j];
			count++;
		}
		i--,j--;
		i_max--;
		for(;j>=j_min;j--)
		{
			D[count]=matrix[i][j];
			count++;
		}
		j_min++;
		i--,j++;
		for(;i>=i_min;i--)
		{
			D[count]=matrix[i][j];
			count++;
		}
		i++,j++;
	}
}

void CopySpiralCentre(int** matrix, int D[], int size)
{
	int size_array=size*size;
	int temp[size_array];
	CopySpiralEdge(matrix,temp,size);
	for(int i=0;i<size_array;i++)
	{
		D[i]=temp[size_array-i-1];
	}
}

void FillArray(int** matrix, int D[], int size, int method)
{
	switch(method)
	{
		case 0:
			CopyRightDiagonal(matrix,D,size);
			break;
		case 1:
			CopyLeftDiagonal(matrix,D,size);
			break;
		case 2:
			CopySpiralCentre(matrix,D,size);
			break;
		case 3:
			CopySpiralEdge(matrix,D,size);
			break;
	}
}

int main()
{
	srand(5);
	system("color 02");
	system("chcp 1251>nul");
	printf("Лабораторная №2.1 \n\n");
	int N = rand()%10;
	N=5;
	int maxValue = 100;
	int** matrix = genRandMatrix(N,maxValue);
	printMatrix(matrix,N);
	int D[N*N];
	for(int i=0;i<4;i++)
	{
		printf("%c) ",i+'а');
		FillArray(matrix,D,N,i);
		printArray(D,N*N);
	}
	system("pause>nul");
	return 0;
}
