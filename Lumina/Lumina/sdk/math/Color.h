#pragma once

#ifndef Color_h

#define Color_h

#include "Vector.h"

class Color
{
public:
	Color()
	{
		*( ( int * )this ) = 0;
	}
	Color( int _r, int _g, int _b )
	{
		SetColor( _r, _g, _b, 255 );
	}
	Color( int _r, int _g, int _b, int _a )
	{
		SetColor( _r, _g, _b, _a );
	}
	Color( float _rgb[ 3 ] )
	{
		SetColor( ( int )( _rgb[ 0 ] * 255.0f ), ( int )( _rgb[ 1 ] * 255.0f ), ( int )( _rgb[ 2 ] * 255.0f ), 255 );
	}
	Color( float _rgb[ 3 ], float _alpha )
	{
		SetColor( ( int )( _rgb[ 0 ] * 255.0f ), ( int )( _rgb[ 1 ] * 255.0f ), ( int )( _rgb[ 2 ] * 255.0f ), ( int )_alpha );
	}

	Color( Color _cl, float _alpha )
	{
		SetColor( ( int )_cl.r(), ( int )_cl.g(), ( int )_cl.b(), ( int )_alpha );
	}

	void SetAlpha(int _a)
	{
		_cl[3] = (unsigned char)_a;
	}

	void SetColor( int _r, int _g, int _b, int _a = 255 )
	{
		_cl[ 0 ] = ( unsigned char )_r;
		_cl[ 1 ] = ( unsigned char )_g;
		_cl[ 2 ] = ( unsigned char )_b;
		_cl[ 3 ] = ( unsigned char )_a;
	}

	void GetColor( int &_r, int &_g, int &_b, int &_a ) const
	{
		_r = _cl[ 0 ];
		_g = _cl[ 1 ];
		_b = _cl[ 2 ];
		_a = _cl[ 3 ];
	}

	void SetRawColor( int color32 )
	{
		*( ( int* )this ) = color32;
	}

	int GetRawColor() const
	{
		return *( ( int* )this );
	}

	int GetD3DColor() const
	{
		return ( ( int )( ( ( ( _cl[ 3 ] ) & 0xff ) << 24 ) | ( ( ( _cl[ 0 ] ) & 0xff ) << 16 ) | ( ( ( _cl[ 1 ] ) & 0xff ) << 8 ) | ( ( _cl[ 2 ] ) & 0xff ) ) );
	}

	inline int r() const { return _cl[ 0 ]; }
	inline int g() const { return _cl[ 1 ]; }
	inline int b() const { return _cl[ 2 ]; }
	inline int a() const { return _cl[ 3 ]; }

	inline float rBase() const { return _cl[ 0 ] / 255.0f; }
	inline float gBase() const { return _cl[ 1 ] / 255.0f; }
	inline float bBase() const { return _cl[ 2 ] / 255.0f; }
	inline float aBase() const { return _cl[ 3 ] / 255.0f; }

	unsigned char &operator[]( int index )
	{
		return _cl[ index ];
	}

	const unsigned char &operator[]( int index ) const
	{
		return _cl[ index ];
	}

	bool operator == ( const Color &rhs ) const
	{
		return ( *( ( int * )this ) == *( ( int * )&rhs ) );
	}

	bool operator != ( const Color &rhs ) const
	{
		return !( operator==( rhs ) );
	}

	Color &operator=( const Color &rhs )
	{
		SetRawColor( rhs.GetRawColor() );
		return *this;
	}

	float* Base()
	{
		float clr[ 3 ];

		clr[ 0 ] = _cl[ 0 ] / 255.0f;
		clr[ 1 ] = _cl[ 1 ] / 255.0f;
		clr[ 2 ] = _cl[ 2 ] / 255.0f;

		return &clr[ 0 ];
	}

	float* BaseNoReduction()
	{
		float clr[3];

		clr[0] = _cl[0];
		clr[1] = _cl[1];
		clr[2] = _cl[2];

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[ 4 ];

		clr[ 0 ] = _cl[ 0 ] / 255.0f;
		clr[ 1 ] = _cl[ 1 ] / 255.0f;
		clr[ 2 ] = _cl[ 2 ] / 255.0f;
		clr[ 3 ] = _cl[ 3 ] / 255.0f;

		return &clr[ 0 ];
	}


	Vector BaseVector()
	{
		return Vector(_cl[0] / 255.0f, _cl[1] / 255.0f, _cl[2] / 255.0f);
	}


	float Hue() const
	{
		if ( _cl[ 0 ] == _cl[ 1 ] && _cl[ 1 ] == _cl[ 2 ] )
		{
			return 0.0f;
		}

		float r = _cl[ 0 ] / 255.0f;
		float g = _cl[ 1 ] / 255.0f;
		float b = _cl[ 2 ] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if ( r == max )
		{
			hue = ( g - b ) / delta;
		}
		else if ( g == max )
		{
			hue = 2 + ( b - r ) / delta;
		}
		else if ( b == max )
		{
			hue = 4 + ( r - g ) / delta;
		}
		hue *= 60;

		if ( hue < 0.0f )
		{
			hue += 360.0f;
		}
		return hue;
	}

	float Saturation() const
	{
		float r = _cl[ 0 ] / 255.0f;
		float g = _cl[ 1 ] / 255.0f;
		float b = _cl[ 2 ] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if ( max != min )
		{
			l = ( max + min ) / 2;
			if ( l <= 0.5f )
				s = ( max - min ) / ( max + min );
			else
				s = ( max - min ) / ( 2 - max - min );
		}
		return s;
	}

	float Brightness() const
	{
		float r = _cl[ 0 ] / 255.0f;
		float g = _cl[ 1 ] / 255.0f;
		float b = _cl[ 2 ] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return ( max + min ) / 2;
	}

	static Color FromHSB( float hue, float saturation, float brightness )
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - ( int )h;
		float p = brightness * ( 1.0f - saturation );
		float q = brightness * ( 1.0f - saturation * f );
		float t = brightness * ( 1.0f - ( saturation * ( 1.0f - f ) ) );

		if ( h < 1 )
		{
			return Color(
				( unsigned char )( brightness * 255 ),
				( unsigned char )( t * 255 ),
				( unsigned char )( p * 255 )
			);
		}
		else if ( h < 2 )
		{
			return Color(
				( unsigned char )( q * 255 ),
				( unsigned char )( brightness * 255 ),
				( unsigned char )( p * 255 )
			);
		}
		else if ( h < 3 )
		{
			return Color(
				( unsigned char )( p * 255 ),
				( unsigned char )( brightness * 255 ),
				( unsigned char )( t * 255 )
			);
		}
		else if ( h < 4 )
		{
			return Color(
				( unsigned char )( p * 255 ),
				( unsigned char )( q * 255 ),
				( unsigned char )( brightness * 255 )
			);
		}
		else if ( h < 5 )
		{
			return Color(
				( unsigned char )( t * 255 ),
				( unsigned char )( p * 255 ),
				( unsigned char )( brightness * 255 )
			);
		}
		else
		{
			return Color(
				( unsigned char )( brightness * 255 ),
				( unsigned char )( p * 255 ),
				( unsigned char )( q * 255 )
			);
		}
	}

	static Color Red() { return Color( 255, 0, 0 ); }
	static Color Green() { return Color( 0, 255, 0 ); }
	static Color Blue() { return Color( 0, 0, 255 ); }
	static Color LightBlue() { return Color( 100, 100, 255 ); }
	static Color Grey() { return Color( 128, 128, 128 ); }
	static Color DarkGrey() { return Color( 45, 45, 45 ); }
	static Color Black() { return Color( 0, 0, 0 ); }
	static Color White() { return Color( 255, 255, 255 ); }
	static Color Purple() { return Color( 220, 0, 220 ); }
	static Color Pink() { return Color( 255, 105, 180 ); }

	//Menu
	static Color Background() { return Color( 55, 55, 55 ); }
	static Color FrameBorder() { return Color( 80, 80, 80 ); }
	static Color MainText() { return Color( 230, 230, 230 ); }
	static Color HeaderText() { return Color( 49, 124, 230 ); }
	static Color CurrentTab() { return Color( 55, 55, 55 ); }
	static Color Tabs() { return Color( 23, 23, 23 ); }
	static Color Highlight() { return Color( 49, 124, 230 ); }
	static Color ElementBorder() { return Color( 0, 0, 0 ); }
	static Color SliderScroll() { return Color( 78, 143, 230 ); }


private:
	unsigned char _cl[ 4 ];
};

#endif // !Color_h
