#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int i,j;
int C=0,M=0,K=0;
float M2=0;
int const A=1000, B=1000000;
int const Ciyr[9]={1,4,10,23,57,132,301,701,1750};

struct CellPhone
{
	char lastname[20];
	char name[20];
	char phone[20];
	char address[30];
};

struct Spisok
{
	struct Spisok *next;
	union
	{	
		int data;
		unsigned char Digit[sizeof(data)];
	};
};

int random (int N)
{
	return rand()%N;
}
void FillInc(int Z[], int N)
{
	for(i=1;i<=N;i++) Z[i]=i;
}
void FillDec (int Z[], int N)
{
	for(i=N;i>0;i--) Z[N-i+1]=i;
}
void FillRand (int Z[], int N, int A, int B)
{
	for(i=1;i<=N;i++) Z[i]=random(B-A+1)+A;
}
void PrintMas(int Z[], int N)
{
	printf("\nNew massive\n");
	for(i=1;i<=N;i++) printf("%i ",Z[i]);
}
void CheckSum(int Z[], int N)
{
	int s=Z[1];
	for(i=2;i<=N;i++) s+=Z[i];
	printf("\nNew Summa of massive:\t%i",s);
}
void RunNumber(int Z[], int N)
{
	int k=1;
	for(i=1;i<N;i++)
	{
		if(Z[i+1]<Z[i]) {k+=1;}
	}
	printf("\nNumber of serii:\t%i",k);
}
void SelectSort(int Z[], int N)
{
	int min,t;
	for(i=1;i<N;i++)
	{
		min=i;
		for(j=i+1;j<=N;j++)
		{
			C++;
			if(Z[min]>Z[j]) 
			{
				min=j;
			}
		}
		t=Z[i];
		Z[i]=Z[min];
		Z[min]=t;
		M+=3;
	}
}
void ZeroOut()
{
	C=0;
	M=0;
	K=0;
}
void Difficulty()
{
	printf("\nDifficulty on this moment:\t%i\t(%i+%i)",C+M,C,M);
}
void SelectSortT(int N)
{
	printf("\nTeoretic difficulty on this moment:\t%i\t(%i+%i)",(N-1)*(N+6)/2,N*(N-1)/2,3*(N-1));
}
void SelectSortMod(int Z[], int N)
{
	int min,t;
	for(i=1;i<N;i++)
	{
		min=i;
		for(j=i+1;j<=N;j++)
		{
			C++;
			if(Z[min]>Z[j]) 
			{
				min=j;
			}
		}
		if(min!=i)
		{
			t=Z[i];
			Z[i]=Z[min];
			Z[min]=t;
			M+=3;
		}
	}
}
void BubbleSort(int Z[], int N)
{
	int t;
	for(i=1;i<N;i++)
	{
		for(j=N;j>i;j--)
		{
			C++;
			if(Z[j]<Z[j-1])
			{
				t=Z[j];
				Z[j]=Z[j-1];
				Z[j-1]=t;
				M+=3;
			}
		}
	}
}
void ShakerSort(int Z[], int N)
{
	int l=1,r=N,k=N,t;
	do
	{
		for(j=r;j>l;j--)
		{
			C++;
			if(Z[j]<Z[j-1])
			{
				t=Z[j];
				Z[j]=Z[j-1];
				Z[j-1]=t;
				k=j;
				M+=3;
			}
		}
		l=k;
		for(j=l;j<r;j++)
		{
			C++;
			if(Z[j]>Z[j+1])
			{
				t=Z[j];
				Z[j]=Z[j+1];
				Z[j+1]=t;
				M+=3;
				k=j;
			}
		}
		r=k;
	}while(l<r);
}
int CTM()
{
	return C+M;
}
void InsertSort(int Z[], int N)
{
	int t;
	for(i=2;i<=N;i++)
	{
		t=Z[i];
		M++;
		j=i-1;
		while((j>0) && (t<Z[j]))
		{
			C++;
			Z[j+1]=Z[j];
			M++;
			j--;
		}
		if(j>0)
		{
			C++;
		}
		Z[j+1]=t;
		M++;
	}
}
void InsertSortT500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nInsert sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				InsertSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				InsertSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			ZeroOut();
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				InsertSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}
void SelectSortT500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nSelect sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				SelectSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				SelectSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				SelectSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}
void BubbleSortT500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nBubble sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				BubbleSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				BubbleSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				BubbleSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}
void ShakerSortT500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nShaker sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				ShakerSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				ShakerSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				ShakerSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}

int ShellNumber(int N)
{
	int r=0,h=1;
	while(N>1)
	{
		N=N/2;
		r++;
	}
	r--;
	while(r>0)
	{
		h*=2;
		r--;
	}
	h--;
	printf("\nShellNumber: %i",h);
	return h;
}

void ShellSort(int Z[],int N)
{
	int k=ShellNumber(N),t;
	while(k>=1)
	{
		for(i=k+1;i<=N;i++)
		{
			t=Z[i];
			M++;
			j=i-k;
			while((j>0) && (t<Z[j]))
			{
				C++;
				Z[j+k]=Z[j];
				M++;
				j=j-k;
			}
			if(j>0)
			{
				C++;
			}
			Z[j+k]=t;
			M++;
		}
		K++;
		k=k/2;
		printf("\nShellNumber: %i",k);
	}
}
void ShellSortT(int N,int Var)
{
	int k=ShellNumber(N);
	switch (Var)
	{
		case 0:
			while(k>=1)
			{
				C=C+N-k;
				M+=2*(N-k);
				k/=2;
			}
			printf("\nTeoretic difficulty Shellsort of this increment massive is:\t %i (%i+%i)",C+M,C,M);
			break;
		case 1:
			while(k>=1)
			{
				C+=N*(N-k)/2;
				M+=N*(N-k)/2+2*(N-k);
				k-=2;
			}
			printf("\nTeoretic difficulty Shellsort of this decrement massive is:\t %i (%i+%i)",C+M,C,M);
			break;
	}
}
void ShellSortT500(int C5[], int N, int Del, int T[], int KSort[],int Var)
{
	int m;
	printf("\n\nShell sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				ShellSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				ShellSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				ShellSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}
int ShellNumberMod(int N)
{
	int r=0;
	while((Ciyr[r]<N)&&(r<9))
	{
		r++;
	}
	r--;
	printf("\nShellNumberMod: %i",Ciyr[r]);
	return r;
}

void ShellSortMod(int Z[],int N)
{
	int r=ShellNumberMod(N), k=Ciyr[r],t;
	while(r>=0)
	{
		for(i=k+1;i<=N;i++)
		{
			t=Z[i];
			M++;
			j=i-k;
			while((j>0) && (t<Z[j]))
			{
				C++;
				Z[j+k]=Z[j];
				M++;
				j=j-k;
			}
			if(j>0)
			{
				C++;
			}
			Z[j+k]=t;
			M++;
		}
		K++;
		r--;
		k=Ciyr[r];
	}
}
void ShellSortModT500(int C5[], int N, int Del, int T[], int KSort[],int Var)
{
	int m;
	printf("\n\nShell sort MOD massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				ShellSortMod(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				ShellSortMod(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				ShellSortMod(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				KSort[m-1]=K;
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}


int BSearch1(int Z[], int N, int X)
{
	int L=1, R=N,m;
	while(L<R)
	{
		m=(L+R)/2;
		C++;
		if(Z[m]==X)
		{
			return m;
		}
		C++;
		if(Z[m]<X)
		{
			L=m+1;
		}
		else
		{
			R=m-1;
		}
	}
	return 0;
}
int BSearch2(int Z[], int N, int X)
{
	int L=1, R=N,m;
	while(L<R)
	{
		m=(L+R)/2;
		C++;
		if(Z[m]<X)
		{
			L=m+1;
		}
		else
		{
			R=m;
		}
	}
	C++;
	if(Z[R]==X) 
	{
		return R;
	}
	else 
	{
		return 0;
	}
}
int BSearchAll_1(int Z[], int N, int X, int dif[])
{
	int L=1, R=N,m;
	while(L<R)
	{
		m=(L+R)/2;
		C++;
		if(Z[m]==X)
		{
			C++;
			if(Z[m-1]!=X)
			{
				break;
			}
		}
		C++;
		if(Z[m]<X)
		{
			L=m+1;
		}
		else 
		{
			R=m-1;
		}
		
	}
	L=1,R=N;
	dif[0]=m;
	while(L<R)
	{
		m=(L+R)/2;
		C++;
		if(Z[m]==X)
		{
			C++;
			if(Z[m+1]!=X)
			{
				dif[1]=m;
				return 1;
			}
		}
		C++;
		if(Z[m]>X)
		{
			R=m-1;
		}
		else 
		{
			L=m+1;
		}
		
	}
	return 0;
}
int BSearchAll_2(int Z[], int N, int X, int dif[])
{
	dif[0]=BSearch2(Z,N,X);
	int L=1, R=N,m;
	while(L<R)
	{
		m=(L+R)/2;
		C++;
		if(Z[m]>X)
		{
			R=m;
		}
		else
		{
			L=m+1;
		}
	}
	C++;
	if(Z[L-1]==X) 
	{
		dif[1]=L-1;
		return 1;
	}
	else 
	{
		return 0;
	}
}
void Heap(int Z[], int L, int R)
{
	int X=Z[L], i=L;
	M++;
	while(1)
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R)
		{
			C++;
			if(Z[j+1]<=Z[j]) j++;
		}
		C++;
		if(X<=Z[j])
		{
			break;
		}
		M++;
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
	M++;
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
		M+=3;
		t=Z[1];
		Z[1]=Z[R];
		Z[R]=t;
		R--;
		Heap(Z,1,R);
	}
}
void HeapSortT500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nHeap sort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				HeapSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				HeapSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				HeapSort(C5,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}
void BSearch1Mass(int C5[], int N, int Del, int T[],int X)
{
	int m,var;
	printf("\n\nFirst version of binar search one element");
	for(m=1;m<=Del;m++)
	{
		FillRand(C5,(N/Del)*m,A,B);
		ShellSort(C5,(N/Del)*m);
		ZeroOut();
		if(var=BSearch1(C5,(N/Del)*m,X))
		{
			printf("\nElement of massive found: %i",var);
		}
		else
		{
			printf("\nElement of massive not found");
		}
		Difficulty();
		T[m-1]=CTM();
		ZeroOut();
	}
}
void BSearch2Mass(int C5[], int N, int Del, int T[],int X)
{
	int m,var;
	printf("\n\nSecond version of binar search one element");
	for(m=1;m<=Del;m++)
	{
		FillRand(C5,(N/Del)*m,A,B);
		ShellSort(C5,(N/Del)*m);
		ZeroOut();
		if(var=BSearch2(C5,(N/Del)*m,X))
		{
			printf("\nElement of massive found: %i",var);
		}
		else
		{
			printf("\nElement of massive not found");
		}
		Difficulty();
		T[m-1]=CTM();
		ZeroOut();
	}
}
void BSearchAll_1Mass(int C5[], int N, int Del, int T[],int X, int dif[])
{
	int m;
	printf("\n\nFirst version of binar search all elements with with value %i",X);
	for(m=1;m<=Del;m++)
	{
		FillRand(C5,(N/Del)*m,A,B);
		ShellSort(C5,(N/Del)*m);
		ZeroOut();
		if(BSearchAll_1(C5,(N/Del)*m,X,dif))
		{
			printf("\nElements of massive found: from %i to %i",dif[0],dif[1]);
		}
		else
		{
			printf("\nElements of massive not found");
		}
		Difficulty();
		T[m-1]=CTM();
		ZeroOut();
		dif[0]=0;
		dif[1]=0;
	}
}
void BSearchAll_2Mass(int C5[], int N, int Del, int T[],int X, int dif[])
{
	int m;
	printf("\n\nFirst version of binar search all elements with with value %i",X);
	for(m=1;m<=Del;m++)
	{
		FillRand(C5,(N/Del)*m,A,B);
		ShellSort(C5,(N/Del)*m);
		ZeroOut();
		if(BSearchAll_2(C5,(N/Del)*m,X,dif))
		{
			printf("\nElements of massive found: from %i to %i",dif[0],dif[1]);
		}
		else
		{
			printf("\nElements of massive not found");
		}
		Difficulty();
		T[m-1]=CTM();
		ZeroOut();
		dif[0]=0;
		dif[1]=0;
	}
}
int less(struct CellPhone X, struct CellPhone Y)
{
	if(strcmp(X.lastname,Y.lastname)<0)
	{           
		return 1;
	}
	if(strcmp(X.lastname,Y.lastname)>0)
	{           
		return 0;
	}
	if(strcmp(X.name,Y.name)<0)
	{           
		return 1;
	}
	return 0;
}
void PrintCell(struct CellPhone X)
{
	printf("%22s",X.lastname);
	printf("%22s",X.name);
	printf("%17s",X.phone);
	printf("%32s",X.address);
	printf("\n");
}
void PrintAllCell(struct CellPhone X[],int N)
{
	int m;
	printf("\n\n");
	for(m=1;m<=N;m++)
	{
		PrintCell(X[m]);
	}
}
void PrintAllIndex(struct CellPhone X[],int Z[],int N)
{
	int m;
	printf("\n\n");
	for(m=1;m<=N;m++)
	{
		PrintCell(X[Z[m]]);
	}
}
void ShellSortModStruct(struct CellPhone X[],int Z[], int N)
{
	int r=ShellNumberMod(N), k=Ciyr[r],t;
	while(r>=0)
	{
		for(i=k+1;i<=N;i++)
		{
			t=Z[i];
			j=i-k;
			while((j>0) && (less(X[t],X[Z[j]])))
			{
				Z[j+k]=Z[j];
				j=j-k;
			}
			Z[j+k]=t;
		}
		r--;
		k=Ciyr[r];
	}
}
int LessBSearch2(struct CellPhone S[], int Z, char X[], char Y[])
{
	if(strcmp(S[Z].lastname,X)<0)
	{
		return 1;
	}
	if(strcmp(S[Z].lastname,X)>0)
	{
		return 0;
	}
	if(strcmp(S[Z].name,Y)<0)
	{
		return 1;
	}
	return 0;
}
int BSearch2Cell(struct CellPhone S[], int Z[], int N, char X[], char Y[])
{
	int L=1, R=N,m;
	while(L<R)
	{
		m=(L+R)/2;
		if(LessBSearch2(S,Z[m],X,Y))
		{
			L=m+1;
		}
		else
		{
			R=m;
		}
	}
	if((strcmp(S[Z[R]].lastname,X)==0)&&(strcmp(S[Z[R]].name,Y)==0))
	{
		return Z[R];
	}
	else
	{
		return 0;
	}
}
void QuickSort1(int Z[], int L, int R)
{
	int x=Z[rand()%(R-L+1)+L],i=L,j=R,t;
	while(i<=j)
	{
		while(Z[i]<x)
		{
			i++;
			C++;
		}
		while(Z[j]>x)
		{
			j--;
			C++;
		}
		if(i<=j)
		{
			t=Z[i];
			Z[i]=Z[j];
			Z[j]=t;
			i++;
			j--;
			M+=3;
		}
	}
	if(L<j)
	{
		QuickSort1(Z,L,j);
	}
	if(i<R)
	{
		QuickSort1(Z,i,R);
	}
}

void QuickSort1T500(int C5[], int N, int Del, int T[],int Var)
{
	int m;
	printf("\n\nQuick sort 1 version massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc(C5,(N/Del)*m);
				QuickSort1(C5,1,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec(C5,(N/Del)*m);
				QuickSort1(C5,1,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand(C5,(N/Del)*m,A,B);
				QuickSort1(C5,1,(N/Del)*m);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}


void Delete_Spisok(struct Spisok **head, struct Spisok **tail)
{
	struct Spisok *p,*pp;
	for(p=*head;p;p=pp)
	{
		pp=p->next;
		delete(p);
	}
	*head=NULL;
	*tail=NULL;
}
void FillInc_Stack(struct Spisok **head, int N)
{
	struct Spisok *p;
	for(i=N;i>0;i--)
	{
		p=new Spisok;
		p->data=i;
		p->next=*head;
		*head=p;
	}
}
void FillDec_Stack (struct Spisok **head, int N)
{
	struct Spisok *p;
	for(i=1;i<=N;i++)
	{
		p=new Spisok;
		p->data=i;
		p->next=*head;
		*head=p;
	}
}
void FillRand_Stack (struct Spisok **head, int N, int A, int B)
{
	struct Spisok *p;
	for(i=N;i>0;i--)
	{
		p=new Spisok;
		p->data=random(B-A+1)+A;
		p->next=*head;
		*head=p;
	}
}

void FillInc_Line(struct Spisok **head, struct Spisok *tail, int N)
{
	tail=(Spisok*) &(*head);
	struct Spisok *p;
	for(i=1;i<=N;i++)
	{
		p=new Spisok;
		p->data=i;
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
}

void FillDec_Line(struct Spisok **head, struct Spisok *tail, int N)
{
	tail=(Spisok*) &(*head);
	struct Spisok *p;
	for(i=N;i>0;i--)
	{
		p=new Spisok;
		p->data=i;
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
}

void FillRand_Line(struct Spisok **head, struct Spisok *tail, int N, int A, int B)
{
	tail=(Spisok*) &(*head);
	struct Spisok *p;
	for(i=1;i<=N;i++)
	{
		p=new Spisok;
		p->data=random(B-A+1)+A;
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
}

void PrintSpisok(struct Spisok *head, int N)
{
	printf("\nNew spisok\n");
	struct Spisok *p;
	p=head;
	i=1;
	while((p!=NULL)&&(i<=N))
	{
		printf("%i ",p->data);
		i++;
		p=p->next;
	}
}

void CheckSumSpisok(struct Spisok *head, int N)
{
	int s=0;
	struct Spisok *p;
	p=head;
	i=1;
	while((p!=NULL)&&(i<=N))
	{
		s+=p->data;
		i++;
		p=p->next;
	}
	printf("\nNew Summa of massive:\t%i",s);
}
void RunNumberSpisok(struct Spisok *head, int N)
{
	int k=1;
	struct Spisok *p;
	p=head;
	i=1;
	while((p->next!=NULL)&&(i<N))
	{
		if(p->next->data < p->data) k++;
		i++;
		p=p->next;
	}
	printf("\nNumber of serii:\t%i",k);
}

void FillSeriya_Stack(struct Spisok **head, int N, int A, int B)
{
	struct Spisok *p;
	int j=0;
	for(i=N;i>0;i--)
	{
		p=new Spisok;
		p->data=random(B-A+1)+j+1;
		j=p->data;
		p->next=*head;
		*head=p;
	}
}

void FillSeriya_Line(struct Spisok **head, struct Spisok *tail, int N, int A, int B)
{
	tail=(Spisok*) &(*head);
	struct Spisok *p;
	int j=0;
	for(i=N;i>0;i--)
	{
		p=new Spisok;
		p->data=random(B-A+1)+j+1;
		j=p->data;
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
}

void Split_Stack(struct Spisok **S, struct Spisok **a, struct Spisok **b, int &N)
{
	struct Spisok *p, *k;
	*a=*S;
	*b=(*S)->next;
	k=*a;
	p=*b;
	N=1;
	while(p != NULL)
	{
		N++;
		k->next=p->next;
		k=p;
		p=p->next;
	}
}

void Merge_Seriya(struct Spisok **a, int q, struct Spisok **b, int r, struct Spisok **c)
{
	struct Spisok *tail;
	tail=(Spisok*)&(*c);
	
	while(q!=0 && r!=0)
	{
		C++;
		if((*a)->data <= (*b)->data)
		{
			tail->next=*a;
			tail=*a;
			*a=(*a)->next;
			q--;
			M++;
		}
		else
		{
			tail->next=*b;
			tail=*b;
			*b=(*b)->next;
			r--;
			M++;
		}
	}
	while(q>0)
	{
		tail->next=*a;
		tail=*a;
		*a=(*a)->next;
		q--;
		M++;
	}
	while(r>0)
	{
		tail->next=*b;
		tail=*b;
		*b=(*b)->next;
		r--;
		M++;
	}
	tail->next=NULL;
}

void Merge_Seriya(struct Spisok **a, int q, struct Spisok **b, int r, struct Spisok **c, struct Spisok **tail)
{
	while(q!=0 && r!=0)
	{
		C++;
		if((*a)->data <= (*b)->data)
		{
			(*tail)->next=*a;
			*tail=*a;
			*a=(*a)->next;
			M++;
			q--;
		}
		else
		{
			(*tail)->next=*b;
			*tail=*b;
			*b=(*b)->next;
			M++;
			r--;
		}
	}
	while(q>0)
	{
		(*tail)->next=*a;
		*tail=*a;
		*a=(*a)->next;
		q--;
		M++;
	}
	while(r>0)
	{
		(*tail)->next=*b;
		*tail=*b;
		*b=(*b)->next;
		r--;
		M++;
	}
	(*tail)->next=NULL;
}

void MergeSort(struct Spisok **S)
{
	struct Spisok *a,*b,*c[2],*tail_c[2];
	int N;
	a=NULL;
	b=NULL;
	Split_Stack(&(*S),&a,&b,N);
	int p=1,q,r,m;
	while(p<N)
	{
		c[0]=NULL;
		c[1]=NULL;
		tail_c[0]=(Spisok*)&(c[0]);
		tail_c[1]=(Spisok*)&(c[1]);
		i=0;
		m=N;
		while(m>0)
		{
			if(m>=p)
			{
				q=p;
			}
			else
			{
				q=m;
			}
			m-=q;
			if(m>=p)
			{
				r=p;
			}
			else
			{
				r=m;
			}
			m-=r;
			Merge_Seriya(&a,q,&b,r,&c[i],&tail_c[i]);
			i=1-i;
		}
		a=c[0];
		b=c[1];
		p*=2;
	}
	(*S)=c[0];
	M=M*3/2;
}

void MergeSort500(struct Spisok *head, int N, int Del, int T[],int Var)
{
	int m;
	struct Spisok *tail=NULL;
	printf("\n\nMergeSort massives");
	switch(Var)
	{
		case 0:
			printf("\nOn Increment massives");
			for(m=1;m<=Del;m++)
			{
				FillInc_Stack(&head,(N/Del)*m);
				MergeSort(&head);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
				Delete_Spisok(&head,&tail);
			}
			break;
		case 1:
			printf("\nOn Decrement massives");
			for(m=1;m<=Del;m++)
			{
				FillDec_Stack(&head,(N/Del)*m);
				MergeSort(&head);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
				Delete_Spisok(&head,&tail);
			}
			break;
		case 2:
			printf("\nOn Random massives");
			for(m=1;m<=Del;m++)
			{
				FillRand_Stack(&head,(N/Del)*m,A,B);
				MergeSort(&head);
				Difficulty();
				T[m-1]=CTM();
				ZeroOut();
				Delete_Spisok(&head,&tail);
			}
			break;
		default:
			printf("Other massive we don't have");
	}
}

/*void DigitalSort()
{
	
	while(j=L;j>=1;j--)
	{
		while(i=0;i<=255;i++)
		{
			
		}
	}
}*/

void DigitalSort (struct Spisok **head) 
{
	int KDI[sizeof(int)]={3,2,1,0};
	int d, i, j, k, L=sizeof(int);
	struct Spisok *p;
	struct Spisok *Q[256];
	struct Spisok *tail_Q[256];
	for (j=L-1; j>=0; j--) 
    {
		for (i=0; i<256; i++) tail_Q[i]=(Spisok*)&Q[i];
		p=*head;
		k=KDI[j];
		while (p!=NULL) 
        {
			d=p->Digit[k];
			tail_Q[d]->next=p;
			tail_Q[d]=p;
			p=p->next;
			M++;
		}
		p=(Spisok*)&(*head);
		for (i=0; i<256; i++) 
        {
			if (tail_Q[i]!=(Spisok*)&Q[i]) 
            {
				p->next=Q[i];
				p=tail_Q[i];
			}
		}
		p->next=NULL;
	}
}
