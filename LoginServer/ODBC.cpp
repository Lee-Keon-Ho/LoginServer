#include "ODBC.h"
#include <stdexcept>
#include <iostream>

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

int CODBC::LoginQuery(wstring _query)
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
	SQLINTEGER key = 0;

	SQLGetData(stmt, 1, SQL_INTEGER, &key, sizeof(SQLINTEGER), NULL);

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	if (key > 0) return key;
	return 0;
}

int CODBC::SelectID(wstring _query)
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

int CODBC::CreateAccountQuery(wstring _query)
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

int CODBC::CharacterList(wstring _query, sCharacterList& _info)
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

	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;
	SQLGetData(stmt, 1, SQL_INTEGER, &_info.name_1_Len, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 2, SQL_C_CHAR, &_info.name1, sizeof(_info.name1), NULL);
	SQLGetData(stmt, 3, SQL_INTEGER, &_info.type_1, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 4, SQL_INTEGER, &_info.type_1_level, sizeof(SQLINTEGER), NULL);
	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;
	SQLGetData(stmt, 1, SQL_INTEGER, &_info.name_2_Len, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 2, SQL_C_CHAR, &_info.name2, sizeof(_info.name1), NULL);
	SQLGetData(stmt, 3, SQL_INTEGER, &_info.type_2, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 4, SQL_INTEGER, &_info.type_2_level, sizeof(SQLINTEGER), NULL);
	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;
	SQLGetData(stmt, 1, SQL_INTEGER, &_info.name_3_Len, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 2, SQL_C_CHAR, &_info.name3, sizeof(_info.name1), NULL);
	SQLGetData(stmt, 3, SQL_INTEGER, &_info.type_3, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 4, SQL_INTEGER, &_info.type_3_level, sizeof(SQLINTEGER), NULL);

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

int CODBC::CreateCharacter(wstring _query)
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
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

int CODBC::DeleteCharacter(wstring _query)
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
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

int CODBC::SelectName(wstring _query)
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

int CODBC::InsertCharacterInfo(wstring _query)
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
	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

int CODBC::SelectCharacterInfo(wstring _query, sCharacterInfo& _characterInfo)
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
	wstring name;
	if (SQLFetch(stmt) != SQL_SUCCESS) return 0;
	SQLGetData(stmt, 1, SQL_WCHAR, &_characterInfo.name, sizeof(_characterInfo.name), NULL);
	SQLGetData(stmt, 2, SQL_INTEGER, &_characterInfo.type, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 3, SQL_INTEGER, &_characterInfo.level, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 4, SQL_INTEGER, &_characterInfo.curHp, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 5, SQL_INTEGER, &_characterInfo.maxHp, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 6, SQL_INTEGER, &_characterInfo.curMp, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 7, SQL_INTEGER, &_characterInfo.maxMp, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 8, SQL_REAL, &_characterInfo.position.x, sizeof(SQLREAL), NULL);
	SQLGetData(stmt, 9, SQL_REAL, &_characterInfo.position.y, sizeof(SQLREAL), NULL);
	SQLGetData(stmt, 10, SQL_REAL, &_characterInfo.position.z, sizeof(SQLFLOAT), NULL);
	SQLGetData(stmt, 11, SQL_INTEGER, &_characterInfo.curExp, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 12, SQL_INTEGER, &_characterInfo.damageMin, sizeof(SQLINTEGER), NULL);
	SQLGetData(stmt, 13, SQL_INTEGER, &_characterInfo.damageMax, sizeof(SQLINTEGER), NULL);

	SQLFreeHandle(SQL_HANDLE_STMT, stmt);
	return 1;
}

void CODBC::Close()
{
	SQLDisconnect(m_hDbc);
	SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}
