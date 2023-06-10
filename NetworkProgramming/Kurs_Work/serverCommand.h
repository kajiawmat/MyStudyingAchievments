#ifndef SERVERCOMMAND_H
#define SERVERCOMMAND_H

#include "data.h"
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<time.h>

void ZeroFTP(FTP_info &ftp);
void* FileStore(void* _ftp);
void* FileRetrieve(void* _ftp);
int SendMessage(int sockClient,enum server_response num, const char txt[]);
int SendData(int sockClient, const char txt[]);
int RecvData(int sockClient, char* &txt);
void ReadFilePath(FILE* fp, char* &txt);
void ReadFileList(FILE* fp, FTP_info &ftp);
void ReadFileHelp(FILE* fp,char* &txt);
void Abort(FTP_info &ftp);
void CurrDirUp(FTP_info &ftp);
void CurrWorkDir(FTP_info &ftp, char command[]);
void DelFile(FTP_info &ftp, char command[]);
void Help(FTP_info &ftp);
void List(FTP_info &ftp);
void ModDateTime(FTP_info &ftp, char command[]);
void MakeDir(FTP_info &ftp, char command[]);
void NameList(FTP_info &ftp);
void Noop(FTP_info &ftp);
void InPass(FTP_info &ftp, char command[]);
void ActMode(FTP_info &ftp, char command[]);
void PresWorkDir(FTP_info &ftp);
void Quit(FTP_info &ftp);
void Retrieve(FTP_info &ftp, char command[]);
void RemoveDir(FTP_info &ftp, char command[]);
void ReName(FTP_info &ftp, char command[]);
void FileSize(FTP_info &ftp, char command[]);
void Store(FTP_info &ftp, char command[]);
void SystemInfo(FTP_info &ftp);
void TypeTransfer(FTP_info &ftp, char command[]);
void InUser(FTP_info &ftp, char command[]);
void UnNamedFunction(FTP_info &ftp);
void instructionProcessor(FTP_info &ftp, char command[]);


#endif
