#include "serverCommand.h"

struct FTP_info *ftpA;
char* path;

using namespace std;

int main(int argc, char* argv[])
{
	if(argc<2) 
	{
		printf("Too few arguments");
		exit(1);
	}
	fd_set rds,ads;
	int ind=-1;
	int MainsockFTP;
	struct sockaddr_in serverAddr, clientAddr;
	unsigned int Length,N;
	char message[BUFFER_SIZE];
	int msgLength;
	
	int Size=atoi(argv[1]);
	char com[BUFFER_SIZE];
	snprintf(com,BUFFER_SIZE,"./scripts/Existsdir.sh %i . .",Size);
	system(com);
	snprintf(com,BUFFER_SIZE,"temp/%i.txt",Size);
	FILE *fp=fopen(com,"r");
	ReadFilePath(fp,path);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",Size);
	system(com);
	
	ftpA=new struct FTP_info[Size];
	for(int i=0;i<Size;i++)
	{
		ftpA[i].ID=i;
		ZeroFTP(ftpA[i]);
		snprintf(ftpA[i].buffPath,BUFFER_SIZE,"temp/%i.txt",ftpA[i].ID);
		strcpy(ftpA[i].currentPath,path);
	}
	
	MainsockFTP=socket(AF_INET, SOCK_STREAM, 0);
	bzero((char*) &serverAddr, sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serverAddr.sin_port=0;
	if(bind(MainsockFTP,(sockaddr*) &serverAddr,sizeof(serverAddr)))
	{
		printf("Bind error");
		exit(1);
	}
	Length=sizeof(serverAddr);
	if(getsockname(MainsockFTP,(sockaddr*) &serverAddr,&Length))
	{
		printf("getsockname() error");
		exit(1);
	}
	listen(MainsockFTP,5);
	cout<<"Номер порта сервера: "<<ntohs(serverAddr.sin_port)<<endl;
	N=getdtablesize();
	FD_ZERO(&ads);
	FD_SET(MainsockFTP,&ads);
	
	while(1)
	{
		memcpy(&rds,&ads,sizeof(rds));
		if(select(N,&rds,(fd_set*)0,(fd_set*)0,(struct timeval*)0)<0)
		{
			printf("select error");
			exit(1);
		}
		if(FD_ISSET(MainsockFTP,&rds))
		{
			ind=-1;
			for(int i=0;i<Size;i++) if(ftpA[i].sockCommand==-1)
			{
				ind=i;
				break;
			}
			if(ind!=-1)
			{
				if((ftpA[ind].sockCommand=accept(MainsockFTP,(sockaddr*) &clientAddr,&Length))<0)
				{
					printf("accept() error");
					exit(1);
				}
				SendMessage(ftpA[ind].sockCommand,FTP_OVERLOAD,"Hello new user");
				FD_SET(ftpA[ind].sockCommand,&ads);
			}
		}
		for(int i=0;i<N;i++) if(i!=MainsockFTP && FD_ISSET(i,&rds))
		{
			bzero(message,BUFFER_SIZE);
			msgLength=recv(i,message,BUFFER_SIZE,0);
			message[msgLength-2]='\0';
			printf("%s\n",message);
			if(msgLength<0)
			{
				printf("recvfrom() error");
				exit(1);
			}
			else if(msgLength==0)
			{
				for(int k=0;k<Size;k++)
				{
					if(ftpA[k].sockCommand==i)
					{
						ZeroFTP(ftpA[k]);
						snprintf(ftpA[k].buffPath,BUFFER_SIZE,"temp/%i.txt",ftpA[k].ID);
						strcpy(ftpA[k].currentPath,path);
						printf("Client %i closed\n", ftpA[k].ID);
					}
				}
				close(i);
				FD_CLR(i,&ads);
				break;
			}
			for(int k=0;k<Size;k++) if(ftpA[k].sockCommand==i) 
			{
				instructionProcessor(ftpA[k], message);
				break;
			}
		}	
	}
	close(MainsockFTP);
}
