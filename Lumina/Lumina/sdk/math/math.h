#pragma once

#ifndef math_h

#define math_h

#include "Vector.h"

class math
{
public:
	static float Magnitude(Vector a)
	{
		return sqrt((a.x * a.x) + (a.y * a.y));
	}

	static Vector Normalize(Vector value)
	{
		float num = Magnitude(value);
		if (num != 0.f)
			return value / num;
		return Vector(0.f, 0.f, 0.f);
	}

	static Vector ClampMagnitude(Vector vector, float maxLength)
	{
		if (Magnitude(vector) > maxLength)
			return Vector(Normalize(vector).x * maxLength, Normalize(vector).y * maxLength, 0);
		return vector;
	}

	static void vector_angles(const Vector& forward, Vector& angles)
	{
		VMProtectBeginMutation("math::vector_angles");

		Vector view;

		if (!forward[0] && !forward[1])
		{
			view[0] = 0.0f;
			view[1] = 0.0f;
		}
		else
		{
			view[1] = atan2(forward[1], forward[0]) * 180.0f / M_PI;

			if (view[1] < 0.0f)
				view[1] += 360.0f;

			view[2] = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			view[0] = atan2(forward[2], view[2]) * 180.0f / M_PI;
		}

		angles[0] = -view[0];
		angles[1] = view[1];
		angles[2] = 0.f;

		VMProtectEnd();
	}

	static void angle_vectors(const Vector& angles, Vector& forward)
	{
		VMProtectBeginMutation("math::angle_vectors");

		float sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));

		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward.x = cp * cy;
		forward.y = cp * sy;
		forward.z = -sp;

		VMProtectEnd();
	}

};

#endif // !math_h
