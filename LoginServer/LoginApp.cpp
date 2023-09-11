#include "LoginApp.h"
#include "../NetCore/DatabaseManager.h"

#ifdef _DEBUG
#pragma comment (lib, "./../x64/Debug/NetCore.lib")
#else
#pragma comment (lib, "./../x64/Release/NetCore.lib")
#endif

#pragma comment (lib, "winmm.lib")

CLoginApp::CLoginApp()
	: m_pLoginAcceptor(nullptr),
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
	if (!m_pLoginAcceptor) m_pLoginAcceptor = new CLoginAcceptor("112.184.241.183", 30003);
	if (m_pLoginAcceptor == nullptr) return false;
	if (!m_pThreadManager) m_pThreadManager = new CThreadManager();
	if (m_pThreadManager == nullptr) return false;
	if (!CDatabaseManager::GetInstance()->Initialize((SQLWCHAR*)L"account")) return false;
	

	return true;
}

bool CLoginApp::StartInstance()
{
	SYSTEM_INFO si;
	GetSystemInfo(&si);
	
	if (!m_pThreadManager->Start(si.dwNumberOfProcessors * 2)) return false;

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
	if (m_pThreadManager) { delete m_pThreadManager; m_pThreadManager = nullptr; }
	if (m_pLoginAcceptor) { delete m_pLoginAcceptor; m_pLoginAcceptor = nullptr; }
}
