#include"TcpClient.h"

//连接服务器
void TcpClient::connectServer(const char* ip, unsigned short port) {
	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);

	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		std::cout << "连接服务器失败" << std::endl;
	}
	else {
		std::cout << "连接服务器成功" << std::endl;
	}
}

//接受数据
void TcpClient::RecvData() {
	while (true) {
		char buff[1024];
		/*gets_s(buff,sizeof(buff));
		send(sClient, buff, strlen(buff),0);*/

		int ret = recv(sClient, buff, sizeof(buff), 0);

		if (ret > 0) {

		}
		else {
			printf("客户端接收数据失败");
		}
	}
}

//发送数据
void TcpClient::SendData(MsgHead* msgHead) {
	send(sClient, (const char*)msgHead, msgHead->datalen, 0);
}

//获取客户端套接字
SOCKET TcpClient::getSocket() {
	return sClient;
}

TcpClient::TcpClient() {
	//初始化客户端套接字
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipv4，流式套接字，协议

	if (sClient == SOCKET_ERROR) {
		std::cout << "客户端套接字创建失败" << std::endl;
	}
}

TcpClient::~TcpClient() {
	closesocket(sClient);
	system("pause");
}