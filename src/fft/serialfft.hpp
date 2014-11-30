#ifndef SFFT_HPP
#define SFFT_HPP

complex*FFT1D(complex *x, unsigned int N);
void FFT2D(complex** A, unsigned int N);
void test_serial(unsigned int N);

#endif