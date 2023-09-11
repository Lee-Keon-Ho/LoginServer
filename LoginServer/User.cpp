#include "User.h"
#include "PacketHandler.h"
#include "PacketStruct.h"

CUser::CUser()
{
}

CUser::CUser(ACCEPT_SOCKET_INFO _socketInfo) :
	CSession(_socketInfo)
{
	char* packet = new char[4];
	memset(packet, 0, 4);
	send(m_socket_info.socket, packet, 4, 0);
	delete[] packet;
}

CUser::~CUser()
{
}

int CUser::PacketHandle()
{
	char* readBuffer = GetPacketBuffer();
	if (readBuffer == nullptr) return 0;

	int readSize = CPacketHandler::GetInstance()->Handle(this, readBuffer);

	if (readSize > 0)
	{
		m_ringBuffer->Read(readSize);
		return readSize;
	}

	return 0;
}

void CUser::SendPacket_Test()
{
	PACKET packet(sizeof(PACKET), 0);

	Send(reinterpret_cast<char*>(&packet), sizeof(PACKET));
}
