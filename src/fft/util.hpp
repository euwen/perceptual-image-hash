#ifndef UTIL_HPP
#define UTIL_HPP

#include <vector>
#include <ctime>
#include <memory>
#include <cstdlib>
#include <math.h>
#include <ostream>
#include <iostream>

#define PI 3.1415926535897932

float timer(void);
std::vector<int> generatePrimes(int N);
std::vector<std::vector<float>> generateRandomMatrix(int nRow, int nCol);

struct complex {
	float r;
	float i;
};

complex from_polar(float r, float theta_rads);
float  magnitude(complex c);
complex add(complex left, complex right);
complex sub(complex left, complex right);
complex mult(complex left, complex right);

bool is_power_of2(unsigned int N);
void set_col(complex** A, complex* col, int j, unsigned int N);
void get_col(complex** A, complex* col, int j , unsigned int N);
complex** generate_matrix(unsigned int N);
int print_1d(complex* K, unsigned int N);
void print_matrix(complex** A, unsigned int N);

complex** allocateComplexMatrix(int n);

#endif
