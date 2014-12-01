#ifndef BMP_PROC
#define BMP_PROC

#include <iostream>
#include <vector>

#include "easyBMP\EasyBMP.h"
#include "easyBMP\EasyBMP_BMP.h"
#include "..\fft\util.hpp"

class bmpProcessor
{
private:
	complex **red, **green, **blue;
	int bufferSize;

public:
	char* filename;

	bmpProcessor(char* filename);
	~bmpProcessor();

	int GetSize() { return bufferSize; }

	complex** GetRed() { return red; }
	complex** GetGreen() { return green; }
	complex** GetBlue() { return blue; }
};

#endif
