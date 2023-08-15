#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<vector>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"
#include"ClientObject.h"

class TcpServer {
	SocketInit socketInit;//��ʼ��
	SOCKET sLiten;//�������׽���
	FD_SET fd_read;//�洢SOCKET����
	std::vector<ClientObject*> m_vecClient;

public:
	void BindServer(unsigned short port);//���׽���
	void Listen();//��ʼ����
	void Onselect();//ѡ��ģ��ʵ�ֶ�ͻ���
	void DealWithData(MsgHead* msgHead);//��������
	void SendData(MsgHead* msgHead);//��������

	TcpServer();
	~TcpServer();
};