#include "ODBC.h"
#include <stdexcept>
#include <iostream>
#include <codecvt>
CODBC::CODBC() :
	m_hEnv(nullptr),
	m_hDbc(nullptr)
{
}

CODBC::CODBC(SQLWCHAR* _dbName) :
	m_hEnv(nullptr), 
	m_hDbc(nullptr)
{
	// ODBC 환경 핸들 생성
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv) != SQL_SUCCESS)
	{
		throw std::runtime_error("SQLAlloc Error");
	}

	// ODBC 버전 설정
	if (SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0) != SQL_SUCCESS)
	{
		throw std::runtime_error("SQLEnv Error");
	}

	// DB 연결 핸들 생성
	if (SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc) != SQL_SUCCESS)
	{
		throw std::runtime_error("DB Handle Error");
	}

	// DB에 연결
	if (SQLConnectW(m_hDbc, _dbName, SQL_NTS, nullptr, SQL_NTS, nullptr, SQL_NTS) == SQL_ERROR)
	{
		throw std::runtime_error("DB connect Error");
	}
}

CODBC::~CODBC()
{
}

int CODBC::LoginQuery(int& _key, std::wstring _query)
{
	SQLHSTMT stmt;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &stmt) != SQL_SUCCESS)
	{
		// 오류 처리
	}
	if (SQLExecDirectW(stmt, (SQLWCHAR*)_query.c_str(), SQL_NTS) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return 0;
	}
	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;

	SQLGetData(stmt, 1, SQL_INTEGER, &_key, sizeof(SQLINTEGER), NULL);

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	if (_key > 0) return _key;
	return 0;
}

int CODBC::SelectID(std::wstring _query)
{
	SQLHSTMT stmt;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &stmt) != SQL_SUCCESS)
	{
		// 오류 처리
	}
	if (SQLExecDirectW(stmt, (SQLWCHAR*)_query.c_str(), SQL_NTS) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return 0;
	}
	if (SQLFetch(stmt) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return 0;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

int CODBC::CreateAccountQuery(std::wstring _query)
{
	SQLHSTMT stmt;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &stmt) != SQL_SUCCESS)
	{
		// 오류 처리
	}
	if (SQLExecDirectW(stmt, (SQLWCHAR*)_query.c_str(), SQL_NTS) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return 0;
	}
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	
	return 1;
}

int CODBC::CharacterCount(std::wstring _query)
{
	SQLHSTMT stmt;
	if (SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &stmt) != SQL_SUCCESS)
	{
		return 0;
	}
	if (SQLExecDirectW(stmt, (SQLWCHAR*)_query.c_str(), SQL_NTS) != SQL_SUCCESS)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, stmt);
		return 0;
	}
	
	int ret;
	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;
	SQLGetData(stmt, 1, SQL_INTEGER, &ret, sizeof(SQLINTEGER), NULL);
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return ret;
}

void CODBC::Close()
{
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}
