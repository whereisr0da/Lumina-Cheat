#pragma once

class ClientClass;
class IBaseClientDll
{
public:
	VFUNC( 4, Shutdown(), void(__thiscall*)(void*))()
	VFUNC( 8, GetAllClasses(), ClientClass*( __thiscall* )( void* ) )( )
	VFUNC( 20, IN_KeyEvent( int eventcode, int keynum, const char *pszCurrentBinding ), void( __thiscall* )( void*, int, int, const char* ) )( eventcode, keynum, pszCurrentBinding )
	VFUNC( 21, CreateMove( int sequence_number, float frametime, bool active ), void( __thiscall* )( void*, int, float, bool ) )( sequence_number, frametime, active )
};

extern IBaseClientDll* g_pClient;