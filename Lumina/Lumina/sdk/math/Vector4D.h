#pragma once

class Vector4D					
{
public:
	// Members
	float x, y, z, w;

	inline float* Base();
	inline float const* Base() const;

	float operator[](int i) const;
	float& operator[](int i);

	inline Vector2D get_pos() const;
	inline Vector2D get_size() const;
};

inline float* Vector4D::Base()
{
	return (float*)this;
}

inline float const* Vector4D::Base() const
{
	return (float const*)this;
}

inline float& Vector4D::operator[](int i)
{
	Assert( (i >= 0) && (i < 4) );
	return ((float*)this)[i];
}

inline float Vector4D::operator[](int i) const
{
	Assert( (i >= 0) && (i < 4) );
	return ((float*)this)[i];
}

inline Vector2D Vector4D::get_pos() const
{
	return Vector2D(x, y);
}

inline Vector2D Vector4D::get_size() const
{
	return Vector2D(z, w);
}