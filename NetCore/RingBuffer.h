#pragma once

constexpr int Buffer_MAX = 65530;
constexpr int tempBuffer_MAX = 100;

class CRingBuffer
{
private:
	int m_size;

	char* m_buffer;
	char* m_tempBuffer;
	char* m_pRead;
	char* m_pWrite;
	char* m_pBufferEnd;

	size_t m_remainDataSize;
public:
	CRingBuffer(int _bufferSize = Buffer_MAX);
	virtual ~CRingBuffer();

	size_t GetWriteBufferSize();	

	void Write(int _size);

	size_t GetReadSize();

	void Read(int _size);

	bool IsFull() { return (m_remainDataSize >= m_size); }

	char* GetBuffer() { return m_buffer; }

	size_t GetRemainDataSize() { return m_remainDataSize; }

	char* GetEndBufferAddr() { return m_pBufferEnd; }

	char* GetWriteBuffer() { return m_pWrite; }

	char* GetReadBuffer() { return m_pRead; }

	size_t GetRemainSize_EndBuffer(const char* _pBuffer) { return (int)(m_pBufferEnd - _pBuffer); }

	char* GetPacketBuffer();
};