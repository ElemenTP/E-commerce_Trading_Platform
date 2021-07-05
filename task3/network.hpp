#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <WinSock2.h>
//#include <Windows.h>
//#include <Ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define s_addr S_un.S_addr

#define PORT 5775u
