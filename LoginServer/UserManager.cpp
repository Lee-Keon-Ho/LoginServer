#include "UserManager.h"

CUserManager::CUserManager() : m_lock(new SRWLOCK())
{
	InitializeSRWLock(m_lock);
}

CUserManager::~CUserManager()
{
}

void CUserManager::Add(std::wstring _key, CUser* _pUser)
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	m_userList.insert(std::make_pair(_key, _pUser));
}

void CUserManager::Del(std::wstring _key)
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	auto iter = m_userList.find(_key);
	if (iter != m_userList.end()) m_userList.erase(iter);
}

void CUserManager::Find(std::wstring _key)
{
	CLock lock(m_lock, eLockType::SHARED);

	CUser* pUser = m_userList[_key];
	
	LKH::sharedPtr<PACKET> packet = new LS2C_PACKET(pUser->GetId());

	pUser->Send(packet, packet.get()->size);
}

int CUserManager::GetUserSize()
{
	return m_userList.size();
}
