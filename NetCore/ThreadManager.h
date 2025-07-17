#pragma once
#include "workerThread.h"
#include <memory>
#include <vector>
class CThreadManager
{
public:
	using thread_t = std::vector<std::unique_ptr<CWorkerThread>>;

private:
	thread_t m_thread;

public:
	CThreadManager();
	~CThreadManager();

	bool Start(u_int _size);
};