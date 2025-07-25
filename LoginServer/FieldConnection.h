#pragma once
#include "../NetCore/session.h"
#include "../NetCore/Thread.h"

class CFieldConnection;

struct overlapped_field : WSAOVERLAPPED
{
	CFieldConnection* fieldConnector;
	int flag;
};

class CFieldConnection : public CThread
{
public:
	static CFieldConnection* GetInstance()
	{
		static CFieldConnection instance;
		return &instance;
	}

private:
	CFieldConnection();
	~CFieldConnection();

private:
	ACCEPT_SOCKET_INFO m_field;
	std::deque<LKH::sharedPtr<PACKET>>	m_sendQue;
	WSABUF m_dataBuf_send;
	WSABUF m_dataBuf_recv;

	PSRWLOCK m_lock;

	HANDLE m_iocp;

	overlapped_field m_overlapped_send;
	overlapped_field m_overlapped_recv;

	std::unique_ptr<CRingBuffer>	m_pRingBuffer;

	int i = 0;
public:
	bool Start();
	void RunLoop() override;

	void OnSend();
	void OnRecv(DWORD _size);

	void SetFieldSockeInfo(ACCEPT_SOCKET_INFO& _socket_info);

	void Send(LKH::sharedPtr<PACKET> _buffer, int _size);
	void Recv();

private:
	void PacketHandle();
	char* GetPacketBuffer();
};