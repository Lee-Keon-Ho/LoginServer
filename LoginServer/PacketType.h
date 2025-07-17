#pragma once

enum class ePacketType : u_short
{
	CS_PT_TEST = 0,
	CS_PT_LOGIN,
	CS_PT_CHECK_ID,
	CS_PT_CREATE_ACCOUNT,
	CS_PT_IN_FIELD,
	CS_PT_DUMMY_IN_FIELD,
	CS_PT_MAX
};