#include "ODBCPool.h"
#include "../NetCore/Lock.h"
#include <iostream>

CODBCPool::CODBCPool(SQLWCHAR* _dbName, int _poolSize) :
	m_dbName(_dbName),
	m_poolSize(_poolSize)
{
	try
	{
		for (int i = 0; i < m_poolSize; i++)
		{
			CODBC* conn = new CODBC(m_dbName);
			m_connections.push_back(conn);
		}
	}
	catch (runtime_error e)
	{
		std::cout << e.what() << endl;
	}
}

CODBCPool::~CODBCPool()
{
	for (auto* conn : m_connections)
	{
		conn->Close();
	}
}

CODBC* CODBCPool::GetConnection()
{
	unique_lock<mutex> lock(m_mutex);
	while (m_connections.empty())
	{
		// ��� ������ ������ ���� ��� ���
		m_condition.wait(lock);
	}
	CODBC* conn = m_connections.back();
	m_connections.pop_back();
	return conn;
}

void CODBCPool::ReleaseConnection(CODBC* _conn)
{
	lock_guard<mutex> lock(m_mutex); // CLock ������Ʈ�� ����ϸ� �ȴ�.
	m_connections.push_back(_conn);
	// ��� ���� �����尡 �ִ� ��� ����
	m_condition.notify_one();
}
