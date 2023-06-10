#include "RepositoriySiAOD.cpp"
#include "GraphicsSiAOD.cpp"
int const N=10,Del=10, Max=Del*100;
int main(int argc, char*argv[])
{
	int t,var,x;
	srand(5);
	int T[Del],KSort[Del], dif[2]={0};
	//First version
	int C[N+1];
	printf("\nFirst version\n");
	FillRand(C,N,A,B);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	ShellSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	printf("\n\nPlease input value of element of massive:\t");
	scanf("%i",&x);
	if(var=BSearch1(C,N,x))
	{
		printf("\nElement of massive found: %i",var);
	}
	else
	{
		printf("\nElement of massive not found");
	}
	Difficulty();
	ZeroOut();
	//Second version
	printf("\n\nSecond version\n");
	FillRand(C,N,A,B);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	ShellSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	printf("\n\nPlease input value of element of massive:\t");
	scanf("%i",&x);
	if(var=BSearch2(C,N,x))
	{
		printf("\nElement of massive found: %i",var);
	}
	else
	{
		printf("\nElement of massive not found");
	}
	Difficulty();
	ZeroOut();
	
	
	printf("\n\nNow lets work with big massive:\n");
	printf("\n\nPlease input value of element of massive:\t");
	scanf("%i",&x);
	InitWindow();
	InitCoordinates(Del);
	TableInit(4,Del);
	int C5[Max+1]={0};
	BSearch1Mass(C5,Max,Del,T,x);
	GraphicT(T,6);
	TableT(T,1,4,Del,"Ñô I");
	BSearch2Mass(C5,Max,Del,T,x);
	GraphicT(T,2);
	TableT(T,2,4,Del,"Ñô II");
	BSearchAll_1Mass(C5,Max,Del,T,x,dif);
	GraphicT(T,8);
	TableT(T,3,4,Del,"Ñô All I");
	BSearchAll_2Mass(C5,Max,Del,T,x,dif);
	GraphicT(T,10);
	TableT(T,4,4,Del,"Ñô All II");
	BSearch1Mass(C5,100,1,T,x);
	PrintMas(C5,100);
	BSearch2Mass(C5,100,1,T,x);
	PrintMas(C5,100);
	Getch();
	return 0;
}
