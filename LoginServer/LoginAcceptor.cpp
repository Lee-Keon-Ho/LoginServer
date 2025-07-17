#include "LoginAcceptor.h"
#include "User.h"
#include <memory>

CLoginAcceptor::CLoginAcceptor(PCSTR _ip, u_short _port)
	: CTAcceptor(_ip, _port)
{
	CTAcceptor::Start();
}

CLoginAcceptor::~CLoginAcceptor()
{
}

void CLoginAcceptor::Handle(ACCEPT_SOCKET_INFO& _info)
{
	// 2023-12-22 ¼öÁ¤.
	CUser* pUser = new CUser(_info);
	//std::unique_ptr<CUser> pUser = std::make_unique<CUser>(_socket);
}