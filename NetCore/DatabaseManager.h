#pragma once
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <map>

using namespace std;

class CDatabaseManager
{
public:
	static CDatabaseManager* GetInstance()
	{
		static CDatabaseManager instance;
		return &instance;
	}

private:
	CDatabaseManager();
	~CDatabaseManager();

private:
	SQLHENV		m_hEnv;
	SQLHDBC		m_hDbc;

public:
	bool Initialize(SQLWCHAR* _db);
	int FindAccount(SQLWCHAR* _id, SQLWCHAR* _pw);
};