#include "pch.h"
#include "Pixel.h"

void Pixel::operator*=(const float & scalar)
{
	R *= scalar;
	G *= scalar;
	B *= scalar;
}

Pixel Pixel::operator+(const Pixel& other)
{
	float otherOpacity = ((float)other.A / 255.f);
	if (otherOpacity == 0.f) {
		return *this;
	}
	if (otherOpacity < 1.f) {
		float opacity = (float)A / 255.f;
		float oneMinusOpacity = 1.f - otherOpacity;
		float divisor = otherOpacity + opacity * oneMinusOpacity;
		return Pixel(
			std::min(255.f, (other.R * otherOpacity + R * opacity * oneMinusOpacity) / divisor),
			std::min(255.f, (other.G * otherOpacity + G * opacity * oneMinusOpacity) / divisor),
			std::min(255.f, (other.B * otherOpacity + B * opacity * oneMinusOpacity) / divisor),
			std::min(255.f, divisor * 255.f)
		);
	}
	else {
		return other;
	}
}
