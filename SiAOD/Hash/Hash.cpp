#include<stdio.h>
#include<stdlib.h>

int Golden_Ratio(int n)
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

/*
int Hash_Function(int m, int K)
{
	return K%m;
}
*/

int Hash_Function(int m, int K)
{
	return m*(int)(A*K);
}

/*

*/

int Function_Linear(int i)
{
	return i;
}

int Function_Quadratic(int i)
{
	return i*i;
}

/*int Hash_Function(int m, int K, int i)
{
	int h=Hash_Function(m,K);
	int d=1;
	while(1)
	{
		if()
	}
}*/

int Hash_Function(int m, int K, int i)
{
	return (Hash_Function(m,K)+Function_Quadratic(i))%m;
}

int Hash_Insert(int T[], int m, int K)
{
	int i=0,j;
	while(i!=m)
	{
		j=Hash_Function(m,K,i);
		if(T[j]==0)
		{
			T[j]=K;
			return j;
		}
		i++;
	}
	printf("\nПроизошло переполнение хеш-таблицы");
	exit(1);
}

int Hash_Search(int T[], int m, int K)
{
	int i=0,j;
	while(T[j]==0)
	{
		j=Hash_Function(m,K,i);
		if(T[j]==K)
		{
			return j;
		}
		i++;
	}
	printf("Элемент в хеш-таблице не найден");
	return -1;
}

int main()
{
	system("chcp 1251>nul");
	return 0;
}
