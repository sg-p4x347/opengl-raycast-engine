#include "pch.h"
#include "Bitmap.h"
#include <bitset>
vector<uint8_t> Bitmap::GetOpaqueBitMask()
{
	size_t rowSize = std::ceil((double)m_width / 8.0) * sizeof(uint8_t);
	vector<uint8_t> bits(rowSize * m_height,0);
	for (size_t y = 0; y < m_height; y++) {
		for (size_t x = 0; x < m_width; x++) {
			Pixel pixel = Get(x, y);
			if (pixel.A == 255) {
				size_t byteIndex = x / 8;
				uint8_t & byte = bits[y * rowSize + byteIndex];
				byte = byte + (128 >> (x - byteIndex * 8));
			}
		}
	}
	return bits;
}
