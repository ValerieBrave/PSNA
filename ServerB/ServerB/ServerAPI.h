#pragma once
#include "Error.h"


bool  GetRequestFromClient(
	SOCKET s,
	const char*            name, //[in] �������� �������  
	short            port, //[in] ����� �������������� ����� 
	struct sockaddr* from, //[out] ��������� �� SOCKADDR_IN
	int*             flen  //[out] ��������� �� ������ from 
);
bool  PutAnswerToClient(
	SOCKET sS,
	const char*            name, //[in] �������� �������  
	struct sockaddr* to,   //[in] ��������� �� SOCKADDR_IN
	int             lto   //[in] ��������� �� ������ from 
);
bool FindServers(const char* call, short port, struct sockaddr* from, int* flen);