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

void CPrivateAcceptor::Handle(ACCEPT_SOCKET_INFO& _info) // ¼öÁ¤
{
	CFieldConnection::GetInstance()->SetFieldSockeInfo(_info);
}
