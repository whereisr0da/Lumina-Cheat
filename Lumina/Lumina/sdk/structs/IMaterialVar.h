#pragma once

class IMaterialVar
{
public:
	VFUNC( 1, get_tex_value(), ITexture*( __thiscall* )( void* ) )( )
		VFUNC( 4, set_float_vaue( float val ), void( __thiscall* )( void*, float ) )( val )
		VFUNC( 5, set_int_value( int val ), void( __thiscall* )( void*, int ) )( val )
		VFUNC( 6, set_string_value( char const *val ), void( __thiscall* )( void*, char const * ) )( val )
		VFUNC( 11, set_vec_val( float x, float y, float z ), void( __thiscall* )( void*, float, float, float ) )( x, y, z )
		VFUNC( 15, set_tex_val( ITexture* tex ), void( __thiscall* )( void*, ITexture* ) )( tex )
};
