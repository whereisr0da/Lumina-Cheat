#pragma once

class IMemAlloc
{
public:
	VFUNC( 1, Alloc( size_t size ), void*( __thiscall* )( void*, size_t ) )( size )
		VFUNC( 3, Realloc( void *mem, size_t size ), void*( __thiscall* )( void*, void*, size_t ) )( mem, size )
		VFUNC( 5, Free( void *mem ), void( __thiscall* )( void*, void* ) )( mem )
};

extern IMemAlloc* g_pMemAlloc;