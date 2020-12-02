#pragma once
#include "Error.h"
#include <Windows.h>
bool  GetServer(SOCKET cC, const char* call, short port, struct sockaddr* from, int flen);