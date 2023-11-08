#include "ODBCManager.h"

CODBCManager::CODBCManager() : m_connectionPool(nullptr)
{
}

CODBCManager::~CODBCManager()
{
    if (m_connectionPool) { delete m_connectionPool; }
}

bool CODBCManager::Initialize(SQLWCHAR* _db)
{
	if (!m_connectionPool) m_connectionPool = new CODBCPool(_db, 10);
	if (m_connectionPool == nullptr) return false;
}

int CODBCManager::SelectAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select number from userinfo where id='";
    int ret = conn->LoginQuery(str + _id + L"' and pw='" + _pw + L"'");
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::SelectID(SQLWCHAR* _id)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select number from userinfo where id = '";
    int ret = conn->SelectID(str + _id + L"'");
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::CreateAccount(SQLWCHAR* _id, SQLWCHAR* _pw)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"insert userinfo values ('";
    int ret = conn->CreateAccountQuery(str + _id + L"','" + _pw + L"')");
    m_connectionPool->ReleaseConnection(conn);
    conn = m_connectionPool->GetConnection();
    str = L"insert characterlist values ('";
    ret = conn->CreateAccountQuery(str + _id + L"',0,NULL,NULL,NULL)");
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::CharacterInfo(int _key, sCharacterList& _info)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select * from CharacterList where number=";
    int ret = conn->CharacterList(str + to_wstring(_key), _info);
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::SelectCharacterList(wchar_t* _id, sCharacterList& _info)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select LEN(name) Len, name, type, level from CharacterList where id = '";
    int ret = conn->CharacterList(str + _id + L"'", _info);
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::CreateCharacter(wchar_t* _id, wchar_t* _name, int _type)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"insert CharacterList values('";
    int ret = conn->CreateCharacter(str + _id + L"','" + _name + L"', " + to_wstring(_type) + L", 1)");
    m_connectionPool->ReleaseConnection(conn);
    
    if (ret > 0)
    {
        wstring wStr = L"insert CharacterInfo values('";
        wstring endWStr;
        if (_type == 1)
        {
            endWStr = L", 1, 100, 100, 100, 100, 73, 1, 70, 0, 3, 5)";
        }
        else if (_type == 2)
        {
            endWStr = L", 1, 100, 100, 100, 100, 73, 1, 70, 0, 2, 3)";
        }
        else if (_type == 3)
        {
            endWStr = L", 1, 100, 100, 100, 100, 73, 1, 70, 0, 2, 3)";
        }

        conn = m_connectionPool->GetConnection();
        ret = conn->InsertCharacterInfo(wStr + _name + L"', " + to_wstring(_type) + endWStr);
        m_connectionPool->ReleaseConnection(conn);
    }
    
    return ret;
}

int CODBCManager::DeleteCharacter(wchar_t* _id, wchar_t* _name)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"delete CharacterInfo where name = '";
    int ret = conn->DeleteCharacter(str + _name + L"'");
    m_connectionPool->ReleaseConnection(conn);
    if (ret <= 0) return ret;
    conn = m_connectionPool->GetConnection();
    wstring wStr = L"delete CharacterList where id = '";
    ret = conn->DeleteCharacter(wStr + _id + L"' and name = '" + _name + L"'");
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::DoubleCheck(wchar_t* _name)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select name from characterList where name = '";
    int ret = conn->SelectName(str + _name + L"'");
    // 중복이면 1 중복이 아니면 0을 리턴한다.
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}

int CODBCManager::SelectCharacterInfo(wchar_t* _name, sCharacterInfo& _characterInfo)
{
    CODBC* conn = m_connectionPool->GetConnection();
    wstring str = L"select * from characterInfo where name = '";
    int ret = conn->SelectCharacterInfo(str + _name + L"'", _characterInfo);
    m_connectionPool->ReleaseConnection(conn);
    return ret;
}