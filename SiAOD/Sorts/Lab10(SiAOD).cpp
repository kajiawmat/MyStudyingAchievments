#include "RepositoriySiAOD.cpp"
#include "GraphicsSiAOD.cpp"
int const N=10,Del=10,Max=Del*100;
int main(int argc, char*argv[])
{
	system("chcp 1251>nul");
	int t;
	srand(6);
	int T[Del],KSort[Del],DSort[Del];
	//Increment Massive
	int C[N+1];
	printf("\n\nIncrement Massive\n");
	FillInc(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	QuickSort1(C,1,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	//Decrement Massive
	printf("\n\nDecrement Massive\n");
	FillDec(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	QuickSort1(C,1,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	//Random Massive
	printf("\n\nRandom Massive\n");
	FillRand(C,N,A,B);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	QuickSort1(C,1,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();

	
	printf("\n\nNow lets work with big massive:\n");
	InitWindow();
	InitCoordinates(Del);
	TableInit(5,Del);
	int C5[Max+1]={0};
	QuickSort1T500(C5,Max,Del,T,0);
	TableT(T,3,5,Del,"Quick1 Inc");
	QuickSort1T500(C5,Max,Del,T,1);
	TableT(T,4,5,Del,"Quick1 Dec");
	QuickSort1T500(C5,Max,Del,T,2);
	TableT(T,5,5,Del,"Quick1 Rand");
	GraphicT(T,15);
	HeapSortT500(C5,Max,Del,T,2);
	TableT(T,2,5,Del,"HeapMod Rand");
	GraphicT(T,8);
	ShellSortT500(C5,Max,Del,T,KSort,2);
	TableT(T,1,5,Del,"ShellMod Rand");
	GraphicT(T,1);
	Getch();
	return 0;
	
}
