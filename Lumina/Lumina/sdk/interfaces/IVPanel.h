#pragma once

class IVPanel
{
public:
	VFUNC( 36, GetName( int panel ), const char*( __thiscall* )( void*, int ) )( panel )
	VFUNC( 32, SetMouseInputEnabled( unsigned int panel, bool state ), void( __thiscall* )( PVOID, int, bool ) )( panel, state )
};

extern IVPanel* g_pPanel;