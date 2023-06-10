#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h> 

int Num_of_Byte=0;

struct Byte_Chance
{
	unsigned char Num;
	double Chance;
};

double Average_Len(Byte_Chance Array[], int L[], int N)
{
	double res=0;
	for(int i=1;i<=N;i++)
	{
		res+=Array[i].Chance*L[i];
	}
	return res;
}

double N_Tropy(Byte_Chance Array[], int N)
{
	double res=0;
	for(int i=1;i<=N;i++)
	{
		res-=Array[i].Chance*log(Array[i].Chance)/log(2);
	}
	return res;
}

void Heap(Byte_Chance Z[], int L, int R)
{
	Byte_Chance X=Z[L]; int i=L, j;
	while(1)
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R)
		{
			if(Z[j+1].Chance<=Z[j].Chance) j++;
		}
		if(X.Chance<=Z[j].Chance)
		{
			break;
		}
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}
void HeapSort(Byte_Chance Z[], int N)
{
	int L=N/2, R=N;
	Byte_Chance t;
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

void Heap2(Byte_Chance Z[], int L, int R)
{
	Byte_Chance X=Z[L]; int i=L, j;
	while(1)
	{
		j=2*i;
		if(j>R)
		{
			break;
		}
		if(j<R)
		{
			if(Z[j+1].Num<=Z[j].Num) j++;
		}
		if(X.Num<=Z[j].Num)
		{
			break;
		}
		Z[i]=Z[j];
		i=j;
	}
	Z[i]=X;
}
void HeapSort2(Byte_Chance Z[], int N)
{
	int L=N/2, R=N;
	Byte_Chance t;
	while(L>0)
	{
		Heap2(Z,L,N);
		L--;
	}
	while(R>1)
	{
		t=Z[1];
		Z[1]=Z[R];
		Z[R]=t;
		R--;
		Heap2(Z,1,R);
	}
}

int MyLog(double X)
{
	double d=1;
	int i=0;
	if(X<d)
	{
		while(1)
		{
			if(X>=d) return i;
			else
			{
				d/=2;
				i--;
			}
		}
	}
	else if(X>d)
	{
		while(1)
		{
			if(X<d) return i;
			else
			{
				d*=2;
				i++;
			}
		}
	}
	else return i;
}

void Shannon(Byte_Chance Array[], double Q[], int L[],char C[][257],int N)
{
	Array[0].Chance=0;
	Q[0]=0;
	for(int i=1;i<=N;i++)
	{
		Q[i]=Q[i-1]+Array[i].Chance;
		L[i]=-MyLog(Array[i].Chance);
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=L[i];j++)
		{
			Q[i-1]=Q[i-1]*2;
			C[i][j]=(int)Q[i-1]+48;
			if(Q[i-1]>1) Q[i-1]--;
		}
	}
}

void Gilbert_Mur(Byte_Chance Array[], double Q[], int L[],char C[][257],int N)
{
	Array[0].Chance=0;
	Q[0]=0;
	for(int i=1;i<=N;i++)
	{
		Q[i]=Q[i-1]+Array[i-1].Chance/2+Array[i].Chance/2;
		L[i]=-MyLog(Array[i].Chance)+1;
	}
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=L[i];j++)
		{
			Q[i-1]=Q[i-1]*2;
			C[i][j]=(int)Q[i-1]+48;
			if(Q[i-1]>1) Q[i-1]--;
		}
	}
}

int Up(Byte_Chance Array[], int N, double q)
{
	int j=1;
	for(int i=N-1;i>=2;i--)
	{
		if(Array[i-1].Chance<=q) Array[i].Chance=Array[i-1].Chance;
		else 
		{
			if(j==1) j=i;
		}
	}
	Array[j].Chance=q;
	return j;
}

void Copy_Massive(char X[], char Y[],int N)
{
	for(int i=1;i<=N;i++)
	{
		X[i]=Y[i];
	}
}

void Down(char C[][257], int L[],int N, int j)
{
	char S[257];
	Copy_Massive(S,C[j],256);
	int LL=L[j];
	for(int i=j;i<=N-2;i++)
	{
		Copy_Massive(C[i],C[i+1],256);
		L[i]=L[i+1];
	}
	Copy_Massive(C[N-1],S,256);
	Copy_Massive(C[N],S,256);
	C[N-1][LL+1]=0+48;
	C[N][LL+1]=1+48;
	L[N-1]=LL+1;
	L[N]=LL+1;
}

void Huffman(Byte_Chance Array[], int L[],char C[][257],int N)
{
	if(N==2)
	{
		C[1][1]=48;
		L[1]=1;
		C[2][1]=49;
		L[2]=1;
	}
	else
	{
		double q=Array[N-1].Chance+Array[N].Chance;
		int j=Up(Array,N,q);
		Huffman(Array,L,C,N-1);
		Down(C,L,N,j);
	}
}

int Med(int l, int r, Byte_Chance Array[])
{
	double SL,SR;
	SL=0;
	for(int i=l;i<=r-1;i++)
	{
		SL+=Array[i].Chance;
	}
	SR=Array[r].Chance;
	int m=r;
	while(SL>=SR)
	{
		m--;
		SL-=Array[m].Chance;
		SR+=Array[m].Chance;
	}
	return m;
}

void Fano(int l, int r, int k, char C[][257], int L[], Byte_Chance Array[])
{
	if(l<r)
	{
		k++;
		int m=Med(l,r,Array);
		for(int i=l;i<=r;i++)
		{
			if(i<=m)
			{
				C[i][k]=48;
			}
			else
			{
				C[i][k]=49;
			}
			L[i]++;
		}
		Fano(l,m,k,C,L,Array);
		Fano(m+1,r,k,C,L,Array);
	}
}

int main()
{
	FILE *ft, *fcopy;
	Byte_Chance Array[257];
	int Byte_Repeat[257]={0};
	for(int i=1;i<=256;i++)
	{
		Array[i].Num=i-1;
	}
	ft=fopen("Date.dat","rb");
	if(ft == NULL)
	{
		ft=fopen("Date.dat","wb");
		fcopy=fopen("TextofSing.txt","r");
		unsigned char ch[1];
		while((ch[0]=fgetc(fcopy))!=EOF)
		{
			fwrite(ch,sizeof(char),1,ft);
		}
		fclose(fcopy);
		fclose(ft);
		ft=fopen("Date.dat","rb");
	}
	unsigned char ch[1];
	while(fread(ch,sizeof(char),1,ft))
	{
		Byte_Repeat[ch[0]]++;
		Num_of_Byte++;
	}
	fclose(ft);
	system("chcp 1251>null");
	int N=0;
	for(int i=1;i<=256;i++)
	{
		if(Byte_Repeat[i]) N++;
		Array[i].Chance=(double)Byte_Repeat[i]/Num_of_Byte;
		printf("%i: %-6.4f\n",i,Array[i].Chance);
	}
	HeapSort(Array,256);
	double Sum=0;
	for(int i=2;i<=N;i++)
	{
		Sum+=Array[i].Chance;
	}
	Array[1].Chance=(double)1-Sum;
	Sum+=Array[1].Chance;
	for(int i=1;i<=N;i++)
	{
		printf("%i %c: %-6.4f\n",i,Array[i].Num,Array[i].Chance);
	}
	printf("\n\n—уммарна€ веро€тность: %-4.5f\n\n",Sum);
	char C[257][257];
	int L[257];
	double Q[257];
	printf("\n\nЁнтропи€: %-4.5f\n\n",N_Tropy(Array,N));
	printf("Shannon\n");
	Shannon(Array,Q,L,C,N);
	for(int i=1;i<=N;i++)
	{
		printf("%-4.2f %s %-3i\n",Array[i].Chance,C[i]+1,L[i]);
	}
	printf("\n\n—редн€€ длина слова: %-4.5f\n\n",Average_Len(Array,L,N));
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=256;j++)
		{
			C[i][j]=0;
		}
		L[i]=0;
		Q[i]=0;
	}
	double P[257];
	for(int i=1;i<=256;i++)
	{
		P[i]=Array[i].Chance;
	}
	Huffman(Array,L,C,N);
	for(int i=1;i<=256;i++)
	{
		Array[i].Chance=P[i];
	}
	printf("Huffman\n");
	for(int i=1;i<=N;i++)
	{
		printf("%-4.2f %s %-3i\n",Array[i].Chance,C[i]+1,L[i]);
	}
	printf("\n\n—редн€€ длина слова: %-4.5f\n\n",Average_Len(Array,L,N));
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=256;j++)
		{
			C[i][j]=0;
		}
		L[i]=0;
	}
	printf("Fano\n");
	Fano(1,N,0,C,L,Array);
	for(int i=1;i<=N;i++)
	{
		printf("%-4.2f %s %-3i\n",Array[i].Chance,C[i]+1,L[i]);
	}
	printf("\n\n—редн€€ длина слова: %-4.5f\n\n",Average_Len(Array,L,N));
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=256;j++)
		{
			C[i][j]=0;
		}
		L[i]=0;
	}
	HeapSort2(Array,N);
	Gilbert_Mur(Array,Q,L,C,N);
	printf("Gilbert-Mur\n");
	for(int i=1;i<=N;i++)
	{
		printf("%-4.2f %s %-3i\n",Array[i].Chance,C[i]+1,L[i]);
	}
	printf("\n\n—редн€€ длина слова: %-4.5f\n\n",Average_Len(Array,L,N));
	for(int i=1;i<=N;i++)
	{
		for(int j=1;j<=256;j++)
		{
			C[i][j]=0;
		}
		L[i]=0;
		Q[i]=0;
	}
	return 0;
}
