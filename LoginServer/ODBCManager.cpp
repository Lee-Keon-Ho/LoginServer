#include "ODBCManager.h"
#include <assert.h>
CODBCManager::CODBCManager() : m_pConnectionPool(nullptr)
{
}

CODBCManager::~CODBCManager()
{
}

bool CODBCManager::Initialize(SQLWCHAR* _db)
{
	if (!m_pConnectionPool) m_pConnectionPool = std::make_unique<CODBCPool>(_db, 10);
    assert(m_pConnectionPool != nullptr);
    return true;
}

int CODBCManager::SelectAccount(int& _key, const SQLWCHAR* _id, const SQLWCHAR* _pw)
{
    std::string id;
    std::unique_ptr<CODBC> conn = m_pConnectionPool->GetConnection();
    std::wstring str = L"select number from userinfo where id='";
    int ret = conn->LoginQuery(_key, str + _id + L"' and pw='" + _pw + L"'");
    m_pConnectionPool->ReleaseConnection(std::move(conn));
    return ret;
}

int CODBCManager::SelectID(SQLWCHAR* _id)
{
    std::unique_ptr<CODBC> conn = m_pConnectionPool->GetConnection();
    std::wstring str = L"select number from userinfo where id = '";
    int ret = conn->SelectID(str + _id + L"'");
    m_pConnectionPool->ReleaseConnection(std::move(conn));
    return ret;
}

int CODBCManager::CreateAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
    std::unique_ptr<CODBC> conn = m_pConnectionPool->GetConnection();
    std::wstring str = L"insert userinfo values ('";
    int ret = conn->CreateAccountQuery(str + _id + L"','" + _pw + L"')");
    m_pConnectionPool->ReleaseConnection(std::move(conn));
    conn = m_pConnectionPool->GetConnection();
    /*str = L"insert characterlist values ('";
    ret = conn->CreateAccountQuery(str + _id + L"',0,NULL,NULL,NULL)");
    m_pConnectionPool->ReleaseConnection(std::move(conn));*/
    return ret;
}