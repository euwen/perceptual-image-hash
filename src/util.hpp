#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <ctime>
#include <memory>
#include <cstdlib>

inline double timer(void);
std::vector<int> generatePrimes(int N);
std::vector<std::vector<float>> generateRandomMatrix(int nRow, int nCol);

#endif