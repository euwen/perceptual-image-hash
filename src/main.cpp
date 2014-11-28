#include <iostream>
#include <ctime>
#include <string.h>

#include "util.hpp"
#include "hash.hpp"
#include "serialfft.hpp"

int main(int argc, char** argv) {
    if (argc < 1) {
        std::cout << "usage: ./percephash N" << std::endl;
        return -1;
    }
    srand (static_cast <unsigned> (time(0)));
    unsigned int N = strtol(argv[1], NULL, 10);

    if (!is_power_of2(N)) {
        std::cout << "N must be a power of 2" << std::endl;
        return -1;
    }
    std::vector<std::vector<float>> matrix = generateRandomMatrix(N, N);

    test_serial(N);

    HasherSerial hasherSerial;
    hasherSerial.Hash(matrix);

    std::vector<int> numThreads{2, 4, 8, 16};
    for(auto nt = numThreads.begin(); nt != numThreads.end(); nt++){
        HasherParallel hasher(*nt);
        hasher.Hash(matrix);
    }
    return 0;
}
