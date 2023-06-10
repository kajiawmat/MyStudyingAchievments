#include "data.h"
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
#include<pthread.h>

using namespace std;

char hostname[BUFFER_SIZE];
char filename[BUFFER_SIZE];
int sockCommand;
int sockData=-1;
int tempSockData=-1;
bool requestPORT=true;
bool localPORT=false;

void* RecvFile(void* file)
{
	char data[BUFFER_SIZE];
	if(localPORT)
	{
		int len;
		FILE* fp=fopen(filename,"w");
		char txt[BUFFER_SIZE];
		while(true)
		{
			bzero(data,BUFFER_SIZE);
			len=recv(sockData,data,BUFFER_SIZE,0);
			if(len==0) break;
			strncpy(txt,data,len);
			fprintf(fp,"%s",txt);
		}
		fclose(fp);
		close(sockData);
	}
	sockData=-1;
	bzero(data,BUFFER_SIZE);
	recv(sockCommand,data,BUFFER_SIZE,0);
	cout<<data;
	return NULL;
}

void* SendFile(void* file)
{
	char data[BUFFER_SIZE];
	if(localPORT)
	{
		FILE* fp=fopen(filename,"r");
		while(true)
		{
			bzero(data,BUFFER_SIZE);
			if(fgets(data,BUFFER_SIZE,fp)==NULL) break;
			if(send(sockData,data,strlen(data),0)<=0) break;
			
		}
		fclose(fp);
		close(sockData);
	}
	sockData=-1;
	bzero(data,BUFFER_SIZE);
	recv(sockCommand,data,BUFFER_SIZE,0);
	cout<<data;
	return NULL;
}

void* RecvList(void* unused)
{
	int len;
	char response[BUFFER_SIZE];
	if(localPORT)
	{
		while(true)
		{
			bzero(response,BUFFER_SIZE);
			len=recv(sockData,response,BUFFER_SIZE,0);
			if(len==0) break;
			cout<<response;
		}
		close(sockData);
	}
	sockData=-1;
	bzero(response,BUFFER_SIZE);
	len=recv(sockCommand,response,BUFFER_SIZE,0);
	cout<<response;
	return NULL;
}

void* ListenSock(void* unused)
{
	struct sockaddr_in clientAddr;
	unsigned int Length=sizeof(clientAddr);
	int passSock=tempSockData;
	tempSockData=accept(passSock,(sockaddr*) &clientAddr,&Length);
	close(passSock);
	return NULL;
}

int ResponseActions(char message[], char response[])
{
	int len;
	pthread_t pth;
	char *typeCommand;
	char *name;
	char *savePtr1;
	char *savePtr2;
	typeCommand=strtok_r(message," ",&savePtr1);
	if(strncmp(typeCommand,"HELP",4)==0) 
	{
		bzero(response,BUFFER_SIZE);
		len=recv(sockCommand,response,BUFFER_SIZE,0);
		cout<<response;
		if(strncmp(strtok_r(response," ",&savePtr2),"451",3)==0) return len;
		bzero(response,BUFFER_SIZE);
		len=recv(sockCommand,response,BUFFER_SIZE,0);
		cout<<response;
		return len;
	}
	if(strncmp(typeCommand,"PORT",4)==0)
	{
		len=recv(sockCommand,response,BUFFER_SIZE,0);
		cout<<response;
		if(strncmp(strtok_r(response," ",&savePtr2),"200",3)!=0) requestPORT=false;
		else sockData=tempSockData;
		return len;
	}
	name=strtok_r(NULL," \n",&savePtr1);
	len=recv(sockCommand,response,BUFFER_SIZE,0);
	cout<<response;
	if(((strncmp(typeCommand,"LIST",4)==0) || (strncmp(typeCommand,"NLST",4)==0)) && (strncmp(response,"150",3)==0))
	{
		pthread_create(&pth,NULL,RecvList,NULL);
		pthread_detach(pth);
	}
	if((strncmp(typeCommand,"STOR",4)==0) && (strncmp(response,"150",3)==0)) 
	{
		bzero(filename,BUFFER_SIZE);
		strcpy(filename,name);
		pthread_create(&pth,NULL,SendFile,NULL);
		pthread_detach(pth);
	}
	if((strncmp(typeCommand,"RETR",4)==0) && (strncmp(response,"150",3)==0))
	{
		bzero(filename,BUFFER_SIZE);
		strcpy(filename,name);
		pthread_create(&pth,NULL,RecvFile,NULL);
		pthread_detach(pth);
	}
	if(strncmp(typeCommand,"QUIT",4)==0) return 0;
	return len;
}

int main(int argc, char* argv[])
{
	int msgLength;
	pthread_t pth;
	struct sockaddr_in serverAddr,clientAddr;
	struct hostent *hp;
	unsigned int Length;
	char IPData[20];
	int portData;
	char message[BUFFER_SIZE];
	char response[BUFFER_SIZE];
	if(argc<3)
	{
		printf("Too few arguments");
		exit(1);
	}
	system("hostname > Host.txt");
	FILE* fp=fopen("Host.txt","r");
	fscanf(fp,"%s",hostname);
	fclose(fp);
	system("rm Host.txt");
	sockCommand=socket(AF_INET, SOCK_STREAM, 0);
	if(sockCommand<0)
	{
		printf("Open UDPsocket error");
		exit(1);
	}
	
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	hp=gethostbyname(argv[1]);
	bcopy(hp->h_addr, &serverAddr.sin_addr,hp->h_length);
	serverAddr.sin_port=htons(atoi(argv[2]));
	if(connect(sockCommand,(sockaddr*)&serverAddr,sizeof(serverAddr))<0)
	{
		printf("Connect Error");
		exit(1);
	}
	bzero(response,BUFFER_SIZE);
	recv(sockCommand,response,BUFFER_SIZE,0);
	cout<<response;
	while(true)
	{
		bzero(message,BUFFER_SIZE);
		bzero(response,BUFFER_SIZE);
		fgets(message,BUFFER_SIZE,stdin);
		if(strncmp(message,"PORTMY",6)==0)
		{
			tempSockData=socket(AF_INET, SOCK_STREAM, 0);
			bzero((char*) &clientAddr, sizeof(serverAddr));
			clientAddr.sin_family=AF_INET;
			hp=gethostbyname(hostname);
			bcopy(hp->h_addr, &clientAddr.sin_addr,hp->h_length);
			clientAddr.sin_port=0;
			if(bind(tempSockData,(sockaddr*) &clientAddr,sizeof(clientAddr)))
			{
				printf("Bind error\n");
				break;
			}
			Length=sizeof(clientAddr);
			if(getsockname(tempSockData,(sockaddr*) &clientAddr,&Length))
			{
				printf("getsockname() error");
				exit(1);
			}
			snprintf(IPData,20,"%s",inet_ntoa(serverAddr.sin_addr));
			for(int i=0;i<20;i++) if(IPData[i]=='.') IPData[i]=',';
			portData=ntohs(clientAddr.sin_port);
			snprintf(message,BUFFER_SIZE,"PORT %s,%i,%i",IPData,portData/256,portData%256);
			cout<<message<<endl;
			listen(tempSockData,2);
			pthread_create(&pth,NULL,&ListenSock,NULL);
			localPORT=true;
		}
		else if(strncmp(message,"PORT",4)==0) localPORT=false;
		strcat(message," \n");
		if(send(sockCommand,message,strlen(message),0)<0)
		{
			printf("send() error");
			exit(1);
		}
		msgLength=ResponseActions(message,response);
		if(msgLength==0)
		{
			printf("Client closed\n");
			close(sockCommand);
			break;
		}
		if(!requestPORT) 
		{
			pthread_cancel(pth);
			requestPORT=true;
		}
	}
	close(sockCommand);
	return 0;
	
}
