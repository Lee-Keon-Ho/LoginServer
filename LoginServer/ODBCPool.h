#pragma once
#include "ODBC.h"
#include <vector>
#include <queue>
#include <thread>
#include <functional>
#include <mutex>

using namespace std;

class CODBCPool
{
private:
	SQLWCHAR*				m_dbName;
	int						m_poolSize;
	vector<CODBC*>			m_connections;
	mutex					m_mutex;
	condition_variable		m_condition;

public:
	CODBCPool(SQLWCHAR* _dbName, int _poolSize);
	~CODBCPool();

	CODBC* GetConnection();
	void ReleaseConnection(CODBC* _conn);
};