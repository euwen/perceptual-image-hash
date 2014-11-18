#ifndef FFT_HPP
#define FFT_HPP

void img2fftCPU(float** dest, int** img, int N);
void img2fftGPU(float** dest, int** img, int N);

#endif