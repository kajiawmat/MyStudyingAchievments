#include<stdlib.h>
#include<stdio.h>

int first=0;
int second=0;

void Fill_Inc(int Array[], int N)
{
	for(int i=1;i<=N;i++)
	{
		Array[i]=i;
	}
}

void Double_Int(int X, int &size, int len)
{
	if(len!=0)
	{
		Double_Int(X/2,size,len-1);
		printf("%i",X%2);
		size++;
	}
}

void Degree(int X, int &size)
{
	size+=4;
	int deg=8;
	for(int i=0;i<4;i++)
	{
		if(X>=deg)
		{
			printf("1");
			X-=deg;
		}
		else printf("0");
		deg/=2;
	}
	printf(" ");
}

void Fixed_Variable(int X,int &size)
{
	printf("%-4i",X);
	int len=1,flag=0,X_res=0,deg=1;
	for(int i=0;i<16;i++)
	{
		deg*=2;
	}
	while(deg)
	{
		if(flag) len++;
		if(X>=deg)
		{
			X-=deg;
			if(flag==0)
			{ 
				X_res=X;
				flag=1;
			}
		}
		deg/=2;
	}
	Degree(len,size);
	Double_Int(X_res,size,len-1);
	second+=size;
}

void Ellias_Gamma(int X,int &size)
{
	printf("%-4i",X);
	int len=1,flag=0,X_res=0,deg=1;
	for(int i=0;i<16;i++)
	{
		deg*=2;
	}
	while(deg)
	{
		if(flag) len++;
		if(X>=deg)
		{
			if(flag==0)
			{ 
				X_res=X;
				flag=1;
			}
			X-=deg;
		}
		deg/=2;
	}
	for(int i=1;i<len;i++)
	{
		printf("0");
	}
	printf(" ");
	Double_Int(X_res,size,len);
	second+=size;
}

void Print_Table(int Array[], int N, int mode)
{
	void (*func)(int X,int &size);
	int size;
	switch(mode)
	{
		case 1:
			func=Fixed_Variable;
		case 2:
			func=Ellias_Gamma;
	}
	for(int i=1;i<=N;i++)
	{
		size=0;
		func(Array[i],size);
		printf("(%i)\n",size);
		first+=8*sizeof(Array[i]);
	}
	printf("\nКол-во изначально символов: %i",first);
	printf("\nКол-во закодированных символов: %i",second);
	printf("\n\n");
	first=0;
	second=0;
}

int main()
{
	const int N=32;
	int Array[N+1];
	Fill_Inc(Array,N);
	Print_Table(Array,N,1);
	Print_Table(Array,N,2);
	second=0;
	return 0;
}
