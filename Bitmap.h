#pragma once
#include "pch.h"
#include "Pixel.h"

class Bitmap {
public:
	Bitmap(size_t width, size_t height) : m_width(width), m_height(height), m_pixels(new Pixel[width * height * sizeof(Pixel)]) {}
	Bitmap(const Bitmap&& other) : Bitmap::Bitmap(other.m_width, other.m_height) {
		std::memcpy(m_pixels, other.m_pixels, other.m_height * other.m_height * sizeof(Pixel));
	}
	~Bitmap() { delete[] m_pixels; }
	static Bitmap FromFile(string file) {
		// Open the file
		ifstream bmp(file, std::ios::binary);

		if (bmp.is_open()) {
			char headerField[2];
			bmp.read((char*)&headerField, sizeof(headerField));
			if (headerField[0] == 'B' && headerField[1] == 'M') {

				bmp.seekg(10); // Data offset
				int dataOffset;
				bmp.read((char*)&dataOffset, sizeof(dataOffset));
				int width;
				int height;
				bmp.seekg(18); // Width
				bmp.read((char*)&width, sizeof(width));
				bmp.read((char*)&height, sizeof(height));
				Bitmap bitmap(width, height);
				bmp.seekg(28); // bits per pixel (must be 32)
				unsigned short bitsPerPixel;
				bmp.read((char*)&bitsPerPixel, sizeof(bitsPerPixel));
				if (bitsPerPixel == sizeof(Pixel) * 8) {
					size_t pixelCount = width * height;
					bmp.seekg(dataOffset);
					for (size_t pixelIndex = 0; pixelIndex < pixelCount; pixelIndex++) {
						uint8_t a, r, g, b;
						bmp.read((char*)&b, sizeof(b));
						bmp.read((char*)&g, sizeof(g));
						bmp.read((char*)&r, sizeof(r));
						bmp.read((char*)&a, sizeof(a));
						bitmap.m_pixels[pixelIndex] = Pixel(r, g, b, a);
					}

				}


				return bitmap;
			}

		}
		return Bitmap(0, 0);
	}
	Pixel Get(int x, int y) const {
		if (x >= 0 && x < m_width && y >= 0 && y < m_height) {
			return m_pixels[y * m_width + x];
		}
		else {
			return Pixel(0, 0, 0, 0);
		}
		
	}
	void Set(size_t x, size_t y, Pixel&& pixel) {
		m_pixels[y * m_width + x] = pixel;
	}
	void Set(size_t x, size_t y, Pixel& pixel) {
		Set(x, y, std::move(pixel));
	}
	void Set(size_t x, size_t y, size_t width, size_t height, Pixel& pixel) {
		for (size_t rectX = x; rectX < x + width; rectX++) {
			for (size_t rectY = y; rectY < y + height; rectY++) {
				Set(rectX, rectY, std::move(pixel));
			}
		}
	}
	void Add(size_t x, size_t y, Pixel& pixel) {
		Set(x, y, Get(x, y) + pixel);
	}
	void Add(size_t x, size_t y, size_t width, size_t height, Pixel& pixel) {
		for (size_t rectX = x; rectX < x + width; rectX++) {
			for (size_t rectY = y; rectY < y + height; rectY++) {
				Add(rectX, rectY, pixel);
			}
		}
	}
	
	Pixel* GetPixels() { return m_pixels; }
	size_t GetWidth() { return m_width; }
	size_t GetHeight() { return m_height; }
	vector<uint8_t> GetOpaqueBitMask();
private:
	const size_t m_width;
	const size_t m_height;
	Pixel* m_pixels;
};