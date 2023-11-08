#include "FieldConnection.h"
#include <iostream>

using namespace std;

CFieldConnection::CFieldConnection()
{
}

CFieldConnection::~CFieldConnection()
{
}

void CFieldConnection::SetFieldSockeInfo(ACCEPT_SOCKET_INFO& _socket_info)
{
	m_field = _socket_info;
}

void CFieldConnection::Send(char* _buffer, int _size)
{
	int sendSize = send(m_field.socket, _buffer, _size, 0);
	if (sendSize < 0)
	{
		cout << "send Error";
	}
}