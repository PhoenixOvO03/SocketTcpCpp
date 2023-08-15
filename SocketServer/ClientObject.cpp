#include"ClientObject.h"

SOCKET ClientObject::getSocket() {
	return m_cs;
}

void ClientObject::setSocket(SOCKET socket) {
	m_cs = socket;
}

ClientObject::ClientObject() {
	m_cs = INVALID_SOCKET;
}

ClientObject::~ClientObject() {
	if (m_cs != INVALID_SOCKET) {
		closesocket(m_cs);
	}
}