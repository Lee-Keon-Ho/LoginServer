#pragma once
class CUser;

class CPacketHandler
{
public:
	static CPacketHandler* GetInstance()
	{
		static CPacketHandler instance;
		return &instance;
	}
private:
	CPacketHandler();
	~CPacketHandler();
public:
	int Handle(CUser* _pUser, char* _buffer);

	void PT_C2LS_Test(CUser* _pUser, char* _buffer);
	void PT_C2LS_Login(CUser* _pUser, char* _buffer);
};