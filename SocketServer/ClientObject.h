#pragma once

#include"../SocketInit/SocketInit.hpp"

//�ͻ�����
class ClientObject {
private:
	SOCKET m_cs;
public:
	SOCKET getSocket();
	void setSocket(SOCKET socket);

	ClientObject();
	~ClientObject();
};