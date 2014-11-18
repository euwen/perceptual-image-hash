#include "util.hpp"

inline double timer(void){
    return std::clock() / (double) CLOCKS_PER_SEC;
}

/**
* Returns N first primes starting with 2
*/
std::vector<int> generatePrimes(int N){
    std::vector<int> pvec;
    int n = 1000;
    while(pvec.size() < N){
        bool isPrime = true;
        for(int i = 2; i < n; i++){
            if(n % i == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime){
            pvec.push_back(n);
        }
        n++;
    }
    return pvec;
}

std::vector<std::vector<float>> generateRandomMatrix(int nRow, int nCol){
    int LO = 1, HI = 100;
    std::vector<std::vector<float>> matrix;
    for(int i = 0; i < nRow; i++){
        std::vector<float> col;
        for(int j = 0; j < nCol; j++){
            float random = LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)));
            col.push_back(random);
        }
        matrix.push_back(col);
    }
    return matrix;
}