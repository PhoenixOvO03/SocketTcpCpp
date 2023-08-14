#ifndef _SOCKET_INIT_H_
#define _SOCKET_INIT_H_

#include<iostream>
#include<WinSock2.h>

#pragma comment(lib,"ws2_32.lib")

class SocketInit {
public:
	SocketInit() {
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wasData;
		if (WSAStartup(sockVersion, &wasData) != 0) {
			std::cout << "¶¯Ì¬Á´½Ó¿â¼ÓÔØÊ§°Ü" << std::endl;
		}
	}

	~SocketInit() {
		WSACleanup();
	}
};

#endif // !_SOCKET_INIT_H_
