#include "FieldConnection.h"
#include "../NetCore/Lock.h"
#include "UserManager.h"
#include <iostream>

using namespace std;

CFieldConnection::CFieldConnection() : m_lock(new SRWLOCK())
{
	InitializeSRWLock(m_lock);
	m_iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	m_overlapped_send.fieldConnector = this;
	m_overlapped_send.flag = static_cast<int>(eFlag::SEND);
	m_overlapped_recv.fieldConnector = this;
	m_overlapped_recv.flag = static_cast<int>(eFlag::RECV);

	m_pRingBuffer = std::make_unique<CRingBuffer>();

	m_dataBuf_recv.buf = m_pRingBuffer.get()->GetWriteBuffer();
	m_dataBuf_recv.len = m_pRingBuffer.get()->GetWriteBufferSize();
}

CFieldConnection::~CFieldConnection()
{
	if (m_lock) { delete m_lock; m_lock = nullptr; }
}

bool CFieldConnection::Start()
{
	if (!CThread::Start()) return false;
	return true;
}

void CFieldConnection::RunLoop()
{
	HANDLE hIOCP = m_iocp;
	DWORD bytesTrans;
	overlapped_field* overlapped;
	int bin;

	while (true) // 상속 구조를 생각해보자
	{
		if (!GetQueuedCompletionStatus(hIOCP, &bytesTrans, (PULONG_PTR)&bin, (LPOVERLAPPED*)&overlapped, INFINITE))
		{
			printf("Error : %d\n", GetLastError()); // 오류 처리 부분이 부족

			continue;
		}

		switch (overlapped->flag)
		{
		case static_cast<int>(eFlag::RECV):
			overlapped->fieldConnector->OnRecv(bytesTrans);
			break;
		case static_cast<int>(eFlag::SEND):
			overlapped->fieldConnector->OnSend();
			break;
		}
	}
}

void CFieldConnection::OnSend()
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	m_sendQue.pop_front();

	if (m_sendQue.size() > 0)
	{
		DWORD sendSize = 0;
		DWORD err = 0;

		m_dataBuf_send.len = m_sendQue.front().get()->size;
		m_dataBuf_send.buf = reinterpret_cast<char*>(m_sendQue.front().get());

		if (WSASend(m_field.socket, &m_dataBuf_send, 1, &sendSize, 0, &m_overlapped_send, NULL) == SOCKET_ERROR)
		{
			err = GetLastError();
			if (err != WSAEWOULDBLOCK)
			{
				std::cout << "WSASend Error : " << err << std::endl;
			}
		}

		assert(sendSize > 0);
	}
	else m_dataBuf_send.len = 0;
}

void CFieldConnection::OnRecv(DWORD _size)
{
	m_pRingBuffer->Write(_size);
	PacketHandle();

	m_dataBuf_recv.len = m_pRingBuffer->GetWriteBufferSize();
	m_dataBuf_recv.buf = m_pRingBuffer->GetWriteBuffer();

	Recv();
}

void CFieldConnection::SetFieldSockeInfo(ACCEPT_SOCKET_INFO& _socket_info)
{
	m_field = _socket_info;
	CreateIoCompletionPort((HANDLE)m_field.socket, m_iocp, (ULONG_PTR)this, 0);
	Recv();
}

void CFieldConnection::Send(LKH::sharedPtr<PACKET> _packet, int _size)
{
	CLock lock(m_lock, eLockType::EXCLUSIVE);

	m_sendQue.push_back(_packet);
	if (m_dataBuf_send.len == 0)
	{
		DWORD sendSize = 0;
		DWORD err = 0;

		m_dataBuf_send.len = _packet.get()->size;
		m_dataBuf_send.buf = reinterpret_cast<char*>(m_sendQue.front().get());

		if (WSASend(m_field.socket, &m_dataBuf_send, 1, &sendSize, 0, &m_overlapped_send, NULL) == SOCKET_ERROR)
		{
			err = GetLastError();
			if (err != WSAEWOULDBLOCK)
			{
				std::cout << "WSASend Error : " << err << std::endl;
			}
		}

		assert(sendSize > 0);
	}
}

void CFieldConnection::Recv()
{
	DWORD recvBytes = 0;
	DWORD flags = 0;
	DWORD err;

	if (WSARecv(m_field.socket, &m_dataBuf_recv, 1, &recvBytes, &flags, &m_overlapped_recv, NULL) == SOCKET_ERROR)
	{
		if (err = WSAGetLastError() != WSA_IO_PENDING)
		{
			printf("Error WSARecv : %d \n", err);
		}
	}
}

void CFieldConnection::PacketHandle()
{
	char* readBuffer = GetPacketBuffer();
	if (readBuffer == nullptr) return;

	FS2LS_PACKET* packet = reinterpret_cast<FS2LS_PACKET*>(readBuffer);

	CUserManager::GetInstance()->Find(packet->key);

	if (packet->size > 0)
	{
		m_pRingBuffer.get()->Read(packet->size);
	}
}

char* CFieldConnection::GetPacketBuffer()
{
	return m_pRingBuffer.get()->GetPacketBuffer();
}
