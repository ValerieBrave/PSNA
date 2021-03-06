// ClientU.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "Error.h"
#include <time.h>
#include <Windows.h>

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	SOCKET cC;
	wVersionRequested = MAKEWORD(2, 2);
	try
	{
		WSAStartup(wVersionRequested, &wsaData);

		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
			throw SetErrorMsgText("socket:", WSAGetLastError());
		SOCKADDR_IN serv; // параметры сокета sS
		serv.sin_family = AF_INET; // используется IP-адресация
		serv.sin_port = htons(2000); // порт 2000
		serv.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес сервера
		int ls = sizeof(serv);

		if ((connect(cC, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw SetErrorMsgText("connect:", WSAGetLastError());
		
		int lobuf = 0; //количество отправленных
		char ibuf[50]; //буфер ввода
		int lb = 0; //количество принятых байт
		int k = 0;
		char obuf[50];
		std::cout << "How many messages to send?" << std::endl;
		std::cin >> k;

		clock_t t1 = 0, t2 = 0;

		t1 = clock();
		for (int i = 0; i < k; i++)
		{
			
			sprintf_s(obuf, "Hello from ClientU1! %d", i);

			if ((lobuf = sendto(cC, obuf, strlen(obuf) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
				throw SetErrorMsgText("sendto:", WSAGetLastError());

			/*if (lb = recvfrom(cC, ibuf, sizeof(ibuf), NULL, (sockaddr*)&serv, &ls) == SOCKET_ERROR)
				throw SetErrorMsgText("recv:", WSAGetLastError());
			std::cout <<"from serverU: "<< ibuf << std::endl;*/
		}
		t2 = clock();
		std::cout << "Transmission time: " << (t2 - t1) / CLOCKS_PER_SEC << " seconds" << std::endl;
		if ((lobuf = sendto(cC, "", 0, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
			throw SetErrorMsgText("send:", WSAGetLastError());
		std::cout << "-- last message sent" << std::endl;
	}
	catch (string errorMsgText)
	{
		std::cout << std::endl << "WSAGetLastError: " << errorMsgText;
	}
	Sleep(5000);
	closesocket(cC);
	WSACleanup();
	system("pause");
    return 0; 
}
