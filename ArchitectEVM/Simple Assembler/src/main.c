#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define countOper 39
#define size_array 100

int memory[100];
int listOper[countOper]
= {0x10, 0x11, 0x20, 0x21, 0x30, 0x31, 0x32, 0x33, 0x40, 0x41,
0x42, 0x43, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
0x59, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68,
0x69, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x00};


int getCommand(char* cmd){
	if(!strcmp(cmd,"READ"))return 0x10;
	if(!strcmp(cmd,"WRITE"))return 0x11;
	if(!strcmp(cmd,"LOAD"))return 0x20;
	if(!strcmp(cmd,"STORE"))return 0x21;
	if(!strcmp(cmd,"ADD"))return 0x30;
	if(!strcmp(cmd,"SUB"))return 0x31;
	if(!strcmp(cmd,"DIVIDE"))return 0x32;
	if(!strcmp(cmd,"MUL"))return 0x33;
	if(!strcmp(cmd,"JUMP"))return 0x40;
	if(!strcmp(cmd,"JNEG"))return 0x41;
	if(!strcmp(cmd,"JZ"))return 0x42;
	if(!strcmp(cmd,"HALT"))return 0x43;
	if(!strcmp(cmd,"LOGRC"))return 0x68;
	return -1;

}

int sc_commandEncode(int command, int operand, int* value)
{
    if(command>127||command<0) return -1;
    if(operand>127||operand<0) return -2;
    *value=0;
    *value=*value | (command<<(8-1));
    *value=*value | operand;
    return 0;
}


int main(int argc, char* argv[])
{
	if(argc!=2){
		printf("Command should look like ./bin/main <filename>\n");
		return -1;
	}
	char temp[]="";
	strcpy(temp,argv[1]);
	FILE *input=fopen(strcat(argv[1],".sa"),"r");
	if(input==NULL)
	{
		printf("File doesn't exist\n");
		return -1;
	}
	FILE *output=fopen(strcat(temp,".o"),"wb+");;
	int last = -1;
	int a,b;
	char str[10],in[3],out[10],s[1024];
	int data;
	while(!feof(input)){
		data=0;
		fgets(s,1024,input);
		int check = sscanf(s,"%s %s %s ",in,str,out);
		if(check == -1)break;
		if(check!=3||strlen(in)!=2||!(strlen(out)==2||strlen(out)==5)){printf("ERROR WRONG INPUT %d %s %s %s \n",check,in,str,out);exit(1);}

		for(int i=0;i<strlen(in);i++) if(!(in[i]>='0'&&in[i]<='9')){printf("ERROR FIRST ARGUMENT INPUT\n");exit(1);}
		a=atoi(in);
		if(a<=last){printf("ERROR WRONG NUMERATION %s %d \n",in,last);exit(1);}
		last=a;
		if(strlen(out)==2){
			if(getCommand(str)==-1){printf("ERROR COMMAND %s\n",str);exit(1);}
			for(int i=0;i<strlen(out);i++) if(!(out[i]>='0'&&out[i]<='9')){printf("ERROR WRONG OUT1\n");exit(1);}
			b=atoi(out);
			sc_commandEncode(getCommand(str),b,&data);
			memory[a]=data;
		}else{
			if(strcmp(str,"=")){printf("ERROR DONT FIND EQUEL\n");exit(1);}
			if(out[0]!='+'&&out[0]!='-'){printf("ERROR NOT FIND +\n");exit(1);}
			for(int i=1;i<strlen(out);i++) if(!isxdigit(out[i])){printf("ERROR WRON OUT2\n");exit(1);}
			b = (int)strtol(out,NULL,16);
			if(b<-0x1fff||b>0x1fff){printf("ERROR WRONG NUMBER %s %d\n",out , b);exit(1);}
			if(b<0) b=abs(b)+(1<<13);
			b+=1<<14;
			memory[a]=b;
		}
	}

	fwrite(memory,sizeof(int),size_array,output);
	fclose(input);
	fclose(output);


    return 0;
}
