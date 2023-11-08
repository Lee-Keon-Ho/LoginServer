#pragma once

#define FUNC_MAX 8

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

	typedef void (CPacketHandler::* tFunc)(CUser* _user, char* _buffer);
private:
	tFunc* m_lpfp;

public:
	int Handle(CUser* _pUser, char* _buffer);

private:
	void PT_C2LS_Test(CUser* _pUser, char* _buffer);
	void PT_C2LS_Login(CUser* _pUser, char* _buffer);
	void PT_C2LS_Check_ID(CUser* _pUser, char* _buffer);
	void PT_C2LS_CreateAccount(CUser* _pUser, char* _buffer);
	void PT_C2LS_CreateCharacter(CUser* _pUser, char* _buffer);
	void PT_C2LS_DeleteCharacter(CUser* _pUser, char* _buffer);
	void PT_C2LS_In_Field(CUser* _pUser, char* _buffer);
	void PT_C2LS_DoubleCheck(CUser* _pUser, char* _buffer);
};