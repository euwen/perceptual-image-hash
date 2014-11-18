#include <iostream>
#include <cstdlib>
#include <ctime>

#include "hash.hpp"
#include "util.hpp"

int main(){
    srand (static_cast <unsigned> (time(0)));

    CPUHasher hasher;
    std::vector<std::vector<float>> matrix = generateRandomMatrix(1000, 1000);
    std::cout<<hasher.Hash(matrix)<<std::endl;
    return 0;
}
