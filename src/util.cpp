#include "util.hpp"

double timer(void){
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

//complex number function from polar
complex from_polar(double r, double theta_rads) {
    complex result;
    result.r = r * cos(theta_rads);
    result.i = r * sin(theta_rads);
    return result;
}

double magnitude(complex c) {
    return sqrt(c.r*c.r + c.i*c.i);
}

complex add(complex left, complex right) {
    complex result;
    result.r = left.r + right.r;
    result.i = left.i + right.i;
    return result;
}

complex sub(complex left, complex right) {
    complex result;
    result.r = left.r - right.r;
    result.i = left.i - right.i;
    return result;
}

complex mult(complex left, complex right) {
    complex result;
    result.r = left.r*right.r - left.i*right.i;
    result.i = left.r*right.i + left.i*right.r;
    return result;
}

bool is_power_of2(unsigned int N) {
    while ((N&1)==0 && N>1) {
        N>>=1;
    }
    return N==1;
}

void set_col(complex** A, complex* col, int j, unsigned int N) {

    for (unsigned int i = 0; i < N; ++i) {
        A[i][j] = col[i];
    }

}

void get_col(complex** A, complex* col, int j , unsigned int N){

    for (unsigned int i = 0; i < N; ++i) {
        col[i] = A[i][j];
    }

}

complex** generate_matrix(unsigned int N) {
    complex** A = (complex**)malloc(sizeof(complex*) * N);
    srand (static_cast <unsigned> (time(0)));

    for (unsigned int i=0; i<N; i++) {
        A[i] = (complex *) malloc(sizeof(complex) * N);

        for (unsigned int j = 0; j<N; j++) {
            A[i][j].r = rand() % 10 + 1;
            A[i][j].i = 0.0;
        }
    }

    return A;
}

int print_1d(complex* K, unsigned int N) {
    std::cout << "N: " << N << std::endl;
    for (unsigned int i = 0; i<N; i++) {
        std::cout << "im: " << K[i].i << " re: " << K[i].r <<std::endl;
    }
    return(0);
}

void print_matrix(complex ** A, unsigned int N) {

    for (unsigned int i = 0; i<N; i++) {
        for (unsigned int j = 0; j<N; j++) {
            std::cout << " re: " << A[i][j].r << " im: " << A[i][j].i;
        }

        std::cout << std::endl;
    }
}