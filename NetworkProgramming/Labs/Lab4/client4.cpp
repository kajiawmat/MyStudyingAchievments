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
	int sockTCP;
	int Number;
	unsigned int Length;
	struct sockaddr_in serverAddr;
	struct hostent *hp;
	char message[BUFFER_SIZE];
	if(argc<4)
	{
		printf("Too few arguments");
		exit(1);
	}
	sockTCP=socket(AF_INET, SOCK_STREAM, 0);
	if(sockTCP<0)
	{
		printf("Open UDPsocket error");
		exit(1);
	}
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr, &serverAddr.sin_addr,hp->h_length);
	serverAddr.sin_port=htons(atoi(argv[2]));
	if(connect(sockTCP,(sockaddr*)&serverAddr,sizeof(serverAddr))<0)
	{
		printf("Connect Error");
		exit(1);
	}
	Number=atoi(argv[3]);
	for(int i=0;i<COUNT;i++)
	{
		sleep(Number);
		if(send(sockTCP,argv[3],strlen(argv[3]),0)<0)
		{
			printf("sendto() error");
			exit(1);
		}
		bzero(message,sizeof(BUFFER_SIZE));
		Length=sizeof(serverAddr);
		if(recv(sockTCP,message,BUFFER_SIZE,0)<0)
		{
			printf("recvfrom() error");
			exit(1);
		}	
		cout<<message<<endl;
	}
	printf("Ok end.\n");
	close(sockTCP);
	return 0;
}
