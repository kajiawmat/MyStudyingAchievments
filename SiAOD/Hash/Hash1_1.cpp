#include<stdio.h>
#include<stdlib.h>

struct Spisok
{
	int data;
	struct Spisok *next;
};

void PrintSpisok(struct Spisok *head)
{
	struct Spisok *p;
	p=head;
	while(p!=NULL)
	{
		printf("%i ",p->data);
		p=p->next;
	}
}


int SearchInSpisok(struct Spisok *head, int K)
{
	struct Spisok *p;
	p=head;
	while(p!=NULL)
	{
		if(p->data==K)
		{
			return 1;
		}
		p=p->next;
	}
	return 0;
}

void InputInSpisok(struct Spisok **head, int K)
{
	struct Spisok *p;
	p=new Spisok;
	p->data=K;
	p->next=*head;
	*head=p;
}

double Golden_Ratio(int n)
{
	int a=1,b=1;
	for(int i=3;i<=n;i++)
	{
		a+=b;
		b=a-b;
	}
	return (double)b/a;
}

const double A=Golden_Ratio(30);

int Hash_Function(int m, int K)
{
	return (int)(m*((A*K)-(int)(A*K)));
}

void Hash_Insert(struct Spisok ***T, int m, int K)
{
	int j=Hash_Function(m,K);
	InputInSpisok(&((*T)[j]),K);
}

int Hash_Search(struct Spisok **T, int m, int K)
{
	int j=Hash_Function(m,K);
	if(SearchInSpisok(T[j],K))
	{
		return j;
	}
	else
	{
		return -1;
	}
}

int main()
{
	srand(9);
	int m;
	system("chcp 1251>nul");
	printf("������� ������ ���-�������: ");
	scanf("%i",&m);
	struct Spisok **head;
	head=new Spisok*[m];
	for(int i=0;i<m;i++)
	{
		head[i]=NULL;
	}
	int Example[30];
	printf("���������� ������:\n");
	for(int i=0;i<30;i++)
	{
		Example[i]=rand()%100+1;
		printf("%i, ",Example[i]);
		Hash_Insert(&head,m,Example[i]);
	}
	printf("\n���������� ���-�������:\n");
	for(int i=0;i<m;i++)
	{
		PrintSpisok(head[i]);
		printf("\n");
	}
	printf("\n\n");
	int search;
	printf("������� ��������, ������� �� ������ �����\n");
	scanf("%i",&search);
	int k=Hash_Search(head,m,search);
	if(k!=-1)
	{
		printf("������� %i ������ � %i ������:\n",search,k);
		PrintSpisok(head[k]);
	}
	else
	{
		printf("������� %i �� ������",search);
	}
	return 0;
}
