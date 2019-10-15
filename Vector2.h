#pragma once
//------------------------------------------------------
// A 2d point represented by 2 floating point components
struct Vector2 {
	float X;
	float Y;
	Vector2();
	Vector2(float x, float y);
	float Dot(const Vector2& other);
	float Length();
	float LengthSquared();
	Vector2 Normalized();
	Vector2 Right();
	Vector2 Left();
	void operator+=(const Vector2& b);
	Vector2 operator+(const Vector2& b) const;
	void operator-=(const Vector2& b);
	Vector2 operator-() const;
	Vector2 operator-(const Vector2& b) const;
	void operator*=(const float& scalar);
	Vector2 operator*(const float& scalar) const;
	void operator/=(const float& scalar);
	Vector2 operator/(const float& scalar) const;
};
