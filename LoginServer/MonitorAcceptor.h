#pragma once
#include "../NetCore/TAcceptor.h"

class CMonitorAcceptor : public CTAcceptor
{
public:
	CMonitorAcceptor(PCSTR _ip, u_short _port);
	~CMonitorAcceptor();

	void Handle(ACCEPT_SOCKET_INFO& _info) override;
};