#include"TcpServer.h"

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

int main() {
	TcpServer tcpServer;
	tcpServer.BindServer(12306);
	tcpServer.Listen();

	while (1) {
		tcpServer.Onselect();
	}

	system("pause");

	return 0;
}