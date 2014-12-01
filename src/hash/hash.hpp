#ifndef HASH_HPP
#define HASH_HPP

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "../fft/util.hpp"

class Hasher {
public:
	Hasher(){}
	virtual double Hash(complex** imgFFT, int n) = 0;
};

class HasherSerial : public Hasher {
public:
	HasherSerial() {}
	double Hash(complex** imgFFT, int n);
};

class HasherParallel : public Hasher {
private:
	int _num_parallel;

public:
	HasherParallel(int num_parallel) : _num_parallel(num_parallel) {}
	double Hash(complex** imgFFT, int n);
};

#endif