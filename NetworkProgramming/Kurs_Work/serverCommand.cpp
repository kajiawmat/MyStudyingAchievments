#include "serverCommand.h"

void ZeroFTP(FTP_info &ftp)
{
	ftp.sockCommand=-1;
	ftp.sockData=-1;
	ftp.isPasswordNeed=false;
	ftp.isAuthorized=false;
	ftp.isConnected=false;
	ftp.isTransfer=false;
	ftp.isAborted=false;
	ftp.isPasv=false;
	ftp.isPort=false;
	ftp.typeTransfer=TYPE_I;
	ftp.nameClient=new char[BUFFER_SIZE];
	ftp.IPClient=new char[BUFFER_SIZE];
	ftp.currentPath=new char[BUFFER_SIZE];
	ftp.filePath=new char[BUFFER_SIZE];
	ftp.buffPath=new char[BUFFER_SIZE];
}

void* FileStore(void* _ftp)
{
	struct FTP_info* ftp=((struct FTP_info*) _ftp);
	int length;
	FILE *fp;
	char *txt=new char[BUFFER_SIZE];
	char *message=new char[BUFFER_SIZE];
	if(ftp->typeTransfer==TYPE_A)
	{
		fp=fopen(ftp->filePath,"w");
		while(true)
		{
			if(ftp->isAborted)
			{
				SendMessage(ftp->sockCommand,TRANSFER_AUTOSTOPPED,"Connection closed; transfer aborted");
				ftp->isAborted=false;
				ftp->isConnected=false;
				close(ftp->sockData);
				fclose(fp);
				return NULL;
			}
			bzero(message,BUFFER_SIZE);
			bzero(txt,BUFFER_SIZE);
			length=RecvData(ftp->sockData,message);
			if(length==0) break;
			strncpy(txt,message,length);
			fprintf(fp,"%s",txt);
		}
	}
	else
	{
		fp=fopen(ftp->filePath,"wb");
		while(true)
		{
			if(ftp->isAborted)
			{
				SendMessage(ftp->sockCommand,TRANSFER_AUTOSTOPPED,"Connection closed; transfer aborted");
				ftp->isAborted=false;
				ftp->isConnected=false;
				close(ftp->sockData);
				return NULL;
			}
			bzero(message,BUFFER_SIZE);
			length=RecvData(ftp->sockData,message);
			if(length==0) break;
			strncpy(txt,message,length);
			fwrite(txt,sizeof(char),length,fp);
		}
	}
	fclose(fp);
	ftp->isConnected=false;
	close(ftp->sockData);
	SendMessage(ftp->sockCommand,CHANNEL_CLOSED,"File stored OK");
	//delete message;
	//delete txt;
	return NULL;
}

void* FileRetrieve(void* _ftp)
{
	struct FTP_info* ftp=((struct FTP_info*) _ftp);
	int length;
	FILE *fp;
	char message[BUFFER_SIZE];
	if(ftp->typeTransfer==TYPE_A)
	{
		fp=fopen(ftp->filePath,"r");
		while(true)
		{
			if(ftp->isAborted)
			{
				SendMessage(ftp->sockCommand,TRANSFER_AUTOSTOPPED,"Connection closed; transfer aborted");
				ftp->isAborted=false;
				ftp->isConnected=false;
				close(ftp->sockData);
				fclose(fp);
				return NULL;
			}
			bzero(message,BUFFER_SIZE);
			if(fgets(message,BUFFER_SIZE,fp)==NULL) break;
			SendData(ftp->sockData,message);
		}
	}
	else
	{
		fp=fopen(ftp->filePath,"rb");
		while(true)
		{
			if(ftp->isAborted)
			{
				SendMessage(ftp->sockCommand,TRANSFER_AUTOSTOPPED,"Connection closed; transfer aborted");
				ftp->isAborted=false;
				ftp->isConnected=false;
				close(ftp->sockData);
				return NULL;
			}
			if(feof(fp)) break;
			bzero(message,BUFFER_SIZE);
			fread(message,sizeof(char),BUFFER_SIZE,fp);
			SendData(ftp->sockData,message);
		}
	}
	fclose(fp);
	ftp->isConnected=false;
	close(ftp->sockData);
	SendMessage(ftp->sockCommand,CHANNEL_CLOSED,"File retrieved OK");
	return NULL;
}

int SendMessage(int sockClient,enum server_response num, const char txt[])
{
	char message[BUFFER_SIZE];
	snprintf(message,BUFFER_SIZE,"%i %s\n",num,txt);
	return send(sockClient,message,strlen(message),0);
}

int SendData(int sockClient, const char txt[])
{
	return send(sockClient,txt,strlen(txt),0);
}

int RecvData(int sockClient, char* &txt)
{
	return recv(sockClient,txt,BUFFER_SIZE,0);
}

void ReadFilePath(FILE* fp, char* &txt)
{
	txt=new char[BUFFER_SIZE];
	fscanf(fp,"%s",txt);
}
void ReadFileList(FILE* fp, FTP_info &ftp)
{
	char *txt=new char[BUFFER_SIZE];
	fgets(txt,BUFFER_SIZE,fp);
	while(true)
	{
		if(ftp.isAborted)
		{
			SendMessage(ftp.sockCommand,TRANSFER_AUTOSTOPPED,"Connection closed; transfer aborted");
			ftp.isAborted=false;
			ftp.isConnected=false;
			close(ftp.sockData);
			return;
		}
		fgets(txt,BUFFER_SIZE,fp);
		if(feof(fp)) break;
		printf("%s",txt);
		SendData(ftp.sockData,txt);
	}
	ftp.isConnected=false;
	ftp.isTransfer=false;
	close(ftp.sockData);
	SendMessage(ftp.sockCommand,CHANNEL_CLOSED,"Directory send OK");
}

void ReadFileHelp(FILE* fp,char* &txt)
{
	txt=new char[BUFFER_SIZE];
	char temp[BUFFER_SIZE];
	while(true)
	{
		if(fgets(temp,BUFFER_SIZE,fp)==NULL) break;
		strcat(txt,temp);
	}
}

void Abort(FTP_info &ftp)
{
	if(ftp.isConnected)
	{
		ftp.isAborted=true;
		while(ftp.isConnected);
		SendMessage(ftp.sockCommand,CHANNEL_CLOSED,"Channel data successfully aborted");
	}
	else
	{
		SendMessage(ftp.sockCommand,COMMAND_IMPOSSIBLE,"Channel data wasn't created");
	}
}
void CurrDirUp(FTP_info &ftp)
{
	char com[BUFFER_SIZE];
	snprintf(com,BUFFER_SIZE,"./scripts/Currdirup.sh %i %s",ftp.ID,ftp.currentPath);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	ReadFilePath(fp,txt);
	strcpy(ftp.currentPath,txt);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	//delete txt;
	SendMessage(ftp.sockCommand,REQUEST_SUCCESS,"Directory successfully changed");
}
void CurrWorkDir(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input new directory");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsdir.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Failed to change directory");
		return;
	}
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"./scripts/Currworkdir.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt;
	fp=fopen(ftp.buffPath,"r");
	ReadFilePath(fp,txt);
	strcpy(ftp.currentPath,txt);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	SendMessage(ftp.sockCommand,REQUEST_SUCCESS,"Directory successfully changed");
}
void DelFile(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input deleting file");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsfile.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Failed to //delete file");
		return;
	}
	ReadFilePath(fp,txt);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"./scripts/Delfile.sh %s",txt);
	system(com);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	//delete txt;
	SendMessage(ftp.sockCommand,REQUEST_SUCCESS,"File successfully //deleted");
}
void Help(FTP_info &ftp)
{
	char* txt;
	FILE *fp=fopen("Help.txt","r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,LOCAL_ERROR,"Help.txt not found");
		return;
	}
	ReadFileHelp(fp,txt);
	SendData(ftp.sockCommand,txt);
	SendMessage(ftp.sockCommand,HELP_MESSAGE,"Help OK");
	fclose(fp);
	//delete txt;
}
void List(FTP_info &ftp)
{
	if(ftp.isConnected==false)
	{
		SendMessage(ftp.sockCommand,CHANNEL_NO_CREATED,"Channel data not created");
		return;
	}
	if(ftp.isTransfer)
	{
		SendMessage(ftp.sockCommand,TRANSFER_START,"Data connection already open; transfer starting");
		return;
	}
	char com[BUFFER_SIZE];
	snprintf(com,BUFFER_SIZE,"./scripts/List.sh %i %s",ftp.ID,ftp.currentPath);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	SendMessage(ftp.sockCommand,FILE_READY,"Here comes directory listing");
	ReadFileList(fp,ftp);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	////delete txt;
}
void ModDateTime(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input existing filepath");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsfile.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Could not get file modification time");
		return;
	}
	ReadFilePath(fp,txt);
	fclose(fp);
	struct stat buf;
	stat(txt,&buf);
	char message[BUFFER_SIZE];
	snprintf(message,BUFFER_SIZE,"%s",ctime(&buf.st_mtime));
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	SendMessage(ftp.sockCommand,FILE_STATUS,message);
	//delete txt;
}
void MakeDir(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input filepath to new directory");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsdir.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp!=NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Directory already exists");
		fclose(fp);
		snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
		system(com);
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Makedir.sh %s %s",ftp.currentPath,path);
	system(com);
	SendMessage(ftp.sockCommand,PATH_CREATED,"Directory created");
}
void NameList(FTP_info &ftp)
{
	if(ftp.isConnected==false)
	{
		SendMessage(ftp.sockCommand,CHANNEL_NO_CREATED,"Channel data not created");
		return;
	}
	if(ftp.isTransfer)
	{
		SendMessage(ftp.sockCommand,TRANSFER_START,"Data connection already open; transfer starting");
		return;
	}
	char com[BUFFER_SIZE];
	snprintf(com,BUFFER_SIZE,"./scripts/Namelist.sh %i %s",ftp.ID,ftp.currentPath);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	SendMessage(ftp.sockCommand,FILE_READY,"Here comes directory listing");
	ReadFileList(fp,ftp);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	////delete txt;
}

void Noop(FTP_info &ftp)
{
	SendMessage(ftp.sockCommand,COMMAND_CORRECT,"Noop successful");
}
void InPass(FTP_info &ftp, char command[])
{
	if(ftp.isAuthorized) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ORDER_INCORRECT,"You already logged in");
		return;
	}
	char *savePtr;
	char *pass=strtok_r(command," ",&savePtr);
	pass=strtok_r(NULL," ",&savePtr);
	if(pass==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"Please input password");
		return;
	}
	if(ftp.isPasswordNeed==false)
	{
		SendMessage(ftp.sockCommand,COMMAND_ORDER_INCORRECT,"You should use command USER first");
		return;
	}
	ftp.isAuthorized=true;
	ftp.isPasswordNeed=false;
	SendMessage(ftp.sockCommand,USER_AUTHORIZED,"Login successful");
}
void ActMode(FTP_info &ftp, char command[])
{
	char *savePtr,*savePtr1;
	char *adr=strtok_r(command," ",&savePtr);
	char *temp;
	struct sockaddr_in dataAddr;
	int numbers[6];
	adr=strtok_r(NULL," ",&savePtr);
	if(adr==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"Please input IP-adress and port");
		return;
	}
	//printf("%s\n",adr);
	temp=strtok_r(adr,",",&savePtr1);
	try
	{
		for(int i=0;i<6;i++) 
		{
			sscanf(temp,"%i",&(numbers[i]));
			temp=strtok_r(NULL,",",&savePtr1);
		}
	}
	catch(...)
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input corrrect IP-adress and port");
		return;
	}
	for(int i=0;i<6;i++) if(numbers[i]<0 || numbers[i]>255) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input corrrect IP-adress and port");
		return;
	}
	bzero((char*) &dataAddr, sizeof(dataAddr));
	dataAddr.sin_family=AF_INET;
	snprintf(ftp.IPClient,BUFFER_SIZE,"%i.%i.%i.%i",numbers[0],numbers[1],numbers[2],numbers[3]);
	inet_aton(ftp.IPClient,&(dataAddr.sin_addr));
	dataAddr.sin_port=htons(numbers[4]*256+numbers[5]);
	ftp.sockData=socket(AF_INET, SOCK_STREAM, 0);
	if(connect(ftp.sockData,(sockaddr*)&dataAddr,sizeof(dataAddr))<0)
	{
		printf("Connect Error");
		exit(1);
	}
	ftp.isConnected=true;
	SendMessage(ftp.sockCommand,COMMAND_CORRECT,"PORT command succesful");
}
void PresWorkDir(FTP_info &ftp)
{
	char message[BUFFER_SIZE];
	snprintf(message,BUFFER_SIZE,"\"%s\" is the current directory",ftp.currentPath);
	SendMessage(ftp.sockCommand,PATH_CREATED,message);
}
void Quit(FTP_info &ftp)
{
	if(ftp.isTransfer) Abort(ftp);
	SendMessage(ftp.sockCommand,QUIT_SUCCESS,"Goodbye Client.");
	ZeroFTP(ftp);
}

void Retrieve(FTP_info &ftp, char command[])
{
	if(ftp.isConnected==false)
	{
		SendMessage(ftp.sockCommand,CHANNEL_NO_CREATED,"Channel data not created");
		return;
	}
	if(ftp.isTransfer)
	{
		SendMessage(ftp.sockCommand,TRANSFER_START,"Data connection already open; transfer starting");
		return;
	}
	char *savePtr;
	char *name=strtok_r(command," \n",&savePtr);
	name=strtok_r(NULL," \n",&savePtr);
	if(name==NULL)
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input file for store on server");
		return;
	}
	snprintf(ftp.filePath,BUFFER_SIZE,"%s/%s",ftp.currentPath,name);
	FILE *fp=fopen(ftp.filePath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Failed to retrieve file (doesn't exist)");
		return;
	}
	fclose(fp);
	SendMessage(ftp.sockCommand,FILE_READY,"Here comes file transfer");
	pthread_t pth_retrieve;
	pthread_create(&pth_retrieve,NULL,&FileRetrieve,(void*) &ftp);
	pthread_detach(pth_retrieve);
}

void RemoveDir(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input filepath to new directory");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsdir.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Directory not exists");
		return;
	}
	ReadFilePath(fp,txt);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"./scripts/Removedir.sh %s",txt);
	system(com);
	//delete txt;
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
}
void ReName(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input old filename");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsfile.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt1;
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Failed to rename file (doesn't exist)");
		return;
	}
	ReadFilePath(fp,txt1);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL || strncmp(path,"RNTO",4)!=0)
	{
		SendMessage(ftp.sockCommand,COMMAND_INCORRECT,"Command RNTO expected");
		return;
	}
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL)
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input new filename");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Rename.sh %s %s %s",ftp.currentPath,txt1,path);
	system(com);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	SendMessage(ftp.sockCommand,REQUEST_SUCCESS,"File successfully renamed");
}
void FileSize(FTP_info &ftp, char command[])
{
	char com[BUFFER_SIZE];
	char *savePtr;
	char *path=strtok_r(command," ",&savePtr);
	path=strtok_r(NULL," ",&savePtr);
	if(path==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input existing filepath");
		return;
	}
	snprintf(com,BUFFER_SIZE,"./scripts/Existsfile.sh %i %s %s",ftp.ID,ftp.currentPath,path);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	if(fp==NULL)
	{
		SendMessage(ftp.sockCommand,FILE_NOT_EXISTS,"Could not get file size in bytes");
		return;
	}
	ReadFilePath(fp,txt);
	fclose(fp);
	struct stat buf;
	stat(txt,&buf);
	char message[BUFFER_SIZE];
	snprintf(message,BUFFER_SIZE,"%li B",buf.st_size);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	SendMessage(ftp.sockCommand,FILE_STATUS,message);
	//delete txt;
}
void Store(FTP_info &ftp, char command[])
{
	if(ftp.isConnected==false)
	{
		SendMessage(ftp.sockCommand,CHANNEL_NO_CREATED,"Channel data not created");
		return;
	}
	if(ftp.isTransfer)
	{
		SendMessage(ftp.sockCommand,TRANSFER_START,"Data connection already open; transfer starting");
		return;
	}
	char *savePtr,*savePtr1;
	char *path=strtok_r(command," \n",&savePtr);
	path=strtok_r(NULL," \n",&savePtr);
	if(path==NULL)
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input file for store on server");
		return;
	}
	char *name, *next_token;
	name=strtok_r(path,"/",&savePtr1);
	next_token=strtok_r(NULL,"/",&savePtr1);
	while(next_token!=NULL)
	{
		name=next_token;
		next_token=strtok_r(NULL,"/",&savePtr1);
	}
	snprintf(ftp.filePath,BUFFER_SIZE,"%s/%s",ftp.currentPath,name);
	FILE *fp;
	int ind=0;
	do
	{
		fp=fopen(ftp.filePath,"r");
		if(fp==NULL) break;
		fclose(fp);
		snprintf(ftp.filePath,BUFFER_SIZE,"%s/%i%s",ftp.currentPath,ind,name);
		ind++;
	}while(true);
	SendMessage(ftp.sockCommand,FILE_READY,"Here comes file transfer");
	pthread_t pth_store;
	pthread_create(&pth_store,NULL,&FileStore,(void*) &ftp);
	pthread_detach(pth_store);
}
void SystemInfo(FTP_info &ftp)
{
	char com[BUFFER_SIZE];
	snprintf(com,BUFFER_SIZE,"./scripts/Systeminfo.sh %i",ftp.ID);
	system(com);
	char *txt;
	FILE *fp=fopen(ftp.buffPath,"r");
	ReadFilePath(fp,txt);
	SendMessage(ftp.sockCommand,SYSTEM_TYPE,txt);
	fclose(fp);
	snprintf(com,BUFFER_SIZE,"rm temp/%i.txt",ftp.ID);
	system(com);
	//delete txt;
}
void TypeTransfer(FTP_info &ftp, char command[])
{
	char *savePtr;
	char *type=strtok_r(command," ",&savePtr);
	type=strtok_r(NULL," ",&savePtr);
	if(type==NULL)
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"PLease input type transfer");
		return;
	}
	if(strncmp(type,"I",1)==0) ftp.typeTransfer=TYPE_I;
	else if(strncmp(type,"A",1)==0) ftp.typeTransfer=TYPE_A;
	else
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"This type not exists");
		return;
	}
	SendMessage(ftp.sockCommand,COMMAND_CORRECT,"Type transfer change successful");
}
void InUser(FTP_info &ftp, char command[])
{
	if(ftp.isAuthorized) 
	{
		SendMessage(ftp.sockCommand,USER_NO_AUTHORIZED,"Can't change to another user");
		return;
	}
	char *savePtr;
	char *name=strtok_r(command," ",&savePtr);
	name=strtok_r(NULL," ",&savePtr);
	if(name==NULL) 
	{
		SendMessage(ftp.sockCommand,COMMAND_ARG_INCORRECT,"Syntax error in parameters or arguments");
		return;
	}
	strcpy(ftp.nameClient,name);
	ftp.isPasswordNeed=true;
	ftp.isAuthorized=false;
	SendMessage(ftp.sockCommand,PASSWORD_NEED,"Please specify the password");
	
}
void UnNamedFunction(FTP_info &ftp)
{
	SendMessage(ftp.sockCommand,COMMAND_INCORRECT,"Syntax error, command inrecognized\nPlease use HELP");
}

void instructionProcessor(FTP_info &ftp, char command[])
{
	if(strncmp(command,"HELP",4)==0) 	
	{
		Help(ftp);
		return;
	}
	if(ftp.isPasswordNeed)
	{
		if(strncmp(command,"PASS",4)!=0) SendMessage(ftp.sockCommand,COMMAND_ORDER_INCORRECT,"Please, input password to log in");
		else InPass(ftp,command);
		return;
	}
	if(ftp.isAuthorized==false && strncmp(command,"USER",4)!=0)
	{
		SendMessage(ftp.sockCommand,USER_NO_AUTHORIZED,"Please log in with USER and PASS");
		return;
	}
	if(strncmp(command,"ABOR",4)==0) 		Abort(ftp);
	else if(strncmp(command,"CDUP",4)==0) 	CurrDirUp(ftp);
	else if(strncmp(command,"CWD",3)==0)  	CurrWorkDir(ftp,command); 
	else if(strncmp(command,"DELE",4)==0) 	DelFile(ftp,command);
	else if(strncmp(command,"LIST",4)==0) 	List(ftp);
	else if(strncmp(command,"MDTM",4)==0) 	ModDateTime(ftp,command);
	else if(strncmp(command,"MKD",3)==0)  	MakeDir(ftp,command);
	else if(strncmp(command,"NLST",4)==0) 	NameList(ftp); 
	else if(strncmp(command,"NOOP",4)==0) 	Noop(ftp);
	else if(strncmp(command,"PORT",4)==0) 	ActMode(ftp,command);
	else if(strncmp(command,"PWD",3)==0) 	PresWorkDir(ftp);
	else if(strncmp(command,"QUIT",4)==0)	Quit(ftp);
	else if(strncmp(command,"RETR",4)==0)	Retrieve(ftp,command);
	else if(strncmp(command,"RMD",3)==0)	RemoveDir(ftp,command);
	else if(strncmp(command,"RNFR",4)==0)	ReName(ftp,command); 
	else if(strncmp(command,"SIZE",4)==0)	FileSize(ftp,command);
	else if(strncmp(command,"STOR",4)==0)	Store(ftp,command);
	else if(strncmp(command,"SYST",4)==0)	SystemInfo(ftp);
	else if(strncmp(command,"TYPE",4)==0)	TypeTransfer(ftp,command);
	else if(strncmp(command,"USER",4)==0)	InUser(ftp,command);
	else					UnNamedFunction(ftp);
}


