#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>

#include"../SocketInit/SocketInit.hpp"
#include"../Message/msgType.hpp"

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

//处理客户端发来的消息
void dealWithData(MsgHead * msgHead) {
	switch (msgHead->msgType) {

	case MSG_SHOW:
		std::cout << "请求聊天室" << std::endl;
		break;

	case MSG_JOIN:{
		MsgJoin* msgJoin = (MsgJoin*)msgHead;
		std::cout << "加入聊天室" << msgJoin->roomID << "聊天室" << std::endl;
		break;
	}

	case MSG_CREATE:
		std::cout << "请求创建聊天室" << std::endl;
		break;

	case MSG_ISTALK: {
		MsgIsTalk * msgIsTalk = (MsgIsTalk*)msgHead;
		std::cout << msgIsTalk->getBuff() << std::endl;
		break;
	}

	case MSG_LEAVE:
		std::cout << "离开聊天" << std::endl;
		break;

	default:
		std::cout << "消息解析失败" << msgHead->msgType << std::endl;
		break;
	}
}

int main() {
	SocketInit socketInit;

	//创建监听套接字
	SOCKET sLiten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipv4，流式套接字，协议

	if (sLiten == SOCKET_ERROR) {
		std::cout << "监听套接字创建失败" << std::endl;
		return -1;
	}

	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(12306);
	sock_in.sin_addr.S_un.S_addr = INADDR_ANY;

	//绑定套接字
	int ret = bind(sLiten, (const sockaddr*)&sock_in, sizeof(sockaddr_in));

	if (ret == SOCKET_ERROR) {
		std::cout << "绑定套接字失败！" << std::endl;
		closesocket(sLiten);
		return -1;
	}

	//监听
	if (listen(sLiten, 10) == SOCKET_ERROR) {
		std::cout << "监听失败" << std::endl;
		closesocket(sLiten);
		return -1;
	}

	//select模型实现多客户端
	FD_SET fd_read;//存储SOCKET对象
	FD_ZERO(&fd_read);
	FD_SET(sLiten, &fd_read);

	while (1) {
		FD_SET fd_tmp = fd_read;

		const timeval tv = { 1,0 };//等待时间1s
		int ret = select(NULL, &fd_tmp, NULL, NULL, &tv);
		if (ret == 0) {
			Sleep(1);
			continue;
		}

		//如果监听套接字有网络事件
		for (int i = 0; i < fd_tmp.fd_count; ++i) {
			if (fd_tmp.fd_array[i] == sLiten) {//服务端监听套接字有事件
				sockaddr_in clientAddr;//客户端
				int nlen = sizeof(sockaddr_in);

				//客户端连接
				SOCKET sClient = accept(sLiten, (sockaddr*)&clientAddr, &nlen);

				if (sClient == SOCKET_ERROR) {
					std::cout << "接受客户端失败" << std::endl;
					closesocket(sLiten);
					return -1;
				}

				std::cout << "与客户端建立连接" << inet_ntoa(clientAddr.sin_addr) << std::endl;

				FD_SET(sClient, &fd_read);//客户端加入监听
			}
			else {//客户端监听有事件
				char buff[1024] = { 0 };
				int result = recv(fd_tmp.fd_array[i], buff, sizeof(buff), 0);
				if (result > 0) {
					//std::cout << buff << std::endl;
					dealWithData((MsgHead*)buff);
				}
				else
				{
					//从fd_read中移除当前SOCKET
					FD_CLR(fd_tmp.fd_array[i], &fd_read);

					std::cout << "客户端断开连接！" << std::endl;
					break;
				}
			}
		}

		////多线程实现多客户端(不常用)
		//CreateThread(NULL, NULL, ThreadProc, (LPVOID)&sClient, NULL, NULL);
	}

	closesocket(sLiten);//关闭监听

	system("pause");

	return 0;
}