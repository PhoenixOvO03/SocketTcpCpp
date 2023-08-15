#include"TcpServer.h"

////多线程实现多客户端
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
//			std::cout << "客户端断开连接！" << std::endl;
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