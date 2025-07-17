#pragma once
#include "struct.h"
#include "PacketType.h"
constexpr int id_max_size = 15;
constexpr int pw_max_size = 15;

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
	u_short ret;
	u_short key;
	wchar_t id[id_max_size] = { 0, };

	PACKET_LOGIN() : ret(0), key(0) {}
	PACKET_LOGIN(u_short _ret, u_short _key, wchar_t* _id) : ret(_ret), key(_key)
	{
		size = sizeof(PACKET_LOGIN);
		type = static_cast<u_short>(ePacketType::CS_PT_LOGIN);
		memcpy(id, _id, sizeof(id));
	}
};

struct PACKET_CHECK_ID : PACKET
{
	u_short key;

	PACKET_CHECK_ID(u_short _key) : key(_key)
	{
		size = sizeof(PACKET_CHECK_ID);
		type = static_cast<u_short>(ePacketType::CS_PT_CHECK_ID);
	}
};

struct PACKET_CREATE_ACCOUNT : PACKET
{
	u_short key;

	PACKET_CREATE_ACCOUNT() : key(0) {}
	PACKET_CREATE_ACCOUNT(u_short _key) : key(_key) 
	{
		size = sizeof(PACKET_CREATE_ACCOUNT);
		type = static_cast<u_short>(ePacketType::CS_PT_CREATE_ACCOUNT);
	}
};


struct PACKET_LS2FS_IN_FIELD : PACKET // 수정필요
{
	u_short nameLen;
	sCharacterInfo characterInfo;

	PACKET_LS2FS_IN_FIELD() : nameLen(0), characterInfo() {}
	PACKET_LS2FS_IN_FIELD(u_short _nameLen, sCharacterInfo& _characterInfo) : nameLen(_nameLen), characterInfo(_characterInfo) 
	{
		size = sizeof(PACKET_LS2FS_IN_FIELD);
		type = 0;
	}
};

struct LS2WS_PACKET : PACKET
{
	u_short key;

	LS2WS_PACKET(u_short _key) : key(_key)
	{
		size = sizeof(LS2WS_PACKET);
		type = 0;
	}
};

struct LS2MC_PACKET : PACKET
{
	float		time;
	u_short		userCount;

	LS2MC_PACKET() : time(0.0f), userCount(0) {}
	LS2MC_PACKET(float _time, u_short _userCount) :
		time(_time), userCount(_userCount)
	{
		size = sizeof(LS2MC_PACKET);
		type = 0; // 수정
	}
};

struct C2LS_LOGIN : PACKET
{
	wchar_t id[id_max_size];
	wchar_t pw[pw_max_size];

	C2LS_LOGIN() {}
};

struct C2LS_CHECK_ID : PACKET
{
	wchar_t id[id_max_size] = { 0, };

	C2LS_CHECK_ID() {}
};

struct C2LS_CREATE_ACCOUNT : PACKET
{
	wchar_t id[id_max_size] = { 0, };
	wchar_t pw[pw_max_size] = { 0, };

	C2LS_CREATE_ACCOUNT() {}
};


struct C2LS_IN_FIELD : PACKET
{
	wchar_t name[name_max_size] = { 0, };

	C2LS_IN_FIELD() {}
};

struct C2LS_DUMMY_IN_FIELD : PACKET
{
	wchar_t name[name_max_size] = { 0, };
	VECTOR3 position = {0.0f, 0.0f, 0.0f};

	C2LS_DUMMY_IN_FIELD() {}
};


struct FS2LS_PACKET : PACKET
{
	wchar_t key[name_max_size] = { 0, };

	FS2LS_PACKET() {}
};

struct LS2C_PACKET : PACKET
{
	wchar_t key[name_max_size] = { 0, };

	LS2C_PACKET(wchar_t* _key)
	{
		size = sizeof(LS2C_PACKET);
		type = 99;
		memcpy(key, _key, sizeof(wchar_t) * name_max_size);
	}
};

struct MC2LS_PACKET : PACKET
{
	float time;

	MC2LS_PACKET() : time(0.0f) {}
};

#pragma pack( pop )