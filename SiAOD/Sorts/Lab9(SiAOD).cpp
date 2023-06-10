#include "RepositoriySiAOD.cpp"
#include "GraphicsSiAOD.cpp"
int const N=10,Del=10,Max=Del*100;
int main(int argc, char*argv[])
{
	int t;
	srand(5);
	int T[Del],KSort[Del];
	//Increment Massive
	int C[N+1];
	printf("\nIncrement Massive\n");
	FillInc(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	HeapSort(C,N);
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
	HeapSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	//Random Massive
	FillRand(C,N,A,B);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	HeapSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	printf("\n\nNow lets work with big massive:\n");
	InitWindow();
	InitCoordinates(Del);
	TableInit(3,Del);
	int C5[Max+1]={0};
	HeapSortT500(C5,Max,Del,T,0);
	TableT(T,1,3,Del,"Heap Inc");
	HeapSortT500(C5,Max,Del,T,1);
	TableT(T,2,3,Del,"Heap Dec");
	HeapSortT500(C5,Max,Del,T,2);
	GraphicT(T,8);
	TableT(T,3,3,Del,"Heap Rand");
	ShellSortT500(C5,Max,Del,T,KSort,2);
	GraphicT(T,1);
	Getch();
	return 0;
}
