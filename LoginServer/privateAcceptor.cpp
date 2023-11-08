#include "privateAcceptor.h"
#include "FieldConnection.h"
CPrivateAcceptor::CPrivateAcceptor(PCSTR _ip, u_short _port) :
	CTAcceptor(_ip, _port)
{
	CTAcceptor::Start();
}

CPrivateAcceptor::~CPrivateAcceptor()
{
}

void CPrivateAcceptor::Handle(ACCEPT_SOCKET_INFO _socket)
{
	CFieldConnection::GetInstance()->SetFieldSockeInfo(_socket);
}
