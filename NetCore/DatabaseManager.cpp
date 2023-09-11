#include "DatabaseManager.h"
#include "SQLStmt.h"
CDatabaseManager::CDatabaseManager()
{
}

CDatabaseManager::~CDatabaseManager()
{
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}

bool CDatabaseManager::Initialize(SQLWCHAR* _db)
{
	// ODBC ȯ�� �ڵ� ����
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) return false;
	
	// ODBC ���� ����
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS) return false;
	
	// DB ���� �ڵ� ����
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS) return false;


	// DB�� ����
	if (SQLConnectW(m_hDbc, _db, SQL_NTS, nullptr, SQL_NTS, nullptr, SQL_NTS) == SQL_ERROR) return false;


	return true;
}

int CDatabaseManager::FindAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
	CSQLStmt stmt(m_hDbc); // ����ȭ �κ��� �־�����ϰ�
	return stmt.FindAccount(_id, _pw);
}