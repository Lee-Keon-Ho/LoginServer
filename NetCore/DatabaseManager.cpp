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
	// ODBC 환경 핸들 생성
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS) return false;
	
	// ODBC 버전 설정
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS) return false;
	
	// DB 연결 핸들 생성
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS) return false;


	// DB에 연결
	if (SQLConnectW(m_hDbc, _db, SQL_NTS, nullptr, SQL_NTS, nullptr, SQL_NTS) == SQL_ERROR) return false;


	return true;
}

int CDatabaseManager::FindAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
	CSQLStmt stmt(m_hDbc); // 동기화 부분을 넣어줘야하고
	return stmt.FindAccount(_id, _pw);
}