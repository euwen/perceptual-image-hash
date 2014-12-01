#include <string>
#include <iostream>

#include "fft.hpp"

// I do not want you to include this if you're not ready for
// Some openCL madness. So don't set PARALLEL_EXEC to 1 if you don't,
// YOU FOOL.

#if PARALLEL_EXEC == 1
#include "clFFT\clFFT.h"
#endif

class ParallelFFT : public FFT
{
private:
	int PerformCalculations(float** tab, const char* direction, int sizex, int sizey);
	float** GetAsFloatArrays(complex** A, int n);
	complex** GetAsComplexMatrix(float* A[], int n);
public:
	void FFT2D(complex** A, int n);
};