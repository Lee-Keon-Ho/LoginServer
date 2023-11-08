#pragma once
#include <WinSock2.h>

struct VECTOR3
{
	float x;
	float y;
	float z;

	VECTOR3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct sCharacterList
{
	int name_1_Len;
	char name1[28];
	int type_1;
	int type_1_level;

	int name_2_Len;
	char name2[28];
	int type_2;
	int type_2_level;

	int name_3_Len;
	char name3[28];
	int type_3;
	int type_3_level;

	sCharacterList() : name_1_Len(0), type_1(0), type_1_level(0), name_2_Len(0), type_2(0), type_2_level(0), name_3_Len(0), type_3(0), type_3_level(0)
	{
		memset(name1, 0, sizeof(name1));
		memset(name2, 0, sizeof(name2));
		memset(name3, 0, sizeof(name3));
	}
};

struct sCharacterInfo
{
	wchar_t name[16];
	int type;
	int level;
	int curHp;
	int maxHp;
	int curMp;
	int maxMp;
	VECTOR3 position;
	int curExp;
	int damageMin;
	int damageMax;

	sCharacterInfo() : type(0), level(0), curHp(0), maxHp(0), curMp(0), maxMp(0), position({0.0f, 0.0f, 0.0f}), curExp(0), damageMin(0), damageMax(0)
	{
		memset(name, 0, sizeof(name));
	}
};