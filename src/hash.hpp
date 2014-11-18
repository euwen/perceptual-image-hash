#ifndef HASH_HPP
#define HASH_HPP

#include <vector>
#include <memory>

#include "util.hpp"

class Hasher {
public:
    Hasher(){}
    virtual double Hash(const std::vector<std::vector<float>> &imgFFT) = 0;
};

class CPUHasher : public Hasher {
public:
    CPUHasher() {}
    double Hash(const std::vector<std::vector<float>> &imgFFT);
};

#endif