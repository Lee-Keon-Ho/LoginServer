#pragma once
#include "../NetCore/session.h"
class CFieldConnection
{
public:
	static CFieldConnection* GetInstance()
	{
		static CFieldConnection instance;
		return &instance;
	}

private:
	CFieldConnection();
	~CFieldConnection();

private:
	ACCEPT_SOCKET_INFO m_field;

public:
	void SetFieldSockeInfo(ACCEPT_SOCKET_INFO& _socket_info);

	void Send(char* _buffer, int _size);
};