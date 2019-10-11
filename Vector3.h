#pragma once
#include "Vector2.h"
struct Vector3
{
	Vector3();
	Vector3(float x, float y, float z);
	float Length();
	float LengthSquared();
	float X;
	float Y;
	float Z;
	void operator+=(const Vector3& b);
	Vector3 operator+(const Vector3& b);
	void operator-=(const Vector3& b);
	Vector3 operator-();
	Vector3 operator-(const Vector3& b);
	void operator*=(const float& scalar);
	Vector3 operator*(const float& scalar);
	void operator/=(const float& scalar);
	Vector3 operator/(const float& scalar);
};

