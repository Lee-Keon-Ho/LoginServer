#pragma once
#include"../NetCore/ThreadManager.h"
#include "App.h"
#include "LoginAcceptor.h"

class CLoginApp : public CApp
{
private:
	CLoginAcceptor*		m_pLoginAcceptor;
	CThreadManager*		m_pThreadManager;
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