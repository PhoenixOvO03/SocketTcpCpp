#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

class TcpServer {
	SocketInit socketInit;//初始化
	SOCKET sLiten;//服务器套接字
	FD_SET fd_read;//存储SOCKET对象

public:
	void BindServer(unsigned short port);//绑定套接字
	void Listen();//开始监听
	void Onselect();//选择模型实现多客户端
	void DealWithData(MsgHead* msgHead);//处理数据
	void SendData(MsgHead* msgHead);//发送数据

	TcpServer();
	~TcpServer();
};