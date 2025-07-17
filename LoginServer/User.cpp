#include "User.h"
#include "PacketHandler.h"
#include "PacketStruct.h"
#include "UserManager.h"

CUser::CUser()
{
}

CUser::CUser(ACCEPT_SOCKET_INFO& _socketInfo) :
	CSession(_socketInfo), m_id(nullptr)
{
	m_id = std::make_unique<wchar_t[]>(id_max_size);

	LKH::sharedPtr<PACKET> packet = new PACKET(sizeof(PACKET), 0);
	Send(packet, sizeof(PACKET));
}

CUser::~CUser()
{
}

int CUser::PacketHandle()
{
	char* readBuffer = GetPacketBuffer();
	if (readBuffer == nullptr) return 0;

	int readSize = CPacketHandler::GetInstance()->Handle(this, reinterpret_cast<PACKET*>(readBuffer));

	if (readSize > 0)
	{
		m_ringBuffer->Read(readSize);
		return readSize;
	}

	return 0;
}

void CUser::Delete()
{
	CUserManager::GetInstance()->Del(m_id.get());
}

void CUser::SetInfo(const wchar_t* _id)
{
	memcpy(m_id.get(), _id, sizeof(wchar_t) * id_max_size);
}

void CUser::SendPacket_Test()
{
	LKH::sharedPtr<PACKET> packet = new PACKET(sizeof(PACKET), 0);

	Send(packet, sizeof(PACKET));
}

wchar_t* CUser::GetId()
{
	return m_id.get();
}

int& CUser::GetKey()
{
	return m_key;
}
