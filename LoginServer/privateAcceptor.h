#pragma once
#include "../NetCore/TAcceptor.h"

class CPrivateAcceptor : public CTAcceptor
{
public:
	CPrivateAcceptor(PCSTR _ip, u_short _port);
	~CPrivateAcceptor();

	void Handle(ACCEPT_SOCKET_INFO _socket) override;
};