#include"TcpClient.h"

//指令线程
DWORD WINAPI TreadProc(LPVOID lp) {
	TcpClient sClient = *(TcpClient*)lp;

	while (true) {
		std::cout << "show join create talk exit" << std::endl;
		
		char buff[1024] = { 0 };
		gets_s(buff, sizeof(buff));

		if (strcmp(buff, "show") == 0) {//显示聊天室
			MsgShow msgShow;
			//send(sClient, (const char*)&msgShow, msgShow.datalen, 0);
			sClient.SendData(&msgShow);
		}
		else if (strncmp(buff, "join", strlen("join")) == 0) {//加入聊天室
			int r = atoi(buff + strlen("join"));
			MsgJoin msgJoin(r);
			//send(sClient, (const char*)&msgJoin, msgJoin.datalen, 0);
			sClient.SendData(&msgJoin);
		}
		else if (strcmp(buff, "create") == 0) {//创建聊天室

		}
		else if (strcmp(buff, "talk") == 0) {//聊天
			std::cout << "开始聊天" << std::endl;
			MsgIsTalk msgIsTalk;

			while (true) {
				//gets_s(msgIsTalk.getBuff(), sizeof(msgIsTalk.getBuff()));
				std::cin >> msgIsTalk.getBuff();

				if (strcmp(msgIsTalk.getBuff(), "leave") == 0) {
					std::cout << "结束聊天" << std::endl;
					MsgLeave msgLeave;
					//send(sClient, (const char*)&msgLeave, msgLeave.datalen, 0);
					sClient.SendData(&msgLeave);
					break;
				}

				//send(sClient, (const char*)&msgIsTalk, msgIsTalk.datalen, 0);
				sClient.SendData(&msgIsTalk);
			}
		}
		else if (strcmp(buff, "exit") == 0) {//退出
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

	//多线程实现收发数据分离
	//发送指令
	HANDLE h = CreateThread(0, 0, TreadProc, (LPVOID)&tcpClient, 0, 0);

	//收数据
	

	WaitForSingleObject(h, INFINITE);

	return 0;
}