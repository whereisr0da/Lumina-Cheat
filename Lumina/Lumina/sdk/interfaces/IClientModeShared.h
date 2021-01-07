#pragma once

class CBaseHudChat
{
public:
	VFUNC( 26, ChatPrintf( int idx, int filter, const char* fmt, ... ), void( __cdecl* )( void*, int, int, const char*, ... ) )( idx, filter, fmt )
};

class IClientModeShared
{
public:
	char pad[ 28 ];
	CBaseHudChat			*m_pChatElement;
};

extern IClientModeShared* g_pClientMode;