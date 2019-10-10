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
	float opacity = ((float)other.A / 255);
	if (opacity < 1.f) {
		return Pixel(std::min(255.f, R + other.R * opacity), std::min(255.f, G + other.G * opacity), std::min(255.f, B + other.B * opacity), std::min(255, A + other.A));
	}
	else {
		return other;
	}
}
