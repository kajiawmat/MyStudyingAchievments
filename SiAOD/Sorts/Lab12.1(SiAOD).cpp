#include "RepositoriySiAOD.cpp"
int const N=35;
int main() 
{
	srand(32);
	int qr=0;
	struct Spisok *head, *tail,*a,*b,*c;
	head=NULL;
	tail=NULL;
	a=NULL;
	b=NULL;
	c=NULL;
	FillSeriya_Line(&head,tail,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Split_Stack(&head,&a,&b,qr);
	PrintSpisok(a,qr);
	PrintSpisok(b,qr);
	Merge_Seriya(&a,qr/2+qr%2,&b,qr/2,&c);
	PrintSpisok(c,qr);
	CheckSumSpisok(c,qr);
	RunNumberSpisok(c,qr);
	Delete_Spisok(&head,&tail);
	Difficulty();
	ZeroOut();
	a=NULL;
	b=NULL;
	FillSeriya_Stack(&head,N,A,B);
	PrintSpisok(head,N);
	CheckSumSpisok(head,N);
	RunNumberSpisok(head,N);
	Split_Stack(&head,&a,&b,qr);
	PrintSpisok(a,qr);
	PrintSpisok(b,qr);
	Merge_Seriya(&a,qr/2+qr%2,&b,qr/2,&c);
	PrintSpisok(c,qr);
	CheckSumSpisok(c,qr);
	RunNumberSpisok(c,qr);
	Delete_Spisok(&head,&tail);
	Difficulty();
	ZeroOut();
	return 0;
}
