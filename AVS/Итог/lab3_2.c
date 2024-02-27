#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>
#include<wait.h>


void ITOA(char A[], int n)
{
	int temp=1,i;
	char ch[2];
	for(i=0;temp<=n;i++,temp*=10);
	temp/=10;
	for(;i>0;i--)
	{
		ch[0]=(char)(n/temp+'0');
		A=strncat(A,ch,1);
		n%=temp;
		temp/=10;
	}
}

int main()
{
	int h,w;
	//Флаг, для определения прародителя
	int flag_parent=1;
	pid_t *child_pids, parent_pid;
	printf("Введите высоту дерева процессов:\n");
	scanf("%i",&h);
	printf("Введите ширину дерева:\n");
	scanf("%i",&w);
	child_pids=(int *) calloc(w,sizeof(int));
	for(int i=0;i<w;i++) child_pids[i]=0;
	for(int j=1;j<h;j++)
	{
		//Присваиваю переменной id текущего процесса (буд. род.)
		parent_pid=(int)getpid();
		//Цикл для создания дочерних в родительском процессе
		for(int i=0;i<w;i++)
		{
			//Порождение дочернего процесса
			child_pids[i]=fork();
			//Если это миниродитель, то пусть перейдёт на следующую высоту (итерацию по i) и будет порождать минидетей
			//В самом условии флаг обнуляем (то есть не прародитель), обнуляем для миниродителя переменные
			if(child_pids[i]==0)
			{
				parent_pid=0;
				for(int k=0;k<w;k++) child_pids[k]=0;
				flag_parent=0;
				break;
			}
		}
		//Если это родитель на этой высоте, то создавать миниродителей для других высот не надо
		if(parent_pid!=0) break;
	}
	//Для всех родителей после создания дерева выписать их id и всех непосредственных детей
	if(parent_pid!=0)
	{
		printf("%i -> ",parent_pid);
		for(int i=0;i<w;i++) printf(" %i",child_pids[i]);
		printf("\n");	
	}
	//Для прародителя вывести команду, которая выведет дерево по его id
	if(flag_parent==1) 
	{
		sleep(1);
		char pid[100]="pstree ";
		ITOA(pid,parent_pid);
		system(pid);
	}
	sleep(180);
	return 0;
}
