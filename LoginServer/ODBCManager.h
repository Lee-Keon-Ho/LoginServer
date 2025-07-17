#pragma once
#include "struct.h"
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "ODBCPool.h"

class CODBCManager
{
public:
	static CODBCManager* GetInstance()
	{
		static CODBCManager instance;
		return &instance;
	}

private:
	CODBCManager();
	~CODBCManager();


private:
	std::unique_ptr<CODBCPool> m_pConnectionPool;

public:
	bool Initialize(SQLWCHAR* _db);
	int SelectAccount(int& _key, const SQLWCHAR* _id, const SQLWCHAR* _pw);
	int SelectID(SQLWCHAR* _id);
	int CreateAccount(SQLWCHAR* _id, SQLWCHAR* _pw);
};