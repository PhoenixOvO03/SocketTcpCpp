#pragma once

enum MSG_TYPE {
	MSG_SHOW,
	MSG_JOIN,
	MSG_CREATE,
	MSG_ISTALK,
	MSG_LEAVE
};

class MsgHead{//消息基类
public:
	int msgType;//消息类型
	int datalen;//消息长度
};

class MsgShow :public MsgHead {
public:
	MsgShow() {
		msgType = MSG_SHOW;
		datalen = sizeof(MsgShow);
	}
};

class MsgJoin :public MsgHead {
public:
	int roomID;
	MsgJoin(int ID) {
		msgType = MSG_JOIN;
		datalen = sizeof(MsgJoin);
		roomID = ID;
	}
};

class MsgCreate :public MsgHead {
public:
	MsgCreate() {
		msgType = MSG_CREATE;
		datalen = sizeof(MsgCreate);
	}
};

class MsgIsTalk :public MsgHead {
private:
	char buff[512];
public:
	MsgIsTalk() {
		msgType = MSG_ISTALK;
		datalen = sizeof(MsgIsTalk);
	}

	char* getBuff() {
		return buff;
	}
};

class MsgLeave :public MsgHead {
public:
	MsgLeave() {
		msgType = MSG_LEAVE;
		datalen = sizeof(MsgLeave);
	}
};