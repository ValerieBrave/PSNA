// ClientS.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "ClientSAPI.h"
#include "Error.h"


int main()
{
	WSADATA wsaData;
	SOCKADDR_IN clnt;
	int lc = sizeof(clnt);
	try
	{
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) throw  SetErrorMsgText("Startup: ", WSAGetLastError());
		GetServerByName("DESKTOP-K6FD3O4", "Hello", (sockaddr*)&clnt, &lc);
		if (WSACleanup() == SOCKET_ERROR) throw  SetErrorMsgText("Cleanup: ", WSAGetLastError());
		
	}
	catch (string errorMsgText) 
	{
		cout << endl << errorMsgText;
	}
    return 0; 
}
