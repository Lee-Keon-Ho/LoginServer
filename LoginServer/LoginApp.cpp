#include "LoginApp.h"
#include "ODBCManager.h"
#include "FieldConnection.h"
#include "MonitorConnection.h"

#ifdef _DEBUG
#pragma comment (lib, "./../x64/Debug/NetCore.lib")
#else
#pragma comment (lib, "./../x64/Release/NetCore.lib")
#endif

#pragma comment (lib, "winmm.lib")

CLoginApp::CLoginApp(): 
	m_pLoginAcceptor(nullptr),
	m_pPrivateAcceptor(nullptr),
	m_pMonitorAcceptor(nullptr),
	m_pThreadManager(nullptr)
{
}

CLoginApp::~CLoginApp()
{
}

bool CLoginApp::Initialize()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		printf("Failed WSAStartup()\n");
		return false;
	}

	return true;
}

bool CLoginApp::CreateInstance()
{
	if (!m_pLoginAcceptor) m_pLoginAcceptor = std::make_unique<CLoginAcceptor>("112.184.241.183", 30003);
	if (m_pLoginAcceptor == nullptr) return false;
	assert(m_pLoginAcceptor != nullptr);
	if (!m_pPrivateAcceptor) m_pPrivateAcceptor = std::make_unique<CPrivateAcceptor>("112.184.241.183", 40003);
	assert(m_pPrivateAcceptor != nullptr);
	if (!m_pMonitorAcceptor) m_pMonitorAcceptor = std::make_unique<CMonitorAcceptor>("112.184.241.183", 50004); // connect
	assert(m_pMonitorAcceptor != nullptr);
	if (!m_pThreadManager) m_pThreadManager = std::make_unique<CThreadManager>();
	assert(m_pThreadManager != nullptr);
	if (!CODBCManager::GetInstance()->Initialize((SQLWCHAR*)L"account")) return false;

	return true;
}

bool CLoginApp::StartInstance()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	
	if (!m_pThreadManager->Start(static_cast<u_int>(si.dwNumberOfProcessors * 2))) return false;
	CFieldConnection::GetInstance()->Start();
	CMoniterConnection::GetInstance()->Start();
	printf("login server start...\n");
	return true;
}

void CLoginApp::RunLoop()
{
	while (true)
	{
		Sleep(1);
	}
}

void CLoginApp::DeleteInstance()
{
}
