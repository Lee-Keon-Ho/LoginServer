#pragma once
#include <vector>
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

	using tFunc = void (CPacketHandler::*)(CUser* _pUser, PACKET* _packet);
private:
	std::vector<tFunc> m_lpfp;

public:
	int Handle(CUser* _pUser, PACKET* _buffer);

private:
	void PT_C2LS_Test(CUser* _pUser, PACKET* _packet);
	void PT_C2LS_Login(CUser* _pUser, PACKET* _packet);
	void PT_C2LS_Check_ID(CUser* _pUser, PACKET* _packet);
	void PT_C2LS_CreateAccount(CUser* _pUser, PACKET* _packet);
	void PT_C2LS_In_Field(CUser* _pUser, PACKET* _packet);
	void PT_CSLS_Dummy_In_Field(CUser* _pUser, PACKET* _packet);
};