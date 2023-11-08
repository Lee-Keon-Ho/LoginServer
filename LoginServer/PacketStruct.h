#pragma once
#include "struct.h"

#pragma pack( push, 1)
struct PACKET
{
	u_short size;
	u_short type;

	PACKET() : size(0), type(0) {}
	PACKET(u_short _size, u_short _type) : size(_size), type(_type) {}
};

struct PACKET_LOGIN : PACKET
{
	u_short key;

	PACKET_LOGIN() : key(0) {}
	PACKET_LOGIN(u_short _size, u_short _type, u_short _key) : PACKET(_size, _type), key(_key) {}
};

struct PACKET_CREATE_ACCOUNT : PACKET
{
	u_short key;

	PACKET_CREATE_ACCOUNT() : key(0) {}
	PACKET_CREATE_ACCOUNT(u_short _size, u_short _type, u_short _key) : PACKET(_size, _type), key(_key) {}
};

struct PACKET_CHARACTERLIST : PACKET
{
	u_short key;
	sCharacterList characterList;

	PACKET_CHARACTERLIST() : key(0), characterList() {}
	PACKET_CHARACTERLIST(u_short _size, u_short _type, u_short _key, sCharacterList& _characterList) : PACKET(_size, _type), key(_key), characterList(_characterList) {}
};

struct PACKET_IN_FIELD : PACKET
{
	wchar_t name[28];
	
	PACKET_IN_FIELD() : name(L"") {}
	PACKET_IN_FIELD(u_short _size, u_short _type, u_short _len, wchar_t* _name) : PACKET(_size, _type)
	{
		memset(name, 0, sizeof(name));
		memcpy(name, _name, _len);
	}
};

struct PACKET_DOUBLE_CHECK : PACKET
{
	u_short check;

	PACKET_DOUBLE_CHECK() : check(0) {}
	PACKET_DOUBLE_CHECK(u_short _size, u_short _type, u_short _check) : PACKET(_size, _type), check(_check) {}
};

struct PACKET_FS_IN_FIELD : PACKET
{
	u_short nameLen;
	sCharacterInfo characterInfo;

	PACKET_FS_IN_FIELD() : nameLen(0), characterInfo() {}
	PACKET_FS_IN_FIELD(u_short _size, u_short _type, u_short _nameLen, sCharacterInfo& _characterInfo) : PACKET(_size, _type), nameLen(_nameLen), characterInfo(_characterInfo) {}
};
#pragma pack( pop )