#include <iostream>
#include <ctime>
#include <string.h>

#include "util.hpp"
#include "hash.hpp"
#include "serialfft.hpp"

int main(int argc, char** argv) {
    if (argc<2) {
        std::cout << "usage: ./percephash N [-s]" << std::endl;
        return(-1);
    }

    unsigned int N = strtol(argv[1], NULL, 10);
    if (!is_power_of2(N)) {
        std::cout << "N must be a power of 2" << std::endl;
        return(-1);
    }

    if (strcmp(argv[2], "-s")==0) {
        test_serial(N);
        return(0);
    }

    srand (static_cast <unsigned> (time(0)));

    HasherParallel hasher(16);
    std::vector<std::vector<float>> matrix = generateRandomMatrix(N, N);
    std::cout<<hasher.Hash(matrix)<<std::endl;
    return 0;
}
