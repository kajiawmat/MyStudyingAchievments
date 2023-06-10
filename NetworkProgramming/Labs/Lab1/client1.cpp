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

using namespace std;

#define BUFFER_SIZE 1024
#define COUNT 24

int main(int argc, char* argv[])
{
	int sockUDP;
	int Number;
	unsigned int Length;
	struct sockaddr_in serverAddr, clientAddr;
	struct hostent *hp;
	char message[BUFFER_SIZE];
	if(argc<4)
	{
		printf("Too few arguments");
		exit(1);
	}
	sockUDP=socket(AF_INET, SOCK_DGRAM, 0);
	if(sockUDP<0)
	{
		printf("Open UDPsocket error");
		exit(1);
	}
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr, &serverAddr.sin_addr,hp->h_length);
	serverAddr.sin_port=htons(atoi(argv[2]));
	bzero((char*) &clientAddr, sizeof(clientAddr));
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	clientAddr.sin_port=0;
	if(bind(sockUDP,(sockaddr*) &clientAddr,sizeof(clientAddr)))
	{
		printf("Bind error");
		exit(1);
	}
	Number=atoi(argv[3]);
	for(int i=0;i<COUNT;i++)
	{
		sleep(Number);
		if(sendto(sockUDP,argv[3],strlen(argv[3]),0,(sockaddr*) &serverAddr,sizeof(serverAddr))<0)
		{
			printf("sendto() error");
			exit(1);
		}
		bzero(message,sizeof(BUFFER_SIZE));
		Length=sizeof(serverAddr);
		if(recvfrom(sockUDP,message,BUFFER_SIZE,0,(sockaddr*) &serverAddr,&Length)<0)
		{
			printf("recvfrom() error");
			exit(1);
		}	
		//cout<<"IP адрес клиента: "<<inet_ntoa(serverAddr.sin_addr)<<endl;
		//cout<<"PORT адрес клиента: "<<ntohs(serverAddr.sin_port)<<endl;
		cout<<message<<endl;
	}
	printf("Ok end.\n");
	close(sockUDP);
	return 0;
}
