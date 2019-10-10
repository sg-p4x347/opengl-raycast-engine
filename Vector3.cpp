#include "pch.h"
#include "Vector3.h"

Vector3::Vector3() : Vector3::Vector3(0.f,0.f,0.f)
{
}

Vector3::Vector3(float x, float y, float z): X(x), Y(y), Z(z)
{
}

void Vector3::operator+=(const Vector3& b)
{
	X += b.X;
	Y += b.Y;
	Z += b.Z;
}

Vector3 Vector3::operator+(const Vector3& b)
{
	return Vector3(X + b.X, Y + b.Y, Z + b.Z);
}

void Vector3::operator-=(const Vector3& b)
{
	X -= b.X;
	Y -= b.Y;
	Z -= b.Z;
}

Vector3 Vector3::operator-()
{
	return Vector3(-X,-Y,-Z);
}

Vector3 Vector3::operator-(const Vector3& b)
{
	return Vector3(X - b.X, Y - b.Y, Z - b.Z);;
}

void Vector3::operator*=(const float& scalar)
{
	X *= scalar;
	Y *= scalar;
	Z *= scalar;
}

Vector3 Vector3::operator*(const float& scalar)
{
	return Vector3(X * scalar, Y * scalar, Z * scalar);
}

void Vector3::operator/=(const float& scalar)
{
	X /= scalar;
	Y /= scalar;
	Z /= scalar;
}

Vector3 Vector3::operator/(const float& scalar)
{
	return Vector3(X / scalar, Y / scalar, Z / scalar);
}
