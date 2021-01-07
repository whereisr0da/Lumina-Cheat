#pragma once

struct Vector2D
{
public:
	float x, y;

	Vector2D() {}
	Vector2D( float x_, float y_ ) { x = x_; y = y_; }
	Vector2D( float x_, float y_, float z_ ) { x = x_; y = y_; }
	__forceinline Vector2D&	operator+=( const Vector2D &v );
	__forceinline Vector2D&	operator-=( const Vector2D &v );
	__forceinline Vector2D&	operator*=( const Vector2D &v );
	__forceinline Vector2D&	operator*=( float s );
	__forceinline Vector2D&	operator/=( const Vector2D &v );
	__forceinline Vector2D&	operator/=( float s );
	__forceinline Vector2D&	operator+=( float fl );
	__forceinline Vector2D&	operator-=( float fl );
	__forceinline Vector2D	operator+( float fl ) const;
	__forceinline Vector2D  operator+( Vector2D v ) const;
	__forceinline Vector2D	operator-( float fl ) const;
	__forceinline Vector2D  operator-( Vector2D v ) const;
	__forceinline Vector2D	operator/( float fl ) const;
	inline float	Length() const;
};

//===============================================
__forceinline  Vector2D& Vector2D::operator+=( const Vector2D& v )
{
	x += v.x; y += v.y;
	return *this;
}
//===============================================
__forceinline  Vector2D& Vector2D::operator-=( const Vector2D& v )
{
	x -= v.x; y -= v.y;
	return *this;
}
//===============================================
__forceinline  Vector2D& Vector2D::operator*=( float fl )
{
	x *= fl;
	y *= fl;
	return *this;
}
//===============================================
__forceinline  Vector2D& Vector2D::operator*=( const Vector2D& v )
{
	x *= v.x;
	y *= v.y;
	return *this;
}
//===============================================
__forceinline Vector2D&	Vector2D::operator+=( float fl )
{
	x += fl;
	y += fl;
	return *this;
}
//===============================================
__forceinline Vector2D&	Vector2D::operator-=( float fl )
{
	x -= fl;
	y -= fl;
	return *this;
}

//===============================================
__forceinline Vector2D Vector2D::operator+( float fl ) const
{
	return Vector2D( x + fl, y + fl );
}

//===============================================
__forceinline Vector2D Vector2D::operator+( Vector2D v ) const
{
	return Vector2D( x + v.x, y + v.y );
}

//===============================================
__forceinline Vector2D Vector2D::operator-( float fl ) const
{
	return Vector2D( x - fl, y - fl );
}
//===============================================
__forceinline Vector2D Vector2D::operator-( Vector2D v ) const
{
	return Vector2D( x - v.x, y - v.y );
}
//===============================================
__forceinline Vector2D Vector2D::operator/( float fl ) const
{
	return Vector2D( x / fl, y / fl );
}
//===============================================
__forceinline  Vector2D& Vector2D::operator/=( float fl )
{
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	return *this;
}
//===============================================
__forceinline  Vector2D& Vector2D::operator/=( const Vector2D& v )
{
	x /= v.x;
	y /= v.y;
	return *this;
}

//===============================================
inline float Vector2D::Length( void ) const
{
	float root = 0.0f;

	float sqsr = x * x + y * y;

	__asm sqrtss xmm0, sqsr
	__asm movss root, xmm0

	return root;
}