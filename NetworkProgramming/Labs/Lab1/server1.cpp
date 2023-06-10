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

#define BUFFER_SIZE 1024

using namespace std;

int main()
{
	int sockUDP, msgLength;
	unsigned int Length;
	struct sockaddr_in serverAddr, clientAddr;
	char message[BUFFER_SIZE];
	sockUDP=socket(AF_INET, SOCK_DGRAM, 0);
	if(sockUDP<0)
	{
		printf("Open UDPsocket error");
		exit(1);
	}
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddr.sin_port=0;
	if(bind(sockUDP,(sockaddr*) &serverAddr,sizeof(serverAddr)))
	{
		printf("Bind error");
		exit(1);
	}
	Length=sizeof(serverAddr);
	if(getsockname(sockUDP,(sockaddr*) &serverAddr,&Length))
	{
		printf("getsockname() error");
		exit(1);
	}
	cout<<"PORT адрес сервера:"<<ntohs(serverAddr.sin_port)<<endl;
	cout<<"IP адрес сервера:"<<inet_ntoa(serverAddr.sin_addr)<<endl;
	while(1)
	{
		Length=sizeof(clientAddr);
		bzero(message,sizeof(BUFFER_SIZE));
		msgLength=recvfrom(sockUDP,message,BUFFER_SIZE,0,(sockaddr*) &clientAddr,&Length);
		if(msgLength<0)
		{
			printf("recvfrom() error");
			exit(1);
		}
		cout<<message<<endl;
		cout<<"IP адрес клиента: "<<inet_ntoa(clientAddr.sin_addr)<<endl;
		cout<<"PORT адрес клиента: "<<ntohs(clientAddr.sin_port)<<endl;
		message[1]='+';
		if(sendto(sockUDP,message,BUFFER_SIZE,0,(sockaddr*) &clientAddr,Length)<0)
		{
			printf("sendto() error");
			exit(1);
		}
	}
	return 0;
}
