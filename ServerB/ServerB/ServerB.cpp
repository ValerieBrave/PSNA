// ServerB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
//#include "Error.h"
#include "ServerAPI.h"

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET sS, broadcast;
	wVersionRequested = MAKEWORD(2, 2);
	try
	{
		WSAStartup(wVersionRequested, &wsaData);
		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());

		SOCKADDR_IN serv, clnt;
		serv.sin_family = AF_INET;
		serv.sin_port = htons(2000);
		serv.sin_addr.s_addr = INADDR_ANY;

		//------------------------------------
		memset(&clnt, 0, sizeof(clnt));
		int lc = sizeof(clnt);

		FindServers("Hello", 2000, (sockaddr*)&clnt, &lc);


		//------------------------------------

		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("bind:", WSAGetLastError());
		
		SOCKADDR_IN from;
		memset(&from, 0, sizeof(from));
		int flen = sizeof(from);
		try
		{
			while (true)
			{
				if (GetRequestFromClient(sS, "Hello", 2000, (sockaddr*)&from, &flen))
				{
					std::cout << "client IP: " << inet_ntoa(from.sin_addr) << std::endl;
					std::cout << "client port: " << ntohs(from.sin_port) << std::endl;
					PutAnswerToClient(sS, "Hello", (sockaddr*)&from, flen);
				}
			}
			
		}
		catch (string errorMsgText)
		{
			std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
		}
		

		

		closesocket(sS);
		WSACleanup();
	}
	catch(std::string errorMsgText)
	{
		std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
	}
	system("pause");
    return 0; 
}


