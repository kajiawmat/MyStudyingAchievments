#ifndef DATA_H
#define DATA_H

#include<stdio.h>
#include<stdlib.h>
#define BUFFER_SIZE 2048

enum server_response 
{
	COMMENT = 110,
	TRANSFER_DELAY = 120,
	TRANSFER_START = 125,
	FILE_READY = 150,
	COMMAND_CORRECT = 200,
	SYST_INFO = 211,
	DIR_STATUS = 212,
	FILE_STATUS = 213,
	HELP_MESSAGE = 214,
	SYSTEM_TYPE = 215,
	FTP_OVERLOAD = 220,
	QUIT_SUCCESS = 221,
	CHANNEL_CREATED = 225,
	CHANNEL_CLOSED = 226,
	USER_AUTHORIZED = 230,
	REQUEST_SUCCESS = 250,
	PATH_CREATED = 257,
	PASSWORD_NEED = 331,
	AUTHORIZE_NEED = 332,
	CHANNEL_NO_USED = 421,
	CHANNEL_NO_CREATED = 425,
	TRANSFER_AUTOSTOPPED = 426,
	FILE_IS_USED = 450,
	LOCAL_ERROR = 451,
	OUT_OF_MEMORY = 452,
	COMMAND_INCORRECT = 500,
	COMMAND_ARG_INCORRECT = 501,
	COMMAND_IMPOSSIBLE = 502,
	COMMAND_ORDER_INCORRECT = 503,
	USER_NO_AUTHORIZED = 530,
	AUTHORIZED_IS_RECQUIRED = 532,
	FILE_NOT_EXISTS = 550,
	CRIT_OUT_OF_MEMORY = 552
};

enum transfer_type
{
	TYPE_A = 256,
	TYPE_I = 2
};

struct FTP_info
{
	int ID;
	int sockCommand;
	int sockData;
	bool isPasswordNeed;
	bool isAuthorized;
	bool isConnected;
	bool isAborted;
	bool isPasv;
	bool isPort;
	bool isTransfer;
	enum transfer_type typeTransfer;
	char* nameClient;
	char* IPClient;
	char* currentPath;
	char* filePath;
	char* buffPath;
};

#endif
