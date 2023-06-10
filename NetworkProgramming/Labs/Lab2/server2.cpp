#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<wait.h>
#include<signal.h>

#define BUFFER_SIZE 1024

using namespace std;

struct Data_Socket
{
	int sock;
	struct sockaddr_in clientAddr;
};

void ZombieHandler(int s)
{
	int sig;
	while(wait3(&sig,WNOHANG,(struct rusage*)0)>=0);
}

void* SocketConnection(void* _data)
{
	struct sockaddr_in clientAddr;
	struct Data_Socket data=*((struct Data_Socket*) _data);
	clientAddr=data.clientAddr;
	int sockClient=data.sock;
	int msgLength;
	char message[BUFFER_SIZE];
	while(1)
	{
		bzero(message,sizeof(BUFFER_SIZE));
		msgLength=recv(sockClient,message,BUFFER_SIZE,0);
		if(msgLength<0)
		{
			printf("recvfrom() error");
			exit(1);
		}
		else if(msgLength==0)
		{
			cout<<endl<<"Порт "<<ntohs(clientAddr.sin_port)<<" закрыт!"<<endl<<endl;
			close(sockClient);
			break;
		}
		cout<<"Процесс выполнения "<<getpid()<<endl;
		cout<<"IP адрес клиента: "<<inet_ntoa(clientAddr.sin_addr)<<endl;
		cout<<"PORT адрес клиента: "<<ntohs(clientAddr.sin_port)<<endl;
		cout<<message<<endl;
		message[1]='+';
		if(send(sockClient,message,BUFFER_SIZE,0)<0)
		{
			printf("sendto() error");
			exit(1);
		}	
	}
}

int main()
{
	signal(SIGCHLD,ZombieHandler);
	pid_t child_pid=0;
	int sockTCP,sockClient;
	unsigned int Length;
	struct sockaddr_in serverAddr, clientAddr;
	struct Data_Socket data;
	char message[BUFFER_SIZE];
	sockTCP=socket(AF_INET, SOCK_STREAM, 0);
	if(sockTCP<0)
	{
		printf("Open UDPsocket error");
		exit(1);
	}
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddr.sin_port=0;
	if(bind(sockTCP,(sockaddr*) &serverAddr,sizeof(serverAddr)))
	{
		printf("Bind error");
		exit(1);
	}
	Length=sizeof(serverAddr);
	if(getsockname(sockTCP,(sockaddr*) &serverAddr,&Length))
	{
		printf("getsockname() error");
		exit(1);
	}
	listen(sockTCP,5);
	cout<<"PORT адрес сервера:"<<ntohs(serverAddr.sin_port)<<endl;
	cout<<"IP адрес сервера:"<<inet_ntoa(serverAddr.sin_addr)<<endl;
	while(1)
	{
		Length=sizeof(clientAddr);
		if((data.sock=accept(sockTCP,(sockaddr*) &clientAddr,&Length))<0)
		{
			printf("accept() error");
			exit(1);
		}
		data.clientAddr=clientAddr;
		child_pid=fork();
		if(child_pid!=0)
		{
			SocketConnection((void*) &data);
			return 0;
		}
	}
	close(sockTCP);
	return 0;
}
