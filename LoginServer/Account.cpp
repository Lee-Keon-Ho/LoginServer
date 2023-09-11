#include "Account.h"
#include <iostream>
CAccount::CAccount() : m_index(0)
{
	memset(m_id, 0, MAX);
	memset(m_pw, 0, MAX);
}

CAccount::CAccount(int _index, wchar_t* _id, wchar_t* _pw) : m_index(_index)
{
	memcpy(m_id, _id, MAX);
	memcpy(m_pw, _pw, MAX);
}

CAccount::~CAccount()
{
}

wchar_t* CAccount::GetPassword()
{
	return m_pw;
}

int CAccount::GetIndex()
{
	return m_index;
}
