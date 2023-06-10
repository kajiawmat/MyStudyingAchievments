#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
/*
Шиян
B=2: 2-ая база данных
С=2: По др и ФИО (Ключ = др)
S=3: Merge
D=1: АВЛ-дерево
E=3: Код Фано
*/

int N=4000;
using namespace std;
bool rost = 1; // За физ увеличение дерева по высоте
int kolpov = 0;
bool decrease = 1;
struct record
{
	char a[30];
	short int b;
	char c[22];
	char d[10];
};
struct Vertex {
  record *Data;
  int bal;
  Vertex *Left;
  Vertex *Right;
  Vertex *Same;
};
Vertex *Root;
struct Queue
{
	Queue *next;
	record Data;
};

int Less_Equal(record x, record y)
{
	if(strncmp(x.d,y.d,2)<0) return 1;
	if(strncmp(x.d,y.d,2)>0) return 0;
	if(strcmp(x.a,y.a)<=0) return 1;
	return 0;
}

int Less_B(record* x, record* y)
{
	if(x->b<y->b) return 1;
	return 0;
}
// S - разбиваемый список, a - четные элементы списка, b - нечетные элементы списка, N - макс размер списка
// Сплит разбивает список
void Split_Stack(struct Queue *&S, struct Queue *&a, struct Queue *&b, int &N)
{
	struct Queue *p, *k;
	a=S;
	b=S->next;
	k=a;
	p=b;
	N=1;
	while(p!=NULL)
	{
		N++;
		k->next=p->next;
		k=p;
		p=p->next;
	}
}

// q - кол-во элементов списка а, r - кол-во элементов списка b, с - список полученный путем сливания двух списков a и b, tail - хвост с, чтобы определить где конец, он помогает последнему элементу присвоить указатель на следующий нулевой  
// Merge - соединяет разбитый список
void Merge(struct Queue *&a, int q, struct Queue *&b, int r, struct Queue *&c, struct Queue *&tail)
{
	while(q!=0 && r!=0)
	{
		if(Less_Equal(a->Data,b->Data)) 
		{
			tail->next=a;
			tail=a;
			a=a->next;
			q--;
		}
		else
		{
			tail->next=b;
			tail=b;
			b=b->next;
			r--;
		}
	}
	while(q>0)
	{
		tail->next=a;
		tail=a;
		a=a->next;
		q--;
	}
	while(r>0)
	{
		tail->next=b;
		tail=b;
		b=b->next;
		r--;
	}
	tail->next=NULL;
}

// MergeSort сортирует полученный список из предыдущей функции Merge
void MergeSort(struct Queue *&S)
{
	struct Queue *a,*b,*c[2],*tail_c[2];
	int N, i;
	a=NULL;
	b=NULL;
	Split_Stack(S,a,b,N);
	int p=1,q,r,m;
	while(p<N)
	{
		c[0]=NULL;
		c[1]=NULL;
		tail_c[0]=(Queue*)&(c[0]);
		tail_c[1]=(Queue*)&(c[1]);
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
			Merge(a,q,b,r,c[i],tail_c[i]);
			i=1-i;
		}
		a=c[0];
		b=c[1];
		p*=2;
	}
	S=c[0];
	
}

void PrintDataBase(Queue *head)
{
	Queue *p=head;
	int k=0,flag;
	while(k<N-1)
	{
		for(int i=0;i<20;i++)
		{
			printf(" %-6i  %s  %3i  %s  %s\n",k+1,p->Data.a,p->Data.b,p->Data.c,p->Data.d);
			k++;
			p=p->next;
		}
		printf("\n Print next 20 ? 1 or 0\n");
		scanf("%i",&flag);
		printf("\n");
		if(flag==0) break;
	}
	system("Pause");
}

void SortDataBase(Queue *&head, Queue **&Index)
{
	MergeSort(head);
	Queue *p=head;
	for(int i=0;i<4000;i++)
	{
		Index[i]=p;
		p=p->next;
	}
}

void PrintSortDataBase(Queue **Index)
{
	int k=0,flag;
	while(k<N-1)
	{
		for (int i=0;i<20;i++)
		{
			printf(" %-6i  %s  %3i  %s  %s\n",k+1,Index[k]->Data.a,Index[k]->Data.b,Index[k]->Data.c,Index[k]->Data.d);
			k++;
		}
		printf("\n Print next 20 ? 1 or 0\n");
		scanf("%i",&flag);
		printf("\n");
		if(flag==0) break;
	}
	system("Pause");
}

void FillQueue(Queue *&head,Queue *tail,FILE* fp)
{
	struct record rec;
	struct Queue *p;
	p=new Queue;
	fread(&(p->Data),sizeof(record),1,fp);
	p->next=NULL;
	head=p;
	tail=p;
	for(int i=1;i<N;i++)
	{
		p=new Queue;
		fread(&(p->Data),sizeof(record),1,fp);
		tail->next=p;
		tail=p;
	}
	tail->next=NULL;
}

int BSearch2(Queue **Index, char x[])
{
	int L,R,m,C;
	L=0;R=4000-1;
	while(L<R)
	{
	    m=(L+R)/2;
		if (strncmp(Index[m]->Data.d,x,2)<0)
		{
			L=m+1;	
		}
		else 
		{
			R=m; 
		} 	    	
	}
	if(strncmp(Index[R]->Data.d,x,2)==0)
	{
		return R;	
	}
    return -1;
 } 
 
 Queue* BSearch2All(Queue **Index)
 {
 	char x[2];
 	printf("Enter date of birth:\n");
 	scanf("%s",x);
 	int i=BSearch2(Index,x);
 	int k=0;
 	Queue *Head_Search=NULL,*Tail=NULL;
 	Queue *p=new Queue;
 	p->Data=Index[i]->Data;
 	Head_Search=p;
 	Tail=p;
 	printf(" %-6i  %s  %3i  %s  %s\n",k+1,Index[i]->Data.a,Index[i]->Data.b,Index[i]->Data.c,Index[i]->Data.d);
 	k++;
 	i++;
 	if (i==-1)
 	{
 		printf("There is no person with this date of birth in the database!!!");
 	}
 	else
 	{
 		while(i<4000 && strncmp(Index[i]->Data.d,x,2)==0)
 		{
 			printf(" %-6i  %s  %3i  %s  %s\n",k+1,Index[i]->Data.a,Index[i]->Data.b,Index[i]->Data.c,Index[i]->Data.d);
 			p=new Queue;
			p->Data=Index[i]->Data;
 			Tail->next=p;
 			Tail=p;
			k++;
			i++;
 		}
 	}
 	system("Pause");
 	return Head_Search;
}

void Obh1(Vertex *p) {
  if (p != NULL) {

    Obh1(p->Left);
    printf("  %s  %3i  %s  %s \n", p->Data->a, p->Data->b, p->Data->c, p->Data->d);
    Obh1(p->Same);
    Obh1(p->Right);
  }
}

void LL(Vertex*& p) {
    Vertex* q = p->Left;
    p->bal = 0;
    q->bal = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR(Vertex*& p) {
    Vertex* q = p->Right;
    p->bal = 0;
    q->bal = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void LR(Vertex*& p) {
    Vertex* q = p->Left;
    Vertex* r = q->Right;
    if (r->bal < 0)
        p->bal = 1;
    else
        p->bal = 0;
    if
        (r->bal > 0) q->bal = -1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}

void RL(Vertex*& p) {
    Vertex* q = p->Right;
    Vertex* r = q->Left;
    if (r->bal > 0)
        p->bal = -1;
    else
        p->bal = 0;
    if (r->bal < 0)
        q->bal = 1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Right = q;
    r->Left = p;
    p = r;
}

void Add_ABL(record *Data, Vertex* &p) {
    if (p == NULL) {
        p = new Vertex;
        p->Data = Data;
        p->Left = NULL;
        p->Right = NULL;
        p->Same=NULL;
        p->bal = 0;
        rost = 1;
    }
    else if (Less_B(Data, p->Data)) {
        Add_ABL(Data, p->Left);
        if (rost == 1) {
            if (p->bal > 0) {
                p->bal = 0;
                rost = 0;
            }
            else if (p->bal == 0) {
                p->bal = -1;
            }
            else {
                if (p->Left->bal < 0) {
                    //cout << "LL" << endl;
                    LL(p);
                    rost = 0;
                }
                else {
                    //cout << "LR" << endl;
                    LR(p);
                    rost = 0;
                }
            }
        }
    }
    else if (Less_B(p->Data,Data)) {
        Add_ABL(Data, p->Right);
        if (rost == 1) {
            if (p->bal < 0) {
                p->bal = 0;
                rost = 0;
            }
            else if (p->bal == 0) {
                p->bal = 1;
            }
            else {
                if (p->Right->bal > 0) {
                    RR(p);
                    rost = 0;
                }
                else {
                    RL(p);
                    rost = 0;
                }
            }
        }
    }
    else
    {
    	Add_ABL(Data, p->Same);
    	rost=0;
    }
}

Vertex *TreeSearch(Vertex *Root, record *Data) {
  struct Vertex *box = Root;
  while (box != NULL) {
    if (box->Data > Data)
      box = box->Left;
    else if (box->Data < Data)
      box = box->Right;
    else
      break;
  }
  if (box != NULL) {
    //cout << "Вершина найдена" << endl;
    return box;
  } else {
    //cout << "Вершина не найдена" << endl;
    return 0;
  }
}


int main() {
	FILE *fp;
	fp=fopen("testBase2.dat","rb");
	Queue *head,*tail;
	FillQueue(head,tail,fp);
	fclose(fp);
	Queue **Index = new Queue*[4000];
	Queue *Head_Search=NULL;
	Vertex* Root;
	int Size;
	int flag;
	do{
		system("CLS");
		printf("0) Exit\n");
		printf("1) DataBase\n");
		printf("2) SortDataBase\n");
		printf("3) BSearch2All\n");
		printf("4) Tree\n");
		scanf("%i",&flag);
		system("CLS");
		switch(flag)
		{
			case 1:
				PrintDataBase(head);
				break;
			case 2:
				SortDataBase(head,Index);
				PrintSortDataBase(Index);
				break;
			case 3:
				Head_Search=BSearch2All(Index);
				break;
			case 4:
				Root = NULL;
    			for (Queue *p=Head_Search; p!=NULL; p=p->next) {
        			Add_ABL(&(p->Data), Root);
    			}
    			Obh1(Root);
        		system("Pause");
		}
	}while(flag);
	return 0;
}
