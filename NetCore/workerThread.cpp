#include "../NetCore/session.h"
#include "workerThread.h"
#include "IOCP.h"
#include <process.h>
#include <stdio.h>
#include <iostream>
#include <exception>
CWorkerThread::CWorkerThread()
{
}

CWorkerThread::~CWorkerThread()
{
}

bool CWorkerThread::Start()
{
	m_threadId = (HANDLE)_beginthreadex(NULL, 0, &CWorkerThread::WorkerThreadFunc, this, 0, NULL);
	if (m_threadId == 0)
	{
		printf("Thread Error\n");
		return false;
	}
	return true;
}

unsigned int _stdcall CWorkerThread::WorkerThreadFunc(void* _pArgs)
{
	CWorkerThread* thread = (CWorkerThread*)_pArgs;

	thread->RunLoop();
	return 0;
}

void CWorkerThread::RunLoop()
{
	HANDLE hIOCP = CIocp::GetInstance()->GetHandle();
	DWORD bytesTrans;
	overlapped_ex* overlapped;
	int bin;

	while (true)
	{
		try
		{
			if (!GetQueuedCompletionStatus(hIOCP, &bytesTrans, (PULONG_PTR)&bin, (LPOVERLAPPED*)&overlapped, INFINITE))
			{
				printf("Error : %d\n", GetLastError()); // 수정 필요

				continue;
			}

			if (bytesTrans <= 0)
			{
				overlapped->session->Delete();
			}
			else
			{
				if (overlapped->flag == static_cast<int>(eFlag::RECV)) overlapped->session->OnRecv(bytesTrans);
				else overlapped->session->OnSend();
			}
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}