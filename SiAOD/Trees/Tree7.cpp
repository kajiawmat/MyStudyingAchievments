#include<stdio.h>
#include<stdlib.h>

int VR, HR;
int Rost;

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

struct Vertex
{
	int data;
	struct Vertex *Left;
	struct Vertex *Right;
	int Bal;
};

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

struct Vertex* AddVertex(int x)
{
	struct Vertex* v = new struct Vertex;
	v->data=x;
	v->Left=NULL;
	v->Right=NULL;
	v->Bal=0;
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

int HeightDBT(Vertex* v)
{
	if(v==NULL) return 0;
	if(v->Bal) return 1+Max(HeightDBT(v->Left),Max(HeightDBT(v->Right->Left),HeightDBT(v->Right->Right)));
	return 1+Max(HeightDBT(v->Left),HeightDBT(v->Right));
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


void LL_Turn(Vertex* &p)
{
	Vertex* q=p->Left;
	p->Bal=0;
	q->Bal=0;
	p->Left=q->Right;
	q->Right=p;
	p=q;
}

void RR_Turn(Vertex* &p)
{
	Vertex* q=p->Right;
	p->Bal=0;
	q->Bal=0;
	p->Right=q->Left;
	q->Left=p;
	p=q;
}

void RL_Turn(Vertex* &p)
{
	Vertex* q=p->Right;
	Vertex* r=q->Left;
	if(r->Bal>0) p->Bal=-1;
	else p->Bal=0;
	if(r->Bal<0) q->Bal=1;
	else q->Bal=0;
	r->Bal=0;
	q->Left=r->Right;
	p->Right=r->Left;
	r->Left=p;
	r->Right=q;
	p=r;
}

void LR_Turn(Vertex* &p)
{
	Vertex* q=p->Left;
	Vertex* r=q->Right;
	if(r->Bal<0) p->Bal=1;
	else p->Bal=0;
	if(r->Bal>0) q->Bal=-1;
	else q->Bal=0;
	r->Bal=0;
	q->Right=r->Left;
	p->Left=r->Right;
	r->Right=p;
	r->Left=q;
	p=r;
}

void BL(Vertex* &v)
{
	if(v->Bal>0)
	{
		v->Bal=0;
		Rost=0;
	}
	else if(v->Bal==0)
	{
		v->Bal=-1;
		Rost=1;
	}
	else
	{
		if(v->Left->Bal<0) LL_Turn(v); 
		else LR_Turn(v);
		Rost=0;
	}
}

void BR(Vertex* &v)
{
	if(v->Bal<0)
	{
		v->Bal=0;
		Rost=0;
	}
	else if(v->Bal==0)
	{
		v->Bal=1;
		Rost=1;
	}
	else
	{
		if(v->Right->Bal>0) RR_Turn(v); 
		else RL_Turn(v);
		Rost=0;
	}
}

void AddAVL_Tree(int D, Vertex* &v)
{
	if(v==NULL)
	{
		v=AddVertex(D);
		v->Bal=0;
		Rost=1;
	}
	else if(v->data>D) 
	{
		AddAVL_Tree(D,v->Left);
		if(Rost) BL(v);
	}
	else if(v->data<D)
	{
		AddAVL_Tree(D,v->Right);
		if(Rost) BR(v);
	}
}

struct Vertex* AVL_Tree(int Z[])
{
	struct Vertex* Root = NULL;
	for(int i=1;i<=100;i++)
	{
		Rost=0;
		AddAVL_Tree(Z[i],Root);
	}
	return Root;
}

void AddDBD(int X, Vertex* &v)
{
	if(v==NULL)
	{
		v=AddVertex(X);
		v->Bal=0;
		VR=1;
	}
	else if(X<v->data)
	{
		AddDBD(X,v->Left);
		if(VR)
		{
			if(v->Bal==0)
			{
				Vertex* q=v->Left;
				v->Left=q->Right;
				q->Right=v;
				v=q;
				q->Bal=1;
				VR=0;
				HR=1;
			}
			else
			{
				v->Bal=0;
				VR=1;
				HR=0;
			}
		}
		else HR=0;
	}
	else if(X>v->data)
	{
		AddDBD(X,v->Right);
		if(VR)
		{
			v->Bal=1;
			HR=1;
			VR=0;
		}
		else if(HR)
		{
			if(v->Bal) 
			{
				Vertex* q=v->Right;
				v->Bal=0;
				q->Bal=0;
				v->Right=q->Left;
				q->Left=v;
				v=q;
				VR=1;
				HR=0;
			}
			else HR=0;
		}
	}
}

struct Vertex* DBT(int Z[])
{
	HR=1;
	VR=1;
	struct Vertex* Root = NULL;
	for(int i=1;i<=100;i++)
	{
		AddDBD(Z[i],Root);
	}
	return Root;
}

void Tree_Info(Vertex* Root, char text[], int i)
{
	printf("\n\n%s\n",text);
	printf("Обход слева направо:\n");
	Obhod(Root);
	printf("\n");
	printf("Размер дерева: %i\n", Size(Root));
	printf("Сумма дерева: %i\n", Sum(Root));
	printf("Высота дерева: %i\n", Height(Root));
	if(i) printf("Кол-во уровней Б-дерева: %i\n", HeightDBT(Root));
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


int main()
{
	srand(10);
	struct Vertex *Root =NULL;
	system("chcp 1251>nul");
	int A=1, B=100;
	int Z[101];
	for(int i=0;i<5;i++)
	{
	FillIncRand(Z,100);
	PrintMas(Z,100);
	Root=AVL_Tree(Z);
	Tree_Info(Root,"АВЛ-дерево",0);
	Root=DBT(Z);
	Tree_Info(Root,"Двоичное Б-Дерево",1);
	}
	return 0;
}
