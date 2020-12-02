#include "pch.h"
#include "ClientAPI.h"

bool  GetServer(SOCKET cC, const char* call, short port, struct sockaddr* from, int flen)
{
	int lobuf = 0, libuf = 0;
	char obuf[50];
	if (lobuf = sendto(cC, call, strlen(call) + 1, NULL, from, flen) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto:", WSAGetLastError());

	if (libuf = recvfrom(cC, obuf, strlen(obuf) + 1, NULL, from, &flen) == SOCKET_ERROR)
		throw SetErrorMsgText("recvfrom:", WSAGetLastError());

	if (!strcmp(obuf, call)) return true;
	else return false;
}