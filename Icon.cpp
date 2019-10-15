#include "pch.h"
#include "Icon.h"


void Icon::fileHandler(string fname)
{
	ifstream inFile = ifstream();
	inFile.open(fname);
	if (inFile.is_open()) {
		for (int row = 0; row < HEIGHT; ++row) {
			for (int column = 0; column < WIDTH; ++column) {
				for (int color = 0; color < 3; ++color) {
					inFile >> imagePixels[row][column][color];
				}
			}
		}
		inFile.close();
	}
}

Icon::Icon()
{
	
}
