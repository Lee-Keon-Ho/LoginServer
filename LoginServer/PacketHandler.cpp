#include "User.h"
#include "PacketHandler.h"
#include "PacketStruct.h"
#include "ODBCManager.h"
#include "PacketType.h"
#include "FieldConnection.h"
#include "UserManager.h"
#include <assert.h>

CPacketHandler::CPacketHandler()
{
	m_lpfp.reserve(static_cast<u_short>(ePacketType::CS_PT_MAX));
	m_lpfp.push_back(&CPacketHandler::PT_C2LS_Test);
	m_lpfp.push_back(&CPacketHandler::PT_C2LS_Login);
	m_lpfp.push_back(&CPacketHandler::PT_C2LS_Check_ID);
	m_lpfp.push_back(&CPacketHandler::PT_C2LS_CreateAccount);
	m_lpfp.push_back(&CPacketHandler::PT_C2LS_In_Field);
	m_lpfp.push_back(&CPacketHandler::PT_CSLS_Dummy_In_Field);
}

CPacketHandler::~CPacketHandler()
{
}

int CPacketHandler::Handle(CUser* _pUser, PACKET* _packet)
{
	(this->*m_lpfp[_packet->type])(_pUser, _packet);

	return _packet->size;
}

void CPacketHandler::PT_C2LS_Test(CUser* _pUser, PACKET* _packet)
{
	_pUser->SendPacket_Test();
}

void CPacketHandler::PT_C2LS_Login(CUser* _pUser, PACKET* _packet)
{
	C2LS_LOGIN* buffer = reinterpret_cast<C2LS_LOGIN*>(_packet);
	
	int ret = CODBCManager::GetInstance()->SelectAccount(_pUser->GetKey(), buffer->id, buffer->pw);

	if (ret != 0)
	{
		LKH::sharedPtr<PACKET> WSPacket = new LS2WS_PACKET(static_cast<u_short>(_pUser->GetKey()));

		CFieldConnection::GetInstance()->Send(WSPacket, WSPacket.get()->size); // world

		_pUser->SetInfo(buffer->id);
	}

	LKH::sharedPtr<PACKET> packet = new PACKET_LOGIN(static_cast<u_short>(ret), static_cast<u_short>(_pUser->GetKey()), buffer->id);
	_pUser->Send(packet, sizeof(PACKET_LOGIN));
}

void CPacketHandler::PT_C2LS_Check_ID(CUser* _pUser, PACKET* _packet)
{
	C2LS_CHECK_ID* buffer = reinterpret_cast<C2LS_CHECK_ID*>(_packet);

	int ret = CODBCManager::GetInstance()->SelectID(buffer->id);

	LKH::sharedPtr<PACKET> packet = new PACKET_CHECK_ID(static_cast<u_short>(ret));

	_pUser->Send(packet, sizeof(PACKET_CHECK_ID));
}

void CPacketHandler::PT_C2LS_CreateAccount(CUser* _pUser, PACKET* _packet)
{
	C2LS_CREATE_ACCOUNT* buffer = reinterpret_cast<C2LS_CREATE_ACCOUNT*>(_packet);

	int ret = CODBCManager::GetInstance()->CreateAccount(buffer->id, buffer->pw);

	LKH::sharedPtr<PACKET> packet = new PACKET_CREATE_ACCOUNT(static_cast<u_short>(ret));

	_pUser->Send(packet, sizeof(PACKET_CREATE_ACCOUNT));
}


void CPacketHandler::PT_C2LS_In_Field(CUser* _pUser, PACKET* _packet)
{
	C2LS_IN_FIELD* buffer = reinterpret_cast<C2LS_IN_FIELD*>(_packet);

	sCharacterInfo characterInfo;
	int ret = 0;// CODBCManager::GetInstance()->SelectCharacterInfo(buffer->name, characterInfo);

	CUserManager::GetInstance()->Add(buffer->name, _pUser);

	LKH::sharedPtr<PACKET> FSPacket = new PACKET_LS2FS_IN_FIELD(sizeof(characterInfo.name), characterInfo);

	CFieldConnection::GetInstance()->Send(FSPacket, sizeof(PACKET_LS2FS_IN_FIELD));
	
	/*LKH::sharedPtr<PACKET> packet = new PACKET_IN_FIELD(characterInfo.name);
	_pUser->Send(packet, sizeof(PACKET_IN_FIELD));*/
}



void CPacketHandler::PT_CSLS_Dummy_In_Field(CUser* _pUser, PACKET* _packet)
{
	//C2LS_DUMMY_IN_FIELD* packet = reinterpret_cast<C2LS_DUMMY_IN_FIELD*>(_packet);

	//sCharacterInfo characterInfo;
	//int ret = 0;// CODBCManager::GetInstance()->SelectCharacterInfo(packet->name, characterInfo);
	//characterInfo.position = packet->position;

	//CUserManager::GetInstance()->Add(packet->name, _pUser);

	//LKH::sharedPtr<PACKET> FSPacket = new PACKET_LS2FS_IN_FIELD(sizeof(characterInfo.name), characterInfo);

	//CFieldConnection::GetInstance()->Send(FSPacket, sizeof(PACKET_LS2FS_IN_FIELD));

	//LKH::sharedPtr<PACKET> C2Packet = new PACKET_IN_FIELD(characterInfo.name);
	//_pUser->Send(C2Packet, sizeof(PACKET_IN_FIELD));
}
