#pragma once

class ConVar
{
public:
	VFUNC( 5, get_name(), char*( __thiscall* )( void* ) )( )
		VFUNC( 14, set_value( const char* value ), void( __thiscall* )( void*, const char* ) )( value )
		VFUNC( 15, set_value( float value ), void( __thiscall* )( void*, float ) )( value )
		VFUNC( 16, set_value( int value ), void( __thiscall* )( void*, int ) )( value )
		VFUNC( 17, set_value( Color value ), void( __thiscall* )( void*, Color ) )( value )

		bool get_bool() { return !!get_int(); }
	char* get_default() { return pszDefaultValue; }
	float get_float()
	{
		const auto temp = *reinterpret_cast< int* >( &fValue );
		auto temp_result = static_cast< int >( temp ^ reinterpret_cast< uintptr_t >( this ) );

		return *reinterpret_cast< float* >( &temp_result );
	}
	int get_int()
	{
		const auto temp = *reinterpret_cast< int* >( &fValue );
		auto temp_result = static_cast< int >( temp ^ reinterpret_cast< uintptr_t >( this ) );

		return *static_cast< int* >( &temp_result );
	}

	char pad_0x0000[ 0x4 ]; //0x0000
	ConVar* pNext; //0x0004 
	__int32 bRegistered; //0x0008 
	char* pszName; //0x000C 
	char* pszHelpString; //0x0010 
	__int32 nFlags; //0x0014 
	char pad_0x0018[ 0x4 ]; //0x0018
	ConVar* pParent; //0x001C 
	char* pszDefaultValue; //0x0020 
	char* strString; //0x0024 
	__int32 StringLength; //0x0028 
	float fValue; //0x002C 
	__int32 nValue; //0x0030 
	__int32 bHasMin; //0x0034 
	float fMinVal; //0x0038 
	__int32 bHasMax; //0x003C 
	float fMaxVal; //0x0040 
	void* fnChangeCallbacks;

	__forceinline const char* GetString() {

		using original_fn = const char*(__thiscall*)(decltype(this));
		return (*(original_fn**)this)[11](this);
	}

};//Size=0x0048
