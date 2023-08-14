#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include <string>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

//ָ���߳�
DWORD WINAPI TreadProc(LPVOID lp) {
	SOCKET sClient = *(SOCKET*)lp;

	while (true) {
		std::cout << "show join create talk exit" << std::endl;

		char buff[1024] = { 0 };
		gets_s(buff, sizeof(buff));

		if (strcmp(buff, "show") == 0) {//��ʾ������
			MsgShow msgShow;
			send(sClient, (const char*)&msgShow, msgShow.datalen, 0);
		}
		else if (strncmp(buff, "join",strlen("join")) == 0) {//����������
			int r = atoi(buff + strlen("join"));
			MsgJoin msgJoin(r);
			send(sClient, (const char*)&msgJoin, msgJoin.datalen, 0);
		}
		else if (strcmp(buff, "create") == 0) {//����������

		}
		else if (strcmp(buff, "talk") == 0) {//����
			std::cout << "��ʼ����" << std::endl;
			MsgIsTalk msgIsTalk;

			while (true) {
				gets_s(msgIsTalk.getBuff(), sizeof(msgIsTalk.getBuff()));

				if (strcmp(msgIsTalk.getBuff(), "leave") == 0) {
					std::cout << "��������" << std::endl;
					MsgLeave msgLeave;
					send(sClient, (const char*)&msgLeave, msgLeave.datalen, 0);
					break;
				}

				send(sClient, (const char*)&msgIsTalk, msgIsTalk.datalen, 0);
			}
		}
		else if (strcmp(buff, "talk") == 0) {//�˳�
			break;
		}
		else
		{
			continue;
		}
	}

	return -1;
}

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

	//���߳�ʵ���շ����ݷ���
	//����ָ��
	HANDLE h = CreateThread(0, 0, TreadProc, (LPVOID)&sClient, 0, 0);

	//������
	while (true) {
		char buff[1024];
		/*gets_s(buff,sizeof(buff));
		send(sClient, buff, strlen(buff),0);*/

		int ret = recv(sClient, buff, sizeof(buff), 0);

		if (ret>0) {

		}
		else {
			printf("�ͻ��˽�������ʧ��");
		}
	}

	WaitForSingleObject(h, INFINITE);

	closesocket(sClient);
	
	system("pause");

	return 0;
}