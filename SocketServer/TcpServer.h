#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

class TcpServer {
	SocketInit socketInit;//��ʼ��
	SOCKET sLiten;//�������׽���
	FD_SET fd_read;//�洢SOCKET����

public:
	void BindServer(unsigned short port);//���׽���
	void Listen();//��ʼ����
	void Onselect();//ѡ��ģ��ʵ�ֶ�ͻ���
	void DealWithData(MsgHead* msgHead);//��������
	void SendData(MsgHead* msgHead);//��������

	TcpServer();
	~TcpServer();
};