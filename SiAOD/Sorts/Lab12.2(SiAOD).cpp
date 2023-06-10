#include "RepositoriySiAOD.cpp"
#include "GraphicsSiAOD.cpp"
int const N=100;
int const Del=5,Max=Del*100;
int main() 
{
	srand(0);
	int T[Del];
	struct Spisok *head, *tail;
	head=NULL;
	tail=NULL;
	FillRand_Stack(&head,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	MergeSort(&head);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	Difficulty();
	ZeroOut();
	FillRand_Line(&head,tail,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	MergeSort(&head);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	Difficulty();
	ZeroOut();
	
	
	InitWindow();
	InitCoordinates(Del);
	TableInit(5,Del);
	int C5[Max+1]={0};
	MergeSort500(head,Max,Del,T,0);
	GraphicT(T,1);
	TableT(T,1,5,Del,"Merg Inc");
	MergeSort500(head,Max,Del,T,1);
	GraphicT(T,2);
	TableT(T,2,5,Del,"Merg Dec");
	MergeSort500(head,Max,Del,T,2);
	GraphicT(T,3);
	TableT(T,3,5,Del,"Merg Rand");
	QuickSort1T500(C5,Max,Del,T,2);
	GraphicT(T,15);
	TableT(T,5,5,Del,"Quick1 Rand");
	HeapSortT500(C5,Max,Del,T,2);
	GraphicT(T,8);
	TableT(T,4,5,Del,"Heap Rand");
	Getch();
	return 0;
}
