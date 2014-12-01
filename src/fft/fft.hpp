#ifndef FFT_HPP
#define FFT_HPP

#include "util.hpp"

class FFT {
public:
	virtual void FFT2D(complex** img, int N) = 0;
};

#endif