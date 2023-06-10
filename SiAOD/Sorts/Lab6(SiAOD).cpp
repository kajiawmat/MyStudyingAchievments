#include "RepositoriySiAOD.cpp"
#include "GraphicsSiAOD.cpp"
int const N=10,Max=500,Del=5;
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
	ShellSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	ShellSortT(N,0);
	ZeroOut();
	//Decrement Massive
	printf("\n\nDecrement Massive\n");
	FillDec(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	ShellSort(C,N);
	PrintMas(C,N);
	CheckSum(C,N);
	RunNumber(C,N);
	Difficulty();
	ZeroOut();
	ShellSortT(N,1);
	ZeroOut();
	//Random Massive
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
	printf("\n\nNow lets work with big massive:\n");
	InitWindow();
	InitCoordinates(Del);
	TableInit(5,Del);
	int C5[Max+1]={0};
	SelectSortT500(C5,Max,Del,T,2);
	GraphicT(T,5);
	BubbleSortT500(C5,Max,Del,T,2);
	GraphicT(T,3);
	ShakerSortT500(C5,Max,Del,T,2);
	GraphicT(T,4);
	InsertSortT500(C5,Max,Del,T,2);
	GraphicT(T,6);
	TableT(T,2,5,Del,"Insert");
	ShellSortT500(C5,Max,Del,T,KSort,2);
	GraphicT(T,2);
	TableT(T,3,5,Del,"Shell");
	TableT(KSort,1,5,Del,"k-iterations");
	ShellSortModT500(C5,Max,Del,T,KSort,2);
	GraphicT(T,10);
	TableT(T,5,5,Del,"ShellModify");
	TableT(KSort,4,5,Del,"k-iterations");
	Getch();
	return 0;
}
