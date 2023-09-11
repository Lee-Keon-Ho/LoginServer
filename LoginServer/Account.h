#pragma once

#define MAX 30

class CAccount
{
private:
	int m_index;
	wchar_t m_id[MAX];
	wchar_t m_pw[MAX];
public:
	CAccount();
	CAccount(int _index, wchar_t* _id, wchar_t* _pw);
	~CAccount();

	wchar_t* GetPassword();
	int GetIndex();
};