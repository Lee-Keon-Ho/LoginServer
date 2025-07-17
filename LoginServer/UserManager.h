#pragma once
#include "User.h"
#include "../NetCore/Lock.h"
#include <map>

class CUserManager
{
public:
	static CUserManager* GetInstance()
	{
		static CUserManager instance;
		return &instance;
	}

private:
	CUserManager();
	~CUserManager();

public:
	using UserList = std::map<std::wstring, CUser*>;

private:
	UserList m_userList;

	PSRWLOCK m_lock;
public:
	void Add(std::wstring _key, CUser* _pUser);
	void Del(std::wstring _key);
	void Find(std::wstring _key);

	int GetUserSize();
};