// ServerU.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"
#include <Windows.h>

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET sS;
	wVersionRequested = MAKEWORD(2, 2);
	try
	{
		WSAStartup(wVersionRequested, &wsaData);

		if ((sS = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		
		SOCKADDR_IN serv; 
		serv.sin_family = AF_INET; 
		serv.sin_port = htons(2000); 
		serv.sin_addr.s_addr = INADDR_ANY; 
		
		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("bind:", WSAGetLastError());
		
		SOCKADDR_IN clnt; 
		memset(&clnt, 0, sizeof(clnt)); 

		int lc = sizeof(clnt);
		char ibuf[50];
		int lb = 0, lobuf = 0;
		char *msgs;
		std::cout << "ready to receive!" << std::endl;
		while (true)
		{
			if ((lb = recvfrom(sS, ibuf, sizeof(ibuf), NULL, (sockaddr*)&clnt, &lc)) == SOCKET_ERROR) throw "recvfrom";
			if (lb == 0) 
			{
				std::cout << "last message!" << std::endl;
				break;
			} 
			std::cout << "Message: " << ibuf << std::endl;
			Sleep(200);
			/*if (lobuf = sendto(sS, ibuf, strlen(ibuf) + 1, NULL, (sockaddr*)&clnt, sizeof(clnt)) == SOCKET_ERROR)
				throw SetErrorMsgText("sendto:", WSAGetLastError());*/
			
		}
		std::cout << "after while" << std::endl;
		
	}
	catch (string errorMsgText)
	{
		std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
	}

	closesocket(sS);
	WSACleanup();
	system("pause");
    return 0; 
}


