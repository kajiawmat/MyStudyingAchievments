#include<stdio.h>
#include<stdlib.h>


int Rost;
int Umen;

int Turn_Add=0;
int Turn_Del=0;

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

struct Vertex* RandVertex(int N)
{
	struct Vertex* v = new struct Vertex;
	v->data=rand()%N;
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
		*v = new struct Vertex;
		(*v)->data = X;
		(*v)->Right = NULL;
		(*v)->Left = NULL;
	}
}

struct Vertex* RBT_Double(int Z[])
{
	struct Vertex* Root = NULL;
	for(int i=1;i<=100;i++)
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

void LL1_Turn(Vertex* &p)
{
	Vertex* q=p->Left;
	if(q->Bal==0)
	{
		p->Bal=-1;
		q->Bal=1;
		Umen=0;
	}
	else
	{
		p->Bal=0;
		q->Bal=0;
	}
	p->Left=q->Right;
	q->Right=p;
	p=q;
}

void RR1_Turn(Vertex* &p)
{
	Vertex* q=p->Right;
	if(q->Bal==0)
	{
		p->Bal=1;
		q->Bal=-1;
		Umen=0;
	}
	else
	{
		p->Bal=0;
		q->Bal=0;
	}
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
		Turn_Add++;
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
		Turn_Add++;
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

void BL1(Vertex *&v)
{
	if(v->Bal==-1)
	{
		v->Bal=0;
	}
	else if(v->Bal==0)
	{
		v->Bal=1;
		Umen=0;
	}
	else
	{
		if(v->Right->Bal>=0) RR1_Turn(v);
		else RL_Turn(v);
		Turn_Del++;
	}
}

void BR1(Vertex* &v)
{
	if(v->Bal==1)
	{
		v->Bal=0;
	}
	else if(v->Bal==0)
	{
		v->Bal=-1;
		Umen=0;
	}
	else
	{
		if(v->Left->Bal<=0) LL1_Turn(v);
		else LR_Turn(v);
		Turn_Del++;
	}
}

void Delete_Vertex_Double(Vertex *&r, Vertex* &q)
{
	if(r->Right!=NULL)
	{
		Delete_Vertex_Double(r->Right,q);
		if(Umen) BR1(r);
	}
	else
	{
		q->data=r->data;
		q=r;
		r=r->Left;
		Umen=1;
	}
}

void DeleteAVL_Tree(int X, Vertex* &v)
{
	if(v==NULL);
	else if(X<v->data)
	{
		DeleteAVL_Tree(X,v->Left);
		if(Umen) BL1(v);
	}
	else if(X>v->data)
	{
		DeleteAVL_Tree(X,v->Right);
		if(Umen) BR1(v);
	}
	else
	{
		Vertex* q=v;
		if(q->Left==NULL)
		{
			v=q->Right;
			Umen=1;
		}
		else if(q->Right==NULL)
		{
			v=q->Left;
			Umen=1;
		}
		else 
		{
			Delete_Vertex_Double(q->Left,q);
			if(Umen) BL1(v);
		}
		delete q;
	}
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
		printf("\n");
	}
}

struct Vertex* AVL_Tree(int Z[],int N)
{
	struct Vertex* Root = NULL;
	for(int i=1;i<=N;i++)
	{
		Rost=0;
		AddAVL_Tree(Z[i],Root);
	}
	return Root;
}

int main()
{
	srand(8);
	const int N=10;
	struct Vertex *Root =NULL;
	system("chcp 1251>nul");
	int A=1, B=N, X;
	int Z[N+1];
	FillIncRand(Z,N);
	PrintMas(Z,N);
	Root=AVL_Tree(Z,N);
	Tree_Info(Root,"АВЛ-Дерево");
	printf("\n\nВведите вершины со значениями, которые хотите удалить:\n");
	for(int i=1;i<=N;i++)
	{
		Umen=0;
		DeleteAVL_Tree(Z[i],Root);
		printf("\n\nУдалена %i-ая вершина со значением %i из AVL-дерева\n",i,Z[i]);
		Tree_Info(Root,"Удалена вершина");
	}
	printf("\n\nКол-во поворотов при добавлении: %i(%.2f)",Turn_Add,(float)Turn_Add/N);
	printf("\n\nКол-во поворотов при удалении: %i(%.2f)",Turn_Del,(float)Turn_Del/N);
	return 0;
}
