#include <iostream>

#include "hash.hpp"

double HasherSerial::Hash(const std::vector<std::vector<float>> &imgFFT) {
    std::vector<int> primes = generatePrimes(imgFFT.size());
    //start timing
    double start = timer();

    float counter = 0;
    for(int i = 0; i < imgFFT.size(); i++) {
        for(int j = 0; j < imgFFT[i].size(); j++){
            int max = i > j ? i : j;
            counter += imgFFT[i][j] * primes[max];
        }
    }

    double sec = timer()-start;
    std::cout << "SerialHash: " << sec << " s" << std::endl;
    return counter;
}

double HasherParallel::Hash(const std::vector<std::vector<float>> &imgFFT) {
    std::vector<int> primes = generatePrimes(imgFFT.size());
    //start timing
    double start = timer();

    float counter = 0;
    #pragma omp parallel for schedule(dynamic) shared(counter) num_threads(_num_parallel)
    for(int i = 0; i < imgFFT.size(); i++) {
        float temp = 0;
        for(int j = 0; j < imgFFT[i].size(); j++){
            int max = i > j ? i : j;
            temp += imgFFT[i][j] * primes[max];
        }
        #pragma omp critical
        counter += temp;
    }
    double sec = timer()-start;
    std::cout << "ParallelHash("<<_num_parallel<<"): " << sec << " s" << std::endl;
    return counter;
}