#pragma once
#include "Winsock2.h" 
#include <string>
#pragma comment(lib, "WS2_32.lib")
using namespace std;
string SetErrorMsgText(string msgText, int code);
string GetErrorMsgText(int code);
