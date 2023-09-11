#pragma once
#include "../NetCore/session.h"

class CUser : public CSession
{
public:
	CUser();
	CUser(ACCEPT_SOCKET_INFO _socketInfo);
	~CUser();

	int PacketHandle() override;

	void SendPacket_Test();
};