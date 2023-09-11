#pragma once
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

class CSQLStmt
{
private:
	SQLHANDLE	m_hDbc;
	SQLHSTMT	m_hStmt;
public:
	CSQLStmt();
	~CSQLStmt();
	CSQLStmt(SQLHANDLE _hDbc);

	int FindAccount(SQLWCHAR* _id, SQLWCHAR* _pw);
};