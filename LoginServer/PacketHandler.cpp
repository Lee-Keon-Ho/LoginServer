#include "User.h"
#include "../NetCore/DatabaseManager.h"
#include "PacketHandler.h"
#include "PacketType.h"
#include <assert.h>

CPacketHandler::CPacketHandler()
{
}

CPacketHandler::~CPacketHandler()
{
}

int CPacketHandler::Handle(CUser* _pUser, char* _buffer)
{
	u_short size = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	u_short type = *(u_short*)_buffer;
	_buffer += sizeof(u_short);

	assert(size > 0);

	switch (type)
	{
	case CS_PT_TEST:
		PT_C2LS_Test(_pUser, _buffer);
		break;
	case CS_PT_LOGIN:
		PT_C2LS_Login(_pUser, _buffer);
		break;
	default:
		break;
	}
	//(this->*m_lpfp[type])(_user, _buffer);
	/*
	* m_lpfp = test;
		함수포인터 구현

		원래는 switch 사용 했었음
	*/

	return size;
}

void CPacketHandler::PT_C2LS_Test(CUser* _pUser, char* _buffer)
{
	_pUser->SendPacket_Test();
}

void CPacketHandler::PT_C2LS_Login(CUser* _pUser, char* _buffer)
{
	wchar_t id[30] = {0,};
	wchar_t pw[30] = {0,};
	int id_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(id, _buffer, id_Len);
	_buffer += id_Len;
	int pw_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(pw, _buffer, pw_Len);

	int result = CDatabaseManager::GetInstance()->FindAccount(id, pw);
	// 완료 처리
}