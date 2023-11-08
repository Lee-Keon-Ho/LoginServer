#pragma once
#include "../NetCore/session.h"

class CUser : public CSession
{
private:
	wchar_t* m_id;
public:
	CUser();
	CUser(ACCEPT_SOCKET_INFO _socketInfo);
	~CUser();

	int PacketHandle() override;

	void SetInfo(wchar_t* _id);

	void SendPacket_Test();
	wchar_t* GetId();
};