#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>

using namespace std;

int C=0;

const int size=40;

void Hash_Null(int T[], int m)
{
	for(int i=0;i<m;i++)
	{
		T[i]=-1;
	}
}

void PrintHash(int T[], int m)
{
	printf("\nХеш-таблица:\n");
	for(int i=0;i<m;i++)
	{
		if(T[i]==-1) printf(" , ");
		else printf("%i, ",T[i]);
	}
}

void PrintColl(int flag, int m)
{
	printf("\nКол-во коллизий при ");
	if(flag) printf("линейных пробах\n");
	else printf("квадратичных пробах\n");
	printf("Размер хеш-таблицы: %i\n",m);
	printf("Кол-во входных данных: %i\n",size);
	printf("Кол-во коллизий: %i\n",C);
	C=0;
}

int Hash_Function(int m, int K)
{
	return K%m;
}

int Hash_Linean(int i)
{
	return i;
}

int Hash_Quadratic(int i)
{
	return i*i;
}

int Hash_Function(int m, int K, int g)
{
	return (Hash_Function(m,K)+g)%m;
}

int Hash_Insert(int T[], int K, int flag, int m)
{
	int C_loc=0;
	int (*g)(int);
	if(flag) g=Hash_Linean;
	else g=Hash_Quadratic;
	int i=0,j;
	do
	{
		j=Hash_Function(m,K,g(i));
		if(T[j]==-1) T[j]=K, C+=C_loc;
		if(T[j]==K) return 0;
		i++;
		C_loc++;
	}while(i!=m);
	printf("\nХеш-Таблица переполнена!\n");
	return 1;
}

int Hash_Search(int T[], int K, int flag, int m)
{
	int (*g)(int);
	if(flag) g=Hash_Linean;
	else g=Hash_Quadratic;
	int i=0,j;
	do
	{
		j=Hash_Function(m,K,g(i));
		if(T[j]==K) return j;
		i++;
		C++;
	}while(i!=m);
	printf("\nЭлемент не найден!\n");
	return -1;
}

int main()
{
	const int m=29;
	int box, num;
	system("chcp 1251>nul");
	int hash_table[m];
	int Example[size];
	printf("Полученный массив:\n");
	Hash_Null(hash_table,m);
	for(int i=0;i<size;i++)
	{
		Example[i]=rand()%100;
		printf("%i, ",Example[i]);
	}
	printf("\n");
	for(int i=0;i<size;i++)
	{
		if(Hash_Insert(hash_table, Example[i],0,m)) break;
	}
	PrintHash(hash_table,m);
	PrintColl(0,m);
	printf("\nВведите число, которое хотите найти?\n");
	scanf("%i",&num);
	box=Hash_Search(hash_table,num,0,m);
	if(box!=-1)
	{
		printf("\nЭлемент %i найден в %i ячейке",num,box);
	}
	Hash_Null(hash_table,m);
	for(int i=0;i<size;i++)
	{
		if(Hash_Insert(hash_table, Example[i],1,m)) break;
	}
	PrintHash(hash_table,m);
	PrintColl(1,m);
	printf("\nВведите число, которое хотите найти?\n");
	scanf("%i",&num);
	box=Hash_Search(hash_table,num,1,m);
	if(box!=-1)
	{
		printf("\nЭлемент %i найден в %i ячейке",num,box);
	}
	cout<<"\n m ="<<m<<"\n size/2*log2(size)= " << size/(2*log2(size));
	system("pause>nul");
	return 0;
}
