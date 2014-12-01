#include <string>
#include <iostream>

#include "fft.hpp"
#include "clFFT\clFFT.h"

class ParallelFFT : public FFT
{
private:
	int PerformCalculations(float** tab, const char* direction, int sizex, int sizey);
	float** GetAsFloatArrays(complex** A, int n);
	complex** GetAsComplexMatrix(float* A[], int n);
public:
	void FFT2D(complex** A, int n);
};