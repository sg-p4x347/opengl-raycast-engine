#pragma once
#include "pch.h"

class Icon
{
public:
	static const int HEIGHT = 128;
	static const int WIDTH = 128;

	GLfloat imagePixels[HEIGHT][WIDTH][3];

	void fileHandler(string fname);

	Icon();
};

