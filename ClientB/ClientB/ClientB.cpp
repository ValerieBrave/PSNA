// ClientB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "Error.h"
#include "ClientAPI.h"

int main()
{

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	SOCKET cC;
	try
	{
		WSAStartup(wVersionRequested, &wsaData);
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		
		SOCKADDR_IN serv;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		serv.sin_addr.s_addr = INADDR_BROADCAST;

		int optval = 1;
		if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST,(char*)&optval, sizeof(int)) == SOCKET_ERROR)
			throw SetErrorMsgText("opt:", WSAGetLastError());

		bool found = false;
		
		found = GetServer(cC, "Hello", 2000, (sockaddr*)&serv, sizeof(serv));
		if (found)
		{
			std::cout << "server IP: " << inet_ntoa(serv.sin_addr) << std::endl;
			std::cout << "server port: " << ntohs(serv.sin_port) << std::endl;
		}
		
		closesocket(cC);
		WSACleanup();
	}
	catch (string errorMsgText)
	{
		std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
	}
	
	
    return 0; 
}

