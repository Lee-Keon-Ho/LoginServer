#pragma once
#include "struct.h"
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

using namespace std;

class CODBC
{
private:
	SQLHENV		m_hEnv;
	SQLHDBC		m_hDbc;

public:
	CODBC();
	CODBC(SQLWCHAR* _dbName);
	~CODBC();

	int LoginQuery(wstring _query);
	int SelectID(wstring _query);
	int CreateAccountQuery(wstring _query);
	int CharacterList(wstring _query, sCharacterList& _info);
	int CreateCharacter(wstring _query);
	int DeleteCharacter(wstring _query);
	int SelectName(wstring _query);
	int InsertCharacterInfo(wstring _query);
	int SelectCharacterInfo(wstring _query, sCharacterInfo& _characterInfo);
	void Close();
};