#include "ThreadManager.h"
#include <process.h>
CThreadManager::CThreadManager()
{
}

CThreadManager::~CThreadManager()
{
	m_thread.clear();
	std::vector < std::unique_ptr<CWorkerThread> >().swap(m_thread);
}

bool CThreadManager::Start(u_int _size)
{
	m_thread.reserve(_size);
	std::unique_ptr<CWorkerThread> workerThread;

	for (int i = 0; i < _size; i++)
	{
		workerThread = std::make_unique<CWorkerThread>();
		if (workerThread->Start())
		{
			m_thread.push_back(std::move(workerThread));
		}
	}
	return true;
}