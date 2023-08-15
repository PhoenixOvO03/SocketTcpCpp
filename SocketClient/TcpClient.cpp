#include"TcpClient.h"

//���ӷ�����
void TcpClient::connectServer(const char* ip, unsigned short port) {
	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);

	if (connect(sClient, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		std::cout << "���ӷ�����ʧ��" << std::endl;
	}
	else {
		std::cout << "���ӷ������ɹ�" << std::endl;
	}
}

//��������
void TcpClient::RecvData() {
	while (true) {
		char buff[1024];
		/*gets_s(buff,sizeof(buff));
		send(sClient, buff, strlen(buff),0);*/

		int ret = recv(sClient, buff, sizeof(buff), 0);

		if (ret > 0) {

		}
		else {
			printf("�ͻ��˽�������ʧ��");
		}
	}
}

//��������
void TcpClient::SendData(MsgHead* msgHead) {
	send(sClient, (const char*)msgHead, msgHead->datalen, 0);
}

//��ȡ�ͻ����׽���
SOCKET TcpClient::getSocket() {
	return sClient;
}

TcpClient::TcpClient() {
	//��ʼ���ͻ����׽���
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipv4����ʽ�׽��֣�Э��

	if (sClient == SOCKET_ERROR) {
		std::cout << "�ͻ����׽��ִ���ʧ��" << std::endl;
	}
}

TcpClient::~TcpClient() {
	closesocket(sClient);
	system("pause");
}