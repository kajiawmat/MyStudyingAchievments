#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>

#define BUFFER_SIZE 1024

using namespace std;

int main()
{
	fd_set rds,ads;
	int sockTCP,sockClient;
	unsigned int Length,N;
	struct sockaddr_in serverAddr, clientAddr;
	char message[BUFFER_SIZE];
	int msgLength;
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
	N=getdtablesize();
	FD_ZERO(&ads);
	FD_SET(sockTCP,&ads);
	while(1)
	{
		memcpy(&rds,&ads,sizeof(rds));
		if(select(N,&rds,(fd_set*)0,(fd_set*)0,(struct timeval*)0)<0)
		{
			printf("select error");
			exit(1);
		}
		if(FD_ISSET(sockTCP,&rds))
		{
			if((sockClient=accept(sockTCP,(sockaddr*) &clientAddr,&Length))<0)
			{
				printf("accept() error");
				exit(1);
			}
			FD_SET(sockClient,&ads);
		}
		for(int i=0;i<N;i++) if(i!=sockTCP && FD_ISSET(i,&rds))
		{
			bzero(message,sizeof(BUFFER_SIZE));
			msgLength=recv(i,message,BUFFER_SIZE,0);
			if(msgLength<0)
			{
				printf("recvfrom() error");
				exit(1);
			}
			else if(msgLength==0)
			{
				cout<<endl<<"Порт "<<ntohs(clientAddr.sin_port)<<" закрыт!"<<endl<<endl;
				close(i);
				FD_CLR(i,&ads);
				break;
			}
			cout<<message<<" (IP:"<<inet_ntoa(clientAddr.sin_addr)<<", PORT:"<<ntohs(clientAddr.sin_port)<<")"<<endl;
			message[1]=message[0]-'1'+'a';
			if(send(i,message,BUFFER_SIZE,0)<0)
			{
				printf("sendto() error");
				exit(1);
			}
		}	
	}
	close(sockTCP);
	return 0;
}
