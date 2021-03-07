#pragma once

#ifndef math_h

#define math_h

#include "Vector.h"
#include "matrix3x4_t.h"

class math
{
public:
	static float Magnitude(Vector a)
	{
		return sqrt((a.x * a.x) + (a.y * a.y));
	}

	static Vector Normalize(Vector value)
	{
		VMProtectBeginMutation("math::Normalize");

		float num = Magnitude(value);
		if (num != 0.f)
			return value / num;

		VMProtectEnd();

		return Vector(0.f, 0.f, 0.f);
	}

	static void transform_vector(Vector& a, matrix3x4_t& b, Vector& out) {

		VMProtectBeginMutation("math::transform_vector");

		out.x = a.Dot(b.m_flMatVal[0]) + b.m_flMatVal[0][3];
		out.y = a.Dot(b.m_flMatVal[1]) + b.m_flMatVal[1][3];
		out.z = a.Dot(b.m_flMatVal[2]) + b.m_flMatVal[2][3];

		VMProtectEnd();
	}

	static Vector ClampMagnitude(Vector vector, float maxLength)
	{
		VMProtectBeginMutation("math::ClampMagnitude");

		if (Magnitude(vector) > maxLength)
			return Vector(Normalize(vector).x * maxLength, Normalize(vector).y * maxLength, 0);

		VMProtectEnd();

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

	static Vector calculate_angle(const Vector& source, const Vector& destination, const Vector& viewAngles) {

		VMProtectBeginMutation("math::calculate_angle");

		Vector delta = source - destination;
		auto radians_to_degrees = [](float radians) { return radians * 180 / static_cast<float>(M_PI); };
		Vector angles;
		angles.x = radians_to_degrees(atanf(delta.z / std::hypotf(delta.x, delta.y))) - viewAngles.x;
		angles.y = radians_to_degrees(atanf(delta.y / delta.x)) - viewAngles.y;
		angles.z = 0.0f;

		if (delta.x >= 0.0)
			angles.y += 180.0f;

		angles.normalize_aimbot();

		VMProtectEnd();

		return angles;
	}

};

#endif // !math_h
