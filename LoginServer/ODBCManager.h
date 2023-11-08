#pragma once
#include "struct.h"
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "ODBCPool.h"

using namespace std;

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
	CODBCPool* m_connectionPool;

public:
	bool Initialize(SQLWCHAR* _db);
	int SelectAccount(SQLWCHAR* _id, SQLWCHAR* _pw);
	int SelectID(SQLWCHAR* _id);
	int CreateAccount(SQLWCHAR* _id, SQLWCHAR* _pw);
	int CharacterInfo(int _key, sCharacterList& _info);
	int SelectCharacterList(wchar_t* _id, sCharacterList& _info);
	int CreateCharacter(wchar_t* _id, wchar_t* _name, int _type);
	int DeleteCharacter(wchar_t* _id, wchar_t* _name);
	int DoubleCheck(wchar_t* _name);
	int SelectCharacterInfo(wchar_t* _name, sCharacterInfo& _characterInfo);
};