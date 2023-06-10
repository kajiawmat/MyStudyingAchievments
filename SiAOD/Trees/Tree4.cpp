#include<stdio.h>
#include<stdlib.h>


int random (int N)
{
	return rand()%N;
}

void FillRand (int Z[], int N, int A, int B)
{
	for(int i=1;i<=N;i++) Z[i]=random(B-A+1)+A;
}

void FillIncRand(int Z[], int N)
{
	Z[1]=1;
	for(int i=2;i<=N;i++)
	{
		Z[i]=Z[i-1]+random(3)+1;
	}
	int left, right, t;
	for(int k=0;k<=N/2;k++)
	{
		left=random(N)+1;
		right=random(N)+1;
		t=Z[left];
		Z[left]=Z[right];
		Z[right]=t;
	}
}

void PrintMas(int Z[], int N)
{
	printf("\nНовый массив\n");
	for(int i=1;i<=N;i++) printf("%i ",Z[i]);
}

void Heap(int Z[], int L, int R)
{
	int X=Z[L], i=L, j;
	while(1)
	{
		j=2*i;
		if(j>R) break;
		if((j<R)&&(Z[j+1]>=Z[j])) j++;
		if(X>Z[j]) break;
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}

void HeapSort(int Z[], int N)
{
	int L=N/2, R=N, t;
	while(L>0)
	{
		Heap(Z,L,N);
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

struct Vertex
{
	int data;
	struct Vertex *Left;
	struct Vertex *Right;
	int Bal;
	int W;
};

struct Vertex* AddVertex(int x)
{
	struct Vertex* v = new struct Vertex;
	v->data=x;
	v->Left=NULL;
	v->Right=NULL;
	v->Bal=0;
	v->W=0;
	return v;
}

int CheckTreeSearch(Vertex* v)
{
	if(v!=NULL)
	{
		if(v->Left!=NULL && (v->data<v->Left->data || CheckTreeSearch(v->Left)==0)) return 0;
		if(v->Right!=NULL && (v->data>v->Right->data || CheckTreeSearch(v->Right)==0)) return 0;
	}
	return 1;
}

Vertex* TreeSearch(Vertex *Root, int X)
{
	struct Vertex* v=Root;
	while(v!=NULL)
	{
		if(v->data<X) v=v->Right;
		else if (v->data>X) v=v->Left;
		else return v;
	}
	return NULL;
}

struct Vertex* RandVertex()
{
	struct Vertex* v = new struct Vertex;
	v->data=rand()%100;
	printf("%i, ",v->data);
	v->Left=NULL;
	v->Right=NULL;
	return v;
}

void Obhod(Vertex *v)
{
	if(v!=NULL)
	{
		Obhod(v->Left);
		printf("%i, ",v->data);
		Obhod(v->Right);
	}
}

int Max(int x, int y)
{
	if(x>y) return x;
	return y;
}

int Size(Vertex* v)
{
	if(v==NULL) return 0;
	return 1+Size(v->Left)+Size(v->Right);
}

int Sum(Vertex* v)
{
	if(v==NULL) return 0;
	return v->data+Sum(v->Left)+Sum(v->Right);
}

int Height(Vertex* v)
{
	if(v==NULL) return 0;
	return 1+Max(Height(v->Left),Height(v->Right));
}

int ALW(Vertex* v, int L)
{
	if(v==NULL) return 0;
	return L+ALW(v->Left,L+1)+ALW(v->Right,L+1);
}

double Average_Height(Vertex* v)
{
	return (double) ALW(v,1)/Size(v);
}

struct Vertex* PBT(int Z[], int L, int R)
{
	if(L>R) return NULL;
	int m = (L+R)/2;
	struct Vertex* v = new struct Vertex;
	v->data= Z[m];
	v->Left= PBT(Z,L,m-1);
	v->Right= PBT(Z,m+1,R);
	return v;
}

void AddVertexRBT(int X, struct Vertex *&Root)
{
	struct Vertex** v;
	v=&Root;
	while(*v!=NULL)
	{
		if(X<(*v)->data) v=&((*v)->Left);
		else if (X>(*v)->data) v=&((*v)->Right);
		else break;
	}
	if(*v == NULL)
	{
		*v = AddVertex(X);
	}
}

struct Vertex* RBT_Double(int Z[])
{
	struct Vertex* Root = NULL;
	for(int i=1;i<=10;i++)
	{
		AddVertexRBT(Z[i],Root);
	}
	return Root;
}

void AddRBT_Rekur(int X, struct Vertex *&v)
{
	if(v==NULL)
	{
		v = AddVertex(X);
	}
	else if(X<v->data) AddRBT_Rekur(X,v->Left);
	else if(X>v->data) AddRBT_Rekur(X,v->Right);
}

Vertex* RBT_Rekur(int Z[])
{
	struct Vertex* Root = NULL;
	for(int i=1;i<=100;i++)
	{
		AddRBT_Rekur(Z[i],Root);
	}
	return Root;
}

void Tree_Info(Vertex* Root, char text[])
{
	printf("\n\n%s\n",text);
	printf("Обход слева направо:\n");
	Obhod(Root);
	printf("\n");
	printf("Размер дерева: %i\n", Size(Root));
	printf("Сумма дерева: %i\n", Sum(Root));
	printf("Высота дерева: %i\n", Height(Root));
	printf("Средняя высота дерева: %f\n", Average_Height(Root));
	if(CheckTreeSearch(Root)==0) printf("Это не дерево поиска\n");
	else
	{
		printf("Это дерево поиска\n");
		int X=144;
		printf("Ищем элемент %i\n",X);
		if(TreeSearch(Root,X)!=NULL) printf("Элемент %i найден",TreeSearch(Root,X)->data);
		else printf("Элемент %i не найден",X);
	}
}

void DeleteRBT(int X, struct Vertex* &Root)
{
	struct Vertex** v=&Root;
	struct Vertex* r;
	struct Vertex* s;
	while(*v!=NULL)
	{
		if((*v)->data<X) v=&((*v)->Right);
		else if((*v)->data>X) v=&((*v)->Left);
		else break;
	}
	if(*v!=NULL)
	{
		struct Vertex* q=*v;
		if (q->Left==NULL && q->Right == NULL) *v=NULL;
		else if(q->Left==NULL) *v=q->Right;
		else if(q->Right == NULL) *v = q->Left;
		else if(q->Left!=NULL && q->Right!=NULL)
		{
			r=q->Left;
			s=q;
			while(r->Right!=NULL)
			{
				
				s=r;
				r=r->Right;
			}
			if(r!=q->Left)
			{
				s->Right=r->Left;
				r->Left=q->Left;
			}
			r->Right=q->Right;
			*v=r;
		}
		delete q;
	}
}

int main()
{
	srand(8);
	struct Vertex *Root =NULL;
	system("chcp 1251>nul");
	int A=1, B=100, X;
	int Z[101];
	FillIncRand(Z,100);
	PrintMas(Z,100);
	Root=RBT_Double(Z);
	Tree_Info(Root,"Случайное дерево поиска (Двойная косвенность)");
	printf("\n\nВведите вершины со значениями, которые хотите удалить:\n");
	for(int i=1;i<=10;i++)
	{
		X=Z[i];
		DeleteRBT(X,Root);
		printf("\n\nУдалена %i-ая вершина со значением %i из случайного дерева поиска",i+1,X);
		Tree_Info(Root,"Удалена вершина");
	}
	return 0;
}
