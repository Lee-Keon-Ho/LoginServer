#include "User.h"
#include "PacketHandler.h"
#include "PacketStruct.h"
#include "ODBCManager.h"
#include "PacketType.h"
#include "FieldConnection.h"
#include <assert.h>

CPacketHandler::CPacketHandler()
{
	m_lpfp = new tFunc[FUNC_MAX];

	m_lpfp[CS_PT_TEST] = &CPacketHandler::PT_C2LS_Test;
	m_lpfp[CS_PT_LOGIN] = &CPacketHandler::PT_C2LS_Login;
	m_lpfp[CS_PT_CHECK_ID] = &CPacketHandler::PT_C2LS_Check_ID;
	m_lpfp[CS_PT_CREATE_ACCOUNT] = &CPacketHandler::PT_C2LS_CreateAccount;
	m_lpfp[CS_PT_CREATE_CHARACTER] = &CPacketHandler::PT_C2LS_CreateCharacter;
	m_lpfp[CS_PT_DELETE_CHARACTER] = &CPacketHandler::PT_C2LS_DeleteCharacter;
	m_lpfp[CS_PT_IN_FIELD] = &CPacketHandler::PT_C2LS_In_Field;
	m_lpfp[CS_PT_DOUBLE_CHECK] = &CPacketHandler::PT_C2LS_DoubleCheck;
}

CPacketHandler::~CPacketHandler()
{
	if (m_lpfp != nullptr) { delete m_lpfp; m_lpfp = nullptr; }
}

int CPacketHandler::Handle(CUser* _pUser, char* _buffer)
{
	u_short size = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	u_short type = *(u_short*)_buffer;
	_buffer += sizeof(u_short);

	assert(size > 0);

	(this->*m_lpfp[type])(_pUser, _buffer);

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

	int ret = CODBCManager::GetInstance()->SelectAccount(id, pw);
	
	PACKET_LOGIN packet(sizeof(PACKET_LOGIN), CS_PT_LOGIN, static_cast<u_short>(ret));

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_LOGIN));

	if (ret <= 0) return;
	_pUser->SetInfo(id);

	sCharacterList info;

	CODBCManager::GetInstance()->SelectCharacterList(id, info);

	PACKET_CHARACTERLIST characterPacket(sizeof(PACKET_CHARACTERLIST), CS_PT_CHARACTERLIST, static_cast<u_short>(ret), info);
	_pUser->Send(reinterpret_cast<char*>(&characterPacket), sizeof(PACKET_CHARACTERLIST));
}

void CPacketHandler::PT_C2LS_Check_ID(CUser* _pUser, char* _buffer)
{
	wchar_t id[30] = { 0, };
	int id_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(id, _buffer, id_Len);

	int ret = CODBCManager::GetInstance()->SelectID(id);

	PACKET_CREATE_ACCOUNT packet(sizeof(PACKET_CREATE_ACCOUNT), CS_PT_CHECK_ID, static_cast<u_short>(ret));

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_CREATE_ACCOUNT));
}

void CPacketHandler::PT_C2LS_CreateAccount(CUser* _pUser, char* _buffer)
{
	wchar_t id[30] = { 0, };
	wchar_t pw[30] = { 0, };
	int id_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(id, _buffer, id_Len);
	_buffer += id_Len;
	int pw_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(pw, _buffer, pw_Len);

	int ret = CODBCManager::GetInstance()->CreateAccount(id, pw);

	PACKET_CREATE_ACCOUNT packet(sizeof(PACKET_CREATE_ACCOUNT), CS_PT_CREATE_ACCOUNT, static_cast<u_short>(ret));

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_CREATE_ACCOUNT));
}

void CPacketHandler::PT_C2LS_CreateCharacter(CUser* _pUser, char* _buffer)
{
	int type = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	int nameLen = *(u_short*)_buffer;
	_buffer += sizeof(u_short);

	wchar_t name[16] = { 0, };
	memcpy(name, _buffer, nameLen);

	sCharacterList info;
	CODBCManager* pODBCManager = CODBCManager::GetInstance();

	int ret = pODBCManager->CreateCharacter(_pUser->GetId(), name, type);
	if (ret <= 0) return;
	ret = pODBCManager->SelectCharacterList(_pUser->GetId(), info);

	PACKET_CHARACTERLIST packet(sizeof(PACKET_CHARACTERLIST), CS_PT_UPDATE_CHARACTERLIST, static_cast<u_short>(ret), info);

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_CHARACTERLIST));
}

void CPacketHandler::PT_C2LS_DeleteCharacter(CUser* _pUser, char* _buffer)
{
	int nameLen = *(u_short*)_buffer;
	_buffer += sizeof(u_short);

	wchar_t name[28] = { 0, };
	memcpy(name, _buffer, nameLen);

	int ret;

	sCharacterList info;
	CODBCManager* pODBCManager = CODBCManager::GetInstance();

	ret = pODBCManager->DeleteCharacter(_pUser->GetId(), name);
	if (ret <= 0) return;
	ret = pODBCManager->SelectCharacterList(_pUser->GetId(), info);

	PACKET_CHARACTERLIST packet(sizeof(PACKET_CHARACTERLIST), CS_PT_UPDATE_CHARACTERLIST, static_cast<u_short>(ret), info);

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_CHARACTERLIST));
}

void CPacketHandler::PT_C2LS_In_Field(CUser* _pUser, char* _buffer)
{
	// ODBC에서 key값으로 캐릭터 정보를 받아와서 
	int len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);

	wchar_t name[28] = { 0, };
	memcpy(name, _buffer, len);

	sCharacterInfo characterInfo;
	int ret = CODBCManager::GetInstance()->SelectCharacterInfo(name, characterInfo);

	if (ret <= 0) return;

	PACKET_FS_IN_FIELD FSPacket(sizeof(PACKET_FS_IN_FIELD), 0, sizeof(characterInfo.name), characterInfo);

	CFieldConnection::GetInstance()->Send(reinterpret_cast<char*>(&FSPacket), sizeof(PACKET_FS_IN_FIELD));

	PACKET_IN_FIELD packet(sizeof(PACKET_IN_FIELD), CS_PT_IN_FIELD, len, characterInfo.name);
	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_IN_FIELD));
}

void CPacketHandler::PT_C2LS_DoubleCheck(CUser* _pUser, char* _buffer)
{
	wchar_t name[28] = { 0, };
	int name_Len = *(u_short*)_buffer;
	_buffer += sizeof(u_short);
	memcpy(name, _buffer, name_Len);
	_buffer += name_Len;

	int ret = CODBCManager::GetInstance()->DoubleCheck(name);
	// 중복이면 1 중복이 아니면 0을 리턴한다.
	PACKET_DOUBLE_CHECK packet(sizeof(PACKET_DOUBLE_CHECK), CS_PT_DOUBLE_CHECK, static_cast<u_short>(ret));

	_pUser->Send(reinterpret_cast<char*>(&packet), sizeof(PACKET_DOUBLE_CHECK));
}