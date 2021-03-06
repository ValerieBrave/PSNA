// ClientT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET cC;
	wVersionRequested = MAKEWORD(2, 2);
	try
	{
		WSAStartup(wVersionRequested, &wsaData);

		if ((cC = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());

		SOCKADDR_IN serv; // параметры сокета sS
		serv.sin_family = AF_INET; // используется IP-адресация
		serv.sin_port = htons(2000); // порт 2000
		serv.sin_addr.s_addr = inet_addr("80.94.168.140"); // IP-адрес сервера

		if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw SetErrorMsgText("connect:", WSAGetLastError());
		
		char ibuf[50]; //буфер ввода
			
		int libuf = 0, //количество принятых байт
			lobuf = 0; //количество отправленных байт
		int k = 0;

		std::cout << "How many messages to send?" << std::endl;
		std::cin >> k;
		for (int i = 0; i < k; i++)
		{
			char obuf[40];
			sprintf_s(obuf, "Hello from Client! %d", i);
			if ((lobuf = send(cC, obuf, strlen(obuf) + 1, NULL)) == SOCKET_ERROR)
				throw SetErrorMsgText("send:", WSAGetLastError());
			
			std::cout << "--after client send " <<lobuf<< " bytes"<< std::endl;
			if ((libuf = recv(cC, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
				throw SetErrorMsgText("recv:", WSAGetLastError());
			std::cout << "--after client got message from server --" << ibuf  << std::endl;
		}
		if ((lobuf = send(cC, "", 0, NULL)) == SOCKET_ERROR)
			throw SetErrorMsgText("send:", WSAGetLastError());
		std::cout << "--after last message send" << std::endl;
		
	}
	catch (string errorMsgText)
	{
		std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
	}
	system("pause");
    return 0; 
}


