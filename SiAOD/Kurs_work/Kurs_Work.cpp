#include<stdio.h>
#include<stdlib.h>

struct record
{
	char author[12];
	char title[32];
	char publisher[16];
	short int year;
	short int num_of_page;
	
}rec;

struct List
{
	record* Data;
	List* Next;
};

struct Element
{
	record* Data;
	int W;
};

struct Vertex
{
	Element* Info;
	Vertex* Left;
	Vertex* Right;
	Vertex* Down;
};

void Copy_Address(struct record Records[], struct record* Index_Records[],int N)
{
	for(int i=1;i<=N;i++)
	{
		Index_Records[i]=&Records[i];
	}
}


int more(struct record *X, struct record *Y)
{
	if(X->year>Y->year) return 1;
	if(X->year<Y->year) return 0;
	for(int i=0;i<12;i++)
	{
		if(X->author[i]>Y->author[i]) return 1;
		if(X->author[i]<Y->author[i]) return 0;
	}
	return 0;
}

int more2(struct record *X, struct record *Y)
{
	if(X->num_of_page>Y->num_of_page) return 1;
	return 0;
}

int more_equal(struct record *X, struct record *Y)
{
	if(X->year>Y->year) return 1;
	if(X->year<Y->year) return 0;
	for(int i=0;i<12;i++)
	{
		if(X->author[i]>Y->author[i]) return 1;
		if(X->author[i]<Y->author[i]) return 0;
	}
	return 1;
}

void Heap(struct record* Z[], int L, int R)
{
	struct record* X=Z[L];
	int i=L, j=0;
	while(1)
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R)
		{
			if(more_equal(Z[j+1],Z[j])) j++;
		}
		if(more(X,Z[j]))
		{
			break;
		}
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}

void HeapSort(struct record* Z[], int N)
{
	int L=N/2, R=N;
	struct record* t;
	while(L>0)
	{
		Heap(Z,L,R);
		L--;
	}
	while(R>1)
	{
		t=Z[1];
		Z[1]=Z[R];
		Z[R]=t;
		R--;
		Heap(Z,1,R);
	}
}

void ReadDataBase(struct record Records[], int N, FILE *file)
{
	for(int i=1;i<=N;i++)
	{
		fread(&rec,sizeof(rec),1,file);
		Records[i]=rec;
	}
}

void WriteDataBase(struct record Records[], int N)
{
	int i=1, switcher=1;
	struct record* show;
	printf("Жизнь замечательных людей!\n\n");
	system("chcp 866>nul");
	while(1)
	{
		for(int k=0;k<20;k++)
		{
			show=&Records[i];
			printf("%-6i %s  %s  %s  %i  %i\n",i,show->author,show->title, show->publisher, show->year, show->num_of_page);
			i++;
		}
		if(i<=N && switcher==1)
		{
			system("chcp 1251>nul");
			printf("\nВы хотите продолжить?\n");
			printf("0 -- Нет\n");
			printf("1 -- Да, ещё 20 записей\n");
			printf("2 -- Да, все оставшиеся записи\n");
			scanf("%i",&switcher);
			printf("\n");
			system("chcp 866>nul");
			if(switcher==0)
			{
				break;
			}
		}
		if(i>4000) break;
	}
	printf("\n");
	system("pause");
}

void SortDataBase(struct record* Index_Records[], int N)
{
	HeapSort(Index_Records,N);
}

void WriteSortDataBase(struct record* Index_Records[],int N)
{
	int i=1, switcher=1;
	struct record* show;
	printf("Жизнь замечательных людей!\n\n");
	system("chcp 866>nul");
	while(1)
	{
		for(int k=0;k<20;k++)
		{
			show=Index_Records[i];
			printf("%-6i %s  %s  %s  %i  %i\n",i,show->author,show->title, show->publisher, show->year, show->num_of_page);
			i++;
		}
		if(i<=N && switcher==1)
		{
			system("chcp 1251>nul");
			printf("\nВы хотите продолжить?\n");
			printf("0 -- Нет\n");
			printf("1 -- Да, ещё 20 записей\n");
			printf("2 -- Да, все оставшиеся записи\n");
			scanf("%i",&switcher);
			printf("\n");
			system("chcp 866>nul");
			if(switcher==0)
			{
				break;
			}
		}
		if(i>N) break;
	}
	printf("\n");
	system("pause");
}

int BSearchDataBase(struct record* Index_Records[], int N, int year)
{
	int L=1, R=N, m;
	while(L<R)
	{
		m=(L+R)/2;
		if(Index_Records[m]->year<year)
		{
			L=m+1;
		}
		else
		{
			R=m;
		}
	}
	if(Index_Records[R]->year==year)
	{
		return R;
	}
	return 0;
}

void BSearchAllDataBase(struct record* Index_Records[], int N, List* &Head, List* &Tail)
{
	int year, switcher=1;
	printf("Пожалуйста, введите год, по которому необходимо провести поиск данных\n");
	system("chcp 866>nul");
	scanf("%i",&year);
	printf("\n");
	int j=BSearchDataBase(Index_Records, N, year);
	if(j==0)
	{
		return;
	}
	struct List* p;
	p = new List;
	p->Data=Index_Records[j];
	Head=p;
	Tail=p;
	j++;
	for(; j<=N && Index_Records[j]->year==year;j++)
	{
		p = new List;
		p->Data=Index_Records[j];
		Tail->Next=p;
		Tail=p;
	}
	system("chcp 1251>nul");
	printf("Жизнь замечательных людей!\n\n");
}

int PrintList(List* Head)
{
	List* p=Head;
	system("chcp 1251>nul");
	if(p==NULL)
	{
		printf("Простите, но элементов с вышеуказанным годом не существует в базе данных\n");
		system("pause");
		return 0;
	}
	system("chcp 866>nul");
	int i=1, switcher=1;
	
	while(p!=NULL)
	{
		printf("%-6i %s  %s  %s  %i  %i\n",i,p->Data->author,p->Data->title, p->Data->publisher, p->Data->year, p->Data->num_of_page);
		if((i%20==0)&&switcher==1)
		{
			system("chcp 1251>nul");
			printf("\nВы хотите продолжить?\n");
			printf("0 -- Нет\n");
			printf("1 -- Да, ещё 20 записей\n");
			printf("2 -- Да, все оставшиеся записи\n");
			scanf("%i",&switcher);
			printf("\n");
			system("chcp 866>nul");
			if(switcher==0)
			{
				break;
			}
		}	
		p=p->Next;
		i++;
	}
	system("pause");
	return i-1;
}


void Copy_Array(struct List* &Head,struct Element* Array_Elements[])
{
	List* p=Head;
	int i=1;
	while(p!=NULL)
	{
		Array_Elements[i] = new Element();
		Array_Elements[i]->Data=p->Data;
		Array_Elements[i]->W=rand()%20+1;
		p=p->Next;
		i++;
	}
}

void Heap(struct Element* Z[], int L, int R)
{
	struct Element* X=Z[L];
	int i=L, j=0;
	while(1)
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R)
		{
			if(Z[j+1]->W>=Z[j]->W) j++;
		}
		if(X->W>Z[j]->W)
		{
			break;
		}
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}

void HeapSort(struct Element* Z[], int N)
{
	int L=N/2, R=N;
	struct Element* t;
	while(L>0)
	{
		Heap(Z,L,R);
		L--;
	}
	while(R>1)
	{
		t=Z[1];
		Z[1]=Z[R];
		Z[R]=t;
		R--;
		Heap(Z,1,R);
	}
}

void Add_Vertex(struct Vertex* &v, struct Element* X)
{
	if(v==NULL)
	{
		v=new Vertex();
		v->Info=X;
		v->Left=NULL;
		v->Right=NULL;
		v->Down=NULL;
	}
	else if(more2(X->Data,v->Info->Data)) Add_Vertex(v->Right,X);
	else if(more2(v->Info->Data,X->Data)) Add_Vertex(v->Left,X);
	else Add_Vertex(v->Down,X);
}

struct Vertex* A1_Tree(struct List* Head, int N)
{
	if(N==0)
	{
		printf("Простите, но вы ещё не совершили поиск в пункте 3)\n");
		return NULL;
	}
	struct Element** Array_Elements = new Element*[N+1];
	Copy_Array(Head,Array_Elements);
	struct Vertex* Root=NULL;
	HeapSort(Array_Elements,N);
	for(int i=1;i<=N;i++)
	{
		Add_Vertex(Root,Array_Elements[i]);
	}
	return Root;
}

void Obhod(Vertex *v, int &L, int &switcher)
{
	if(v!=NULL && switcher)
	{
		Obhod(v->Left,L,switcher);
		if(switcher)
		{
			printf("%-6i %s  %s  %s  %i  %i\n",L,v->Info->Data->author,v->Info->Data->title, v->Info->Data->publisher, v->Info->Data->year, v->Info->Data->num_of_page);
			L++;
			if(switcher==1 && L%20==1)
			{
				system("chcp 1251>nul");
				printf("\nВы хотите продолжить?\n");
				printf("0 -- Нет\n");
				printf("1 -- Да, ещё 20 записей\n");
				printf("2 -- Да, все оставшиеся записи\n");
				scanf("%i",&switcher);
				printf("\n");
				system("chcp 866>nul");
			}
			Obhod(v->Down,L,switcher);
			Obhod(v->Right,L,switcher);
		}
	}
}

Vertex* TreeSearch(Vertex *Root)
{
	short int X;
	printf("\nВведите кол-во страниц:\t");
	scanf("%i",&X);
	struct Vertex* v=Root;
	while(v!=NULL)
	{
		if(X>v->Info->Data->num_of_page) v=v->Right;
		else if (v->Info->Data->num_of_page>X) v=v->Left;
		else return v;
	}
	return NULL;
}

int Menu(char path[])
{
	int switcher;
	system("CLS");
	system("chcp 1251>nul");
	system("color 02");
	printf("Пожалуйста выбирете что вы хотите сделать:\n\n");
	printf("1) Просмотреть файл базы данных %s!\n",path);
	printf("2) Просмотреть отсортированный файл базы данных %s по году и автору!\n",path);
	printf("3) Произвести поиск всех данных в файле %s с указанным годом!\n",path);
	printf("4) Просмотреть дерево оптимального поиска A1 базы данных %s!\n",path);
	printf("5) Выйти из приложения!\n");
	scanf("%i",&switcher);
	system("color 07");
	system("CLS");
	return switcher;
}

int main()
{
	FILE *file;
	char path[]="testBase1.dat";
	file=fopen(path,"rb");
	const int N=4000;
	printf("%i",sizeof(record));
	int L=1, switcher=1;
	struct record *Records = new record[N+1];
	ReadDataBase(Records,N,file);
	fclose(file);
	struct record* Index_Records[N+1];
	Copy_Address(Records,Index_Records,N);
	SortDataBase(Index_Records,N);
	struct List *Head_List=NULL,*Tail_List=NULL;
	Vertex *Root;
	int menu_switcher;
	int Size=0, Search;
	do
	{
		menu_switcher=Menu(path)%5;
		switch(menu_switcher)
		{
			case 1:
				WriteDataBase(Records,N);
				break;
			case 2:
				WriteSortDataBase(Index_Records,N);
				break;
			case 3:
				BSearchAllDataBase(Index_Records,N,Head_List,Tail_List);
				Size=PrintList(Head_List);
				break;
			case 4:
				Root=A1_Tree(Head_List,Size);
				system("chcp 866>nul");
				Obhod(Root,L,switcher);
				system("chcp 1251>nul");
				printf("\nВы хотите найти элемент в этом дереве 1/0:\n");
				scanf("%i",&Search);
				if(Search)
				{
					Vertex *Temp=TreeSearch(Root);
					if(Temp!=NULL)
					{
						printf("\nЭлемент с таким кол-вом страниц найден:\n");
						system("chcp 866>nul");
						while(Temp!=NULL)
						{
							printf("%s  %s  %s  %i  %i\n",Temp->Info->Data->author,Temp->Info->Data->title, Temp->Info->Data->publisher, Temp->Info->Data->year, Temp->Info->Data->num_of_page);
							Temp=Temp->Down;
						}
					}
					else
					{
						printf("\nЭлемент с таким кол-вом страниц НЕ найден:\n");
					}
				}
				system("pause");
				L=1;
				switcher=1;
				break;
				
		}
	}while(menu_switcher);
	delete []Records;
	return 0;
}
