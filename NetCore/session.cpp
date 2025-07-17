#include "session.h"
#include "IOCP.h"
#include "Lock.h"
#include <stdio.h>
#include <iostream>
#include <exception>

CSession::CSession()
{
	
}

CSession::CSession(ACCEPT_SOCKET_INFO _socketInfo) : m_lock(new SRWLOCK())
{
	InitializeSRWLock(m_lock);

	m_recv_overlapped.session = this;
	m_recv_overlapped.flag = static_cast<int>(eFlag::RECV);
	m_send_overlapped.session = this;
	m_send_overlapped.flag = static_cast<int>(eFlag::SEND);
	m_socket_info = _socketInfo;
	m_ringBuffer = std::make_unique<CRingBuffer>(buffer_max);
	m_recv_dataBuf.buf = m_ringBuffer->GetWriteBuffer();
	m_recv_dataBuf.len = m_ringBuffer->GetWriteBufferSize();

	CIocp::GetInstance()->Associate(m_socket_info.socket);

	Recv();
}

CSession::~CSession()
{
	closesocket(m_socket_info.socket);
}

bool CSession::Send(LKH::sharedPtr<PACKET> _buffer, int _size)
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	m_send_que.push_back(_buffer);

	if (m_send_dataBuf.len == 0)
	{
		DWORD sendSize = 0;
		DWORD err = 0;

		m_send_dataBuf.len = _size;
		m_send_dataBuf.buf = reinterpret_cast<char*>(m_send_que.front().get());

		if (WSASend(m_socket_info.socket, &m_send_dataBuf, 1, &sendSize, 0, &m_send_overlapped, NULL) == SOCKET_ERROR)
		{
			if (err = GetLastError() != WSAEWOULDBLOCK)
			{
				std::cout << "WSASend Error : " << err << std::endl;
			}
		}

		assert(sendSize > 0);
	}
	return true;
}

bool CSession::Recv()
{
	DWORD recvBytes = 0;
	DWORD flags = 0;
	DWORD err;

	if (WSARecv(m_socket_info.socket, &m_recv_dataBuf, 1, &recvBytes, &flags, &m_recv_overlapped, NULL) == SOCKET_ERROR)
	{
		if (err = WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("Error WSARecv : %d \n", err);
			return false;
		}
	}
	return true;
}

void CSession::OnRecv(DWORD _size)
{
	m_ringBuffer->Write(_size);
	PacketHandle();

	m_recv_dataBuf.len = m_ringBuffer->GetWriteBufferSize();
	m_recv_dataBuf.buf = m_ringBuffer->GetWriteBuffer();
	
	Recv();
}

void CSession::OnSend()
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	m_send_que.pop_front();

	if (m_send_que.size() > 0)
	{
		DWORD sendSize = 0;
		DWORD err = 0;

		m_send_dataBuf.len = m_send_que.front().get()->size;
		m_send_dataBuf.buf = reinterpret_cast<char*>(m_send_que.front().get());

		WSASend(m_socket_info.socket, &m_send_dataBuf, 1, &sendSize, 0, &m_send_overlapped, NULL);

		assert(sendSize > 0);
	}
	else m_send_dataBuf.len = 0;
}

SOCKET CSession::GetSocket()
{
	return m_socket_info.socket;
}

SOCKADDR_IN CSession::GetAddr()
{
	return m_socket_info.addr;
}

char* CSession::GetPacketBuffer()
{
	return m_ringBuffer->GetPacketBuffer();
}

int CSession::GetReadSize()
{
	return m_ringBuffer->GetReadSize();
}