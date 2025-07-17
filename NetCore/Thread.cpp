#include "Thread.h"
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <iostream>
#include <exception>
#include <assert.h>

CThread::CThread()
{
}

CThread::~CThread()
{
}

bool CThread::Start()
{
	HANDLE threadId = (HANDLE)_beginthreadex(NULL, 0, &CThread::ThreadFunc, this, 0, NULL);

	assert(threadId != 0);
	
	return true;
}

unsigned int _stdcall CThread::ThreadFunc(void* _pArgs)
{
	CThread* thread = (CThread*)_pArgs;

	thread->RunLoop();

	return 0;
}
