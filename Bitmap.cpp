#include "pch.h"
#include "Bitmap.h"
#include <bitset>
vector<uint8_t> Bitmap::GetOpaqueBitMask()
{
	size_t rowSize = std::ceil((float)m_width / 8.f) * sizeof(uint8_t);
	vector<uint8_t> bits(rowSize * m_height);
	for (size_t y = 0; y < m_height; y++) {
		vector<bool> row;
		for (size_t x = 0; x < m_width; x++) {
			Pixel pixel = Get(x, y);
			if (pixel.A == 255) {
				row.push_back(true);
			}
			else {
				row.push_back(false);
			}
		}
		std::memcpy(&bits[y * rowSize], &row[0], rowSize);
	}
	return bits;
}
