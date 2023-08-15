#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include <string>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

class TcpClient {
	SocketInit socketInit;//初始化库连接
	SOCKET sClient;//客户端套接字

public:
	void connectServer(const char* ip, unsigned short port);//连接服务器
	void RecvData();//接受数据
	void SendData(MsgHead * msgHead);//发送数据
	SOCKET getSocket();//获取客户端套接字

	TcpClient();
	
	~TcpClient();
};