#pragma once
#include "struct.h"
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <string>

class CODBC
{
private:
	SQLHENV		m_hEnv;
	SQLHDBC		m_hDbc;

public:
	CODBC();
	CODBC(SQLWCHAR* _dbName);
	~CODBC();

	int LoginQuery(int& _key, std::wstring _query);
	int SelectID(std::wstring _query);
	int CreateAccountQuery(std::wstring _query);
	int CharacterCount(std::wstring _query);
	void Close();
};