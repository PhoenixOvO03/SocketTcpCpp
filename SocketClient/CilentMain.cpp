#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include <string>

#include"../SocketInit/SocketInit.hpp"

int main() {
	SocketInit socketInit;

	//�����ͻ����׽���
	SOCKET sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipv4����ʽ�׽��֣�Э��

	if (sClient == SOCKET_ERROR) {
		std::cout << "�ͻ����׽��ִ���ʧ��" << std::endl;
		return -1;
	}

	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(12306);
	sock_in.sin_addr.S_un.S_addr = inet_addr("10.128.81.74");

	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		std::cout << "���ӷ�����ʧ��" << std::endl;
		return -1;
	}
	else {
		std::cout << "���ӷ������ɹ�" << std::endl;
	}

	while (1) {
		char buff[1024];
		gets_s(buff,sizeof(buff));
		send(sClient, buff, strlen(buff),0);
	}

	closesocket(sClient);
	
	system("pause");

	return 0;
}