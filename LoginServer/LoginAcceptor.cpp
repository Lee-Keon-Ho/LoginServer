#include "LoginAcceptor.h"
#include "User.h"

CLoginAcceptor::CLoginAcceptor(PCSTR _ip, u_short _port)
	: CTAcceptor(_ip, _port)
{
	CTAcceptor::Start();
}

CLoginAcceptor::~CLoginAcceptor()
{
}

void CLoginAcceptor::Handle(ACCEPT_SOCKET_INFO _socket)
{
	CUser* pUser = new CUser(_socket);
}