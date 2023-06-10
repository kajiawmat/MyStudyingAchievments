#include "RepositoriySiAOD.cpp"
int const N=100;
int main() 
{
	struct Spisok *head, *tail;
	head=NULL;
	tail=NULL;
	FillInc_Stack(&head,N);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	FillDec_Stack(&head,N);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	FillRand_Stack(&head,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	
	printf("\n\nNow let's work with FIFO (queue)");
	
	FillInc_Line(&head,tail,N);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	FillDec_Line(&head,tail,N);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	FillRand_Line(&head,tail,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Delete_Spisok(&head,&tail);
	return 0;
}
