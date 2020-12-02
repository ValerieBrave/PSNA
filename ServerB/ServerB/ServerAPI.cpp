#include "pch.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include "ServerAPI.h"
#include <ctime>

//const char name[] = "Hello";
bool  GetRequestFromClient(SOCKET s, const char* name, short port,struct sockaddr* from, int* flen )
{
	int lb = 0;
	char ibuf[50];
	if ((lb = recvfrom(s, ibuf, sizeof(ibuf), NULL, from, flen)) == SOCKET_ERROR) throw "recvfrom";
	if (!strcmp(name, (const char*)ibuf)) return true;
	else return false;
}
bool  PutAnswerToClient(SOCKET sS, const char* name, struct sockaddr* to, int lto)
{
	int lobuf = 0;
	if (lobuf = sendto(sS, name, strlen(name) + 1, NULL, to, lto) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto:", WSAGetLastError());
	return true;
}
bool FindServers(const char* call, short port, struct sockaddr* from, int* flen)
{
	SOCKET cC;
	int found = 0;
	int optval = 1, lb = 0, lobuf = 0;

	SOCKADDR_IN all;                        
	all.sin_family = AF_INET;                
	all.sin_port = htons(port);             
	all.sin_addr.s_addr = INADDR_BROADCAST;
	
	timeval timeout;
	timeout.tv_sec = 10000;
	timeout.tv_usec = 0;
	try
	{
		if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
			throw  SetErrorMsgText("socket:", WSAGetLastError());
		}
		if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR) {
			throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());
		}
		if (setsockopt(cC, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout))) {
			throw  SetErrorMsgText("setsocketopt:", WSAGetLastError());
		}
		if ((lb = sendto(cC, call, sizeof(call) + 2, NULL, (sockaddr*)&all, sizeof(all))) == SOCKET_ERROR) {
			throw SetErrorMsgText("sendto:", WSAGetLastError());
		}
		char buf[50];
		while (true)
		{
			if (recvfrom(cC, buf, sizeof(buf), NULL, from, flen) == SOCKET_ERROR) {
				throw  SetErrorMsgText("recvfrom:", WSAGetLastError());
			}
			if (strcmp(call, buf) == 0) {
				cout << "Server IP: " << inet_ntoa(((SOCKADDR_IN*)from)->sin_addr) << endl;
				found++;
			}
		}
	}
	catch (std::string errorMsgText)
	{
		if (WSAGetLastError() == WSAETIMEDOUT) {
			cout << "Find servers: " << found << endl;
			if (closesocket(cC) == SOCKET_ERROR) throw SetErrorMsgText("closesocket: ", WSAGetLastError());
		}
		else throw errorMsgText;
		
	}
	
}
