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

//Вернуть информацию о потоке
void get_info()
{
	char func[100]="ps -e | grep ";
	ITOA(func,(int)getpid());
	system(func);
}

//Убить процесс с введённым id (передаюм знач. дочернего процесса) 
void kill_child(int n)
{
	char func[100]="kill ";
	ITOA(func,n);
	system(func);
}

int main()
{
	//объявление переменных в которых будут храниться id род. и доч. процесса
	pid_t child_pid, parent_pid;
	int i=0;
	//Переменная, которую мы будем использовать, чтобы ждать завершения дочернего процесса
	//В переменную будет запись какое-то число по состоянию завершения (это нас не интересует) 
	int child_status;
	char func[20];
	fprintf(stdout, "\E[H\E[2J");
	//Присваиваем текущего id процесса (будущего родительского)
	parent_pid=(int)getpid();
	fprintf(stdout, "PID_parent is %i\n",parent_pid);
	//Создание доернего процесса 
	//В род. процесса переменной будет присвоен id доч. процесса, а в доч. - не будет присвоен
	child_pid=fork();
	fprintf(stdout, "PID_children is %i\n",child_pid);
	//Узнаём инфу о процессах после создания дочернего
	get_info();
	if(child_pid!=0) 
	{
		//Убиваем дитя (КТО ТРОНУЛ ДИТЯЯЯЯ!!!???)
		kill_child(child_pid);
		//Ожидаем пока процесс нормально завершится
		//Под нормально я имею ввиду, чтобы не посреди выполнения команды, а не программы в целом
		wait(&child_status);
		printf("child deleted!\n");
	}
	get_info();
	return 0;
}
