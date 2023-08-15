#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

class TcpClient {
	SocketInit socketInit;//��ʼ��������
	SOCKET sClient;//�ͻ����׽���

public:
	void connectServer(const char* ip, unsigned short port);//���ӷ�����
	void RecvData();//��������
	void SendData(MsgHead * msgHead);//��������

	TcpClient();
	
	~TcpClient();
};