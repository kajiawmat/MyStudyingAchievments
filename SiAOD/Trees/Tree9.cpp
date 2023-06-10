#include<stdio.h>
#include<stdlib.h>

int random (int N)
{
	return rand()%N;
}

void PrintMatrix(int **Z)
{
	printf("\n");
	for(int i=0;i<=10;i++)
	{
		for(int j=90;j<=100;j++)
		{
			printf("%-4i ",Z[i][j]);
		}
		printf("\n");
	}
	printf("\n");
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
	int W;
};

struct Data_Vertex
{
	int data;
	int W;
};


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

void Heap(Data_Vertex Z[], int L, int R)
{
	Data_Vertex X=Z[L]; 
	int i=L, j;
	while(1)
	{
		j=2*i;
		if(j>R) break;
		if((j<R)&&(Z[j+1].W<=Z[j].W)) j++;
		if(X.W<Z[j].W) break;
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}

void HeapSort(Data_Vertex Z[], int N)
{
	int L=N/2, R=N;
	Data_Vertex t;
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

void PrintMas(Data_Vertex X[], int N)
{
	printf("\nНовый массив\n");
	for(int i=1;i<=N;i++) printf("%i:%i ",X[i].data,X[i].W);
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
	v->Bal=0;
	v->W=0;
	return v;
}

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

struct Vertex* AddVertex(Data_Vertex X)
{
	struct Vertex* v = new struct Vertex;
	v->data=X.data;
	v->Left=NULL;
	v->Right=NULL;
	v->Bal=0;
	v->W=X.W;
	return v;
}

void DataFillRand(Data_Vertex X[], int Z[])
{
	for(int i=1;i<101;i++)
	{
		X[i].data=Z[i];
		X[i].W=random(10)+1;
	}
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

void Matrix_Zero(int **AW, int **AP, int **AR)
{
	for(int i=0;i<=100;i++)
	{
		for(int j=0;j<=100;j++)
		{
			AW[i][j]=0;
			AP[i][j]=0;
			AR[i][j]=0;
		}
	}
}

void Fill_AW(Data_Vertex X[], int **AW)
{
	for(int i=0;i<100;i++)
	{
		for(int j=i+1;j<=100;j++)
		{
			AW[i][j]=AW[i][j-1]+X[j].W;
		}
	}
}

void Fill_AP_AR(int **AW, int **AP, int **AR)
{
	int i,j,h,m,min,x;
	for(int i=0;i<100;i++)
	{
		j=i+1;
		AP[i][j]=AW[i][j];
		AR[i][j]=j;
	}
	for(h=2;h<=100;h++)
	{
		for(i=0;i<(101-h);i++)
		{
			j=i+h;
			m=AR[i][j-1];
			min=AP[i][m-1]+AP[m][j];
			for(int k=m+1;k<=AR[i+1][j];k++)
			{
				x=AP[i][k-1]+AP[i][k];
				if(x<min)
				{
					m=k;
					min=x;
				}
			}
			AP[i][j]=min+AW[i][j];
			AR[i][j]=m;
		}
	}
}

void TOS(struct Vertex* &v, Data_Vertex X[], int **AR, int L, int R)
{
	if(L<R)
	{
		int k=AR[L][R];
		v=AddVertex(X[k]);
		TOS(v->Left,X,AR,L,k-1);
		TOS(v->Right,X,AR,k,R);
	}
}

void AddVertexA1(Vertex *&Root, Data_Vertex X)
{
	struct Vertex** v;
	v=&Root;
	while(*v!=NULL)
	{
		if(X.data<(*v)->data) v=&((*v)->Left);
		else if (X.data>(*v)->data) v=&((*v)->Right);
		else if (X.W>(*v)->W) (*v)->data=X.data, (*v)->W=X.W;
		else break;
	}
	if(*v == NULL)
	{
		*v = AddVertex(X);
	}
}

Vertex* A1_Tree(Data_Vertex X[])
{
	Vertex* Root=NULL;
	HeapSort(X,100);
	//PrintMas(X,100);
	for(int i=1;i<=100;i++)
	{
		AddVertexA1(Root,X[i]);
	}
	return Root;
}

void A2_Tree(Vertex* &v, Data_Vertex X[], int L, int R)
{
	int wes=0, sum=0;
	if(L<=R)
	{
		for(int i=L;i<=R;i++)
		{
			wes+=X[i].W;
		}
		int i;
		for(i=L;i<=R;i++)
		{
			if(sum<wes/2 && (sum+X[i].W)>wes/2) break;
			sum+=X[i].W;
		}
		if(i>R) i=R;
		v = AddVertex(X[i]);
		A2_Tree(v->Left,X,L,i-1);
		A2_Tree(v->Right,X,i+1,R);
	}
}

int SumHW(Vertex* v, int L)
{
	if(v==NULL) return 0;
	return v->W*L+SumHW(v->Left,L+1)+SumHW(v->Right,L+1);
}

int SumW(Vertex* v)
{
	if(v==NULL) return 0;
	return v->W+SumW(v->Left)+SumW(v->Right);
}

double HeightW(Vertex *Root)
{
	return (double)  SumHW(Root,1)/SumW(Root);
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
	if(i==1) printf("Кол-во уровней Б-дерева: %i\n", HeightDBT(Root));
	if(i==3)printf("Средне взвешенная высота дерева: %f\n", HeightW(Root));
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
	srand(5);
	struct Vertex *Root =NULL;
	system("chcp 1251>nul");
	int A=1, B=100;
	int Z[101];
	struct Data_Vertex X[101];
	FillIncRand(Z,100);
	HeapSort(Z,100);
	DataFillRand(X,Z);
	PrintMas(Z,100);
	PrintMas(X,100);
	int **AW, **AP, **AR;
	AW=new int*[101];
	AP=new int*[101];
	AR=new int*[101];
	for(int k=0;k<=100;k++)
	{
		AW[k]=new int[101];
		AP[k]=new int[101];
		AR[k]=new int[101];
	}
	Matrix_Zero(AW,AP,AR);
	Fill_AW(X,AW);
	Fill_AP_AR(AW,AP,AR);
	PrintMatrix(AW);
	PrintMatrix(AP);
	PrintMatrix(AR);
	TOS(Root,X,AR,0,100);
	Tree_Info(Root,"Дерево Оптимального Поиска",3);
	A2_Tree(Root,X,1,100);
	Tree_Info(Root,"Дерево Почтиоптимального Поиска А2",3);
	Root=A1_Tree(X);
	Tree_Info(Root,"Дерево Почтиоптимального Поиска А1",3);
	for(int k=0;k<=100;k++)
	{
		delete[] AW[k];
		delete[] AP[k];
		delete[] AR[k];
	}
	delete[] AW;
	delete[] AP;
	delete[] AR;
	return 0;
}
