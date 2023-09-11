#pragma once
#include <WinSock2.h>
#include <string>

#pragma pack( push, 1)
struct PACKET
{
	u_short size;
	u_short type;

	PACKET() : size(0), type(0) {}
	PACKET(u_short _size, u_short _type) : size(_size), type(_type) {}
};
#pragma pack( pop )