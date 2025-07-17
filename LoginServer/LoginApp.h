#pragma once
#include"../NetCore/ThreadManager.h"
#include "App.h"
#include "LoginAcceptor.h"
#include "privateAcceptor.h"
#include "MonitorAcceptor.h"

class CLoginApp : public CApp
{
private:
	std::unique_ptr<CLoginAcceptor>		m_pLoginAcceptor;
	std::unique_ptr<CPrivateAcceptor>	m_pPrivateAcceptor;
	std::unique_ptr<CMonitorAcceptor>	m_pMonitorAcceptor;
	std::unique_ptr<CThreadManager>		m_pThreadManager;
public:
	CLoginApp();
	~CLoginApp();

public:
	bool Initialize() override;
	bool CreateInstance() override;
	bool StartInstance() override;
	void RunLoop() override;
	void DeleteInstance() override;
};