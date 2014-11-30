#ifndef HASH_HPP
#define HASH_HPP

#include <vector>
#include <map>
#include <memory>
#include <iostream>

#include "util.hpp"

class Hasher {
public:
    Hasher(){}
    virtual double Hash(const std::vector<std::vector<float>> &imgFFT) = 0;
};

class HasherSerial : public Hasher {
public:
    HasherSerial() {}
    double Hash(const std::vector<std::vector<float>> &imgFFT);
};

class HasherParallel : public Hasher {
private:
    int _num_parallel;

public:
    HasherParallel(int num_parallel) : _num_parallel(num_parallel) {}
    double Hash(const std::vector<std::vector<float>> &imgFFT);
};

#endif