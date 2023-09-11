#include "SQLStmt.h"
#include <stdio.h>
#include <string>

using namespace std;

CSQLStmt::CSQLStmt() : m_hDbc(nullptr), m_hStmt(nullptr)
{
}

CSQLStmt::~CSQLStmt()
{
	SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
}

CSQLStmt::CSQLStmt(SQLHANDLE _hDbc) : m_hDbc(_hDbc), m_hStmt(nullptr)
{
}

int CSQLStmt::FindAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt) != SQL_SUCCESS)
	{
		printf("SQLHSTMT ERROR\n");
		return 0;
	}
	wstring str = L"select number from userInfo where id = '"; 
	str += _id + wstring(L"' and pw ='") + _pw + wstring(L"'");
	SQLWCHAR* sql = _wcsdup(str.c_str());
	
	SQLRETURN ret = SQLExecDirectW(m_hStmt, sql, SQL_NTS);

	if (ret == SQL_SUCCESS)
	{
		
		if(SQLFetch(m_hStmt) == SQL_SUCCESS)
		{
			SQLINTEGER index;

			SQLGetData(m_hStmt, 1, SQL_INTEGER, &index, sizeof(SQLINTEGER), NULL);

			return index;
		}
	}

	return 0;
	// 완료 후 처리 반환
}
