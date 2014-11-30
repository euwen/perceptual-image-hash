#ifndef FFT_HPP
#define FFT_HPP

#define PARALLEL_FFT

#ifdef PARALLEL_FFT
#include "parallelFFt.h"

void img2fftCPU(float** dest, int** img, int N);
void img2fftGPU(float** dest, int** img, int N);

#endif