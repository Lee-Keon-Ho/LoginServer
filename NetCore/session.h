#pragma once
#include <WinSock2.h>
#include "RingBuffer.h"
#include "sharedPtr.h"
#include "../LoginServer/PacketStruct.h"
#include <memory>
#include <deque>

constexpr int buffer_max = 1000;
constexpr int cs_spin_count = 4000;

enum class eFlag : int
{
	RECV = 0,
	SEND
};

class CSession;

struct overlapped_ex : WSAOVERLAPPED
{
	CSession*	session;
	u_short		flag;
};

struct ACCEPT_SOCKET_INFO
{
	SOCKET		socket;
	SOCKADDR_IN	addr;
};

class CSession
{
protected:
	WSABUF								m_recv_dataBuf;
	WSABUF								m_send_dataBuf;

	ACCEPT_SOCKET_INFO					m_socket_info;
	
	overlapped_ex						m_recv_overlapped;
	overlapped_ex						m_send_overlapped;

	std::unique_ptr<CRingBuffer>		m_ringBuffer;
	std::deque<LKH::sharedPtr<PACKET>>	m_send_que;

	PSRWLOCK							m_lock;
public:
	CSession();
	CSession(ACCEPT_SOCKET_INFO _socketInfo);
	virtual ~CSession();

	bool Send(LKH::sharedPtr<PACKET> _buffer, int _size);
	bool Recv();

	void OnRecv(DWORD _size);
	void OnSend();

	virtual int PacketHandle() = 0;
	virtual void Delete() = 0;

	SOCKET GetSocket();
	SOCKADDR_IN GetAddr();
	char* GetPacketBuffer();
	int GetReadSize();
};