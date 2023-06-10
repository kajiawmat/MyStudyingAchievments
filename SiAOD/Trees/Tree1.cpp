#include<stdio.h>
#include<stdlib.h>

struct Vertex
{
	int data;
	struct Vertex *Left;
	struct Vertex *Right;
};

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

void Tree_Info(Vertex* Root)
{
	printf("\n����� ����� �������:\n");
	Obhod(Root);
	printf("\n");
	printf("������ ������: %i\n", Size(Root));
	printf("����� ������: %i\n", Sum(Root));
	printf("������ ������: %i\n", Height(Root));
	printf("������� ������ ������: %f\n", Average_Height(Root));
}

int main()
{
	struct Vertex *Root;
	system("chcp 1251>nul");
	printf("�������� ������ ������ ����:\n");
	Root = RandVertex();
	Root->Left = RandVertex();
	Root->Left->Right = RandVertex();
	Root->Left->Right->Left = RandVertex();
	Root->Right = RandVertex();
	Root->Right->Right = RandVertex();
	Tree_Info(Root);
	return 0;
}
