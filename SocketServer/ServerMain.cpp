#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

////���߳�ʵ�ֶ�ͻ���
//DWORD WINAPI ThreadProc(LPVOID lp) {
//	SOCKET sClient = *(SOCKET*)lp;
//
//	while (1) {
//		char buff[1024] = { 0 };
//		int result = recv(sClient, buff, sizeof(buff), 0);
//		if (result > 0) {
//			std::cout << buff << std::endl;
//		}
//		else
//		{
//			std::cout << "�ͻ��˶Ͽ����ӣ�" << std::endl;
//			break;
//		}
//	}
//
//	return NULL;
//}

//����ͻ��˷�������Ϣ
void dealWithData(MsgHead * msgHead) {
	switch (msgHead->msgType) {

	case MSG_SHOW:
		std::cout << "����������" << std::endl;
		break;

	case MSG_JOIN:{
		MsgJoin* msgJoin = (MsgJoin*)msgHead;
		std::cout << "����������" << msgJoin->roomID << "������" << std::endl;
		break;
	}

	case MSG_CREATE:
		std::cout << "���󴴽�������" << std::endl;
		break;

	case MSG_ISTALK: {
		MsgIsTalk * msgIsTalk = (MsgIsTalk*)msgHead;
		std::cout << msgIsTalk->getBuff() << std::endl;
		break;
	}

	case MSG_LEAVE:
		std::cout << "�뿪����" << std::endl;
		break;

	default:
		std::cout << "��Ϣ����ʧ��" << msgHead->msgType << std::endl;
		break;
	}
}

int main() {
	SocketInit socketInit;

	//���������׽���
	SOCKET sLiten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipv4����ʽ�׽��֣�Э��

	if (sLiten == SOCKET_ERROR) {
		std::cout << "�����׽��ִ���ʧ��" << std::endl;
		return -1;
	}

	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(12306);
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;

	//���׽���
	int ret = bind(sLiten, (const sockaddr*)&sock_in, sizeof(sockaddr_in));

	if (ret == SOCKET_ERROR) {
		std::cout << "���׽���ʧ�ܣ�" << std::endl;
		closesocket(sLiten);
		return -1;
	}

	//����
	if (listen(sLiten, 10) == SOCKET_ERROR) {
		std::cout << "����ʧ��" << std::endl;
		closesocket(sLiten);
		return -1;
	}

	//selectģ��ʵ�ֶ�ͻ���
	FD_SET fd_read;//�洢SOCKET����
	FD_ZERO(&fd_read);
	FD_SET(sLiten, &fd_read);

	while (1) {
		FD_SET fd_tmp = fd_read;

		const timeval tv = { 1,0 };//�ȴ�ʱ��1s
		int ret = select(NULL, &fd_tmp, NULL, NULL, &tv);
		if (ret == 0) {
			Sleep(1);
			continue;
		}

		//��������׽����������¼�
		for (int i = 0; i < fd_tmp.fd_count; ++i) {
			if (fd_tmp.fd_array[i] == sLiten) {//����˼����׽������¼�
				sockaddr_in clientAddr;//�ͻ���
				int nlen = sizeof(sockaddr_in);

				//�ͻ�������
				SOCKET sClient = accept(sLiten, (sockaddr*)&clientAddr, &nlen);

				if (sClient == SOCKET_ERROR) {
					std::cout << "���ܿͻ���ʧ��" << std::endl;
					closesocket(sLiten);
					return -1;
				}

				std::cout << "��ͻ��˽�������" << inet_ntoa(clientAddr.sin_addr) << std::endl;

				FD_SET(sClient, &fd_read);//�ͻ��˼������
			}
			else {//�ͻ��˼������¼�
				char buff[1024] = { 0 };
				int result = recv(fd_tmp.fd_array[i], buff, sizeof(buff), 0);
				if (result > 0) {
					//std::cout << buff << std::endl;
					dealWithData((MsgHead*)buff);
				}
				else
				{
					//��fd_read���Ƴ���ǰSOCKET
					FD_CLR(fd_tmp.fd_array[i], &fd_read);

					std::cout << "�ͻ��˶Ͽ����ӣ�" << std::endl;
					break;
				}
			}
		}

		////���߳�ʵ�ֶ�ͻ���(������)
		//CreateThread(NULL, NULL, ThreadProc, (LPVOID)&sClient, NULL, NULL);
	}

	closesocket(sLiten);//�رռ���

	system("pause");

	return 0;
}