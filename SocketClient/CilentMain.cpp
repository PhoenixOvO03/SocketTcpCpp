#include"TcpClient.h"

//ָ���߳�
DWORD WINAPI TreadProc(LPVOID lp) {
	TcpClient sClient = *(TcpClient*)lp;

	while (true) {
		std::cout << "show join create talk exit" << std::endl;
		
		char buff[1024] = { 0 };
		gets_s(buff, sizeof(buff));

		if (strcmp(buff, "show") == 0) {//��ʾ������
			MsgShow msgShow;
			//send(sClient, (const char*)&msgShow, msgShow.datalen, 0);
			sClient.SendData(&msgShow);
		}
		else if (strncmp(buff, "join", strlen("join")) == 0) {//����������
			int r = atoi(buff + strlen("join"));
			MsgJoin msgJoin(r);
			//send(sClient, (const char*)&msgJoin, msgJoin.datalen, 0);
			sClient.SendData(&msgJoin);
		}
		else if (strcmp(buff, "create") == 0) {//����������

		}
		else if (strcmp(buff, "talk") == 0) {//����
			std::cout << "��ʼ����" << std::endl;
			MsgIsTalk msgIsTalk;

			while (true) {
				//gets_s(msgIsTalk.getBuff(), sizeof(msgIsTalk.getBuff()));
				std::cin >> msgIsTalk.getBuff();

				if (strcmp(msgIsTalk.getBuff(), "leave") == 0) {
					std::cout << "��������" << std::endl;
					MsgLeave msgLeave;
					//send(sClient, (const char*)&msgLeave, msgLeave.datalen, 0);
					sClient.SendData(&msgLeave);
					break;
				}

				//send(sClient, (const char*)&msgIsTalk, msgIsTalk.datalen, 0);
				sClient.SendData(&msgIsTalk);
			}
		}
		else if (strcmp(buff, "exit") == 0) {//�˳�
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
	TcpClient tcpClient;
	tcpClient.connectServer("10.128.81.74", 12306);

	//���߳�ʵ���շ����ݷ���
	//����ָ��
	HANDLE h = CreateThread(0, 0, TreadProc, (LPVOID)&tcpClient, 0, 0);

	//������
	

	WaitForSingleObject(h, INFINITE);

	return 0;
}