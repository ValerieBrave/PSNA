// ServerT.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET sS;
	wVersionRequested = MAKEWORD(2, 2);
	try
	{
		WSAStartup(wVersionRequested, &wsaData);

		if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		std::cout << "---server socket created " << std::endl;

		SOCKADDR_IN serv; // параметры сокета sS
		serv.sin_family = AF_INET; // используется IP-адресация
		serv.sin_port = htons(2000); // порт 2000
		serv.sin_addr.s_addr = INADDR_ANY; // любой собственный IP-адрес
		// связываем параметры с сокетом
		if (bind(sS, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
			throw SetErrorMsgText("bind:", WSAGetLastError());
		std::cout << "---after bind " << std::endl;
		// переводим в режим прослушивания
		if (listen(sS, SOMAXCONN) == SOCKET_ERROR)
			throw SetErrorMsgText("listen:", WSAGetLastError());
		std::cout << "---listening mode " << std::endl;

		SOCKET cS; // сокет для обмена данными с клиентом
		SOCKADDR_IN clnt; // параметры сокета клиента
		memset(&clnt, 0, sizeof(clnt)); // обнулить память
		int lclnt = sizeof(clnt); // размер SOCKADDR_IN

		/*if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
			throw SetErrorMsgText("accept:", WSAGetLastError());*/

		std::cout << "---before accept " << std::endl;
		while ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) != INVALID_SOCKET)
		{
			std::cout << "---after accept "  << std::endl;
			char ibuf[50], //буфер ввода
				obuf[50] = "sever: принято "; //буфер вывода
			int libuf = 0, //количество принятых байт
				lobuf = 0; //количество отправленных байь
			if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
				throw SetErrorMsgText("recv 1:", WSAGetLastError());
			std::cout << "---after recv 1 " << std::endl;
			while (libuf !=0)
			{
				std::cout << "Message: " << ibuf << std::endl;
				if ((lobuf = send(cS, ibuf, strlen(ibuf) + 1, NULL)) == SOCKET_ERROR)
					throw SetErrorMsgText("send:", WSAGetLastError());
				if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR) break;
					//throw SetErrorMsgText("recv 2:", WSAGetLastError());
			}
			std::cout << "---last message received " << std::endl;
		}
		/*std::cout << "Port: " << ntohs(clnt.sin_port) << std::endl;
		std::cout << "IP: " << inet_ntoa(clnt.sin_addr) << std::endl;*/

		
		

		
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


