#include <iostream>

#include "hash.hpp"

double CPUHasher::Hash(const std::vector<std::vector<float>> &imgFFT) {
    std::vector<int> primes = generatePrimes(imgFFT.size());
    float counter = 0;
    for(int i = 0; i < imgFFT.size(); i++) {
        for(int j = 0; j < imgFFT[i].size(); j++){
            int max = i > j ? i : j;
            counter += imgFFT[i][j] * primes[max];
        }
    }
    return counter;
}