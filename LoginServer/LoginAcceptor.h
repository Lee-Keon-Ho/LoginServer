#pragma once
#include "../NetCore/TAcceptor.h"

class CLoginAcceptor : public CTAcceptor
{
public:
	CLoginAcceptor(PCSTR _ip, u_short _port);
	~CLoginAcceptor();

	void Handle(ACCEPT_SOCKET_INFO& _info) override;
};