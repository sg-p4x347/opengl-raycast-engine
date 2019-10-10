#pragma once
struct Pixel {
	Pixel() : Pixel::Pixel(0, 0, 0, 0) {}
	Pixel(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : R(r), G(g), B(b), A(a) {}
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t A;
	void operator*=(const float & scalar);
	Pixel operator+(const Pixel& other);
};

