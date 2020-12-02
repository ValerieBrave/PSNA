#pragma once
#include "Error.h"


bool  GetRequestFromClient(
	SOCKET s,
	const char*            name, //[in] позывной сервера  
	short            port, //[in] номер просушиваемого порта 
	struct sockaddr* from, //[out] указатель на SOCKADDR_IN
	int*             flen  //[out] указатель на размер from 
);
bool  PutAnswerToClient(
	SOCKET sS,
	const char*            name, //[in] позывной сервера  
	struct sockaddr* to,   //[in] указатель на SOCKADDR_IN
	int             lto   //[in] указатель на размер from 
);
bool FindServers(const char* call, short port, struct sockaddr* from, int* flen);