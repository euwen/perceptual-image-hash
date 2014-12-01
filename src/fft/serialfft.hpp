#ifndef SFFT_HPP
#define SFFT_HPP

#include "fft.hpp"

class SerialFFT : public FFT {
private :
	complex* FFT1D(complex *x, int N);
public :
	void FFT2D(complex** A, int N);
	void test_serial(complex** A, int N);
};
#endif