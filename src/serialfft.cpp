#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <time.h>
using namespace std;
#include "complex_ops.h"
#include "serialutils.h"

complex*FFT1D(complex *x, unsigned int N);
void FFT2D(complex** A, unsigned int N);

int main(int argc, char** argv) {
    if (argc!=2) {
        cout << "usage: ./serialfft N" << std::endl;
        exit(-1);
    }

    unsigned int N = strtol(argv[1], NULL, 10);
    if (!is_power_of2(N)) {
        cout << "N must be a power of 2" << std::endl;
        exit(-1);
    }

    cout << "N: " << N << std::endl;

    //start timing
    clock_t start = clock(), diff;

    complex** A = generate_matrix(N);

    //cout << "orig matrix: " << std::endl;
    //print_matrix(A,N);
    FFT2D(A,N);

    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    cout << "Time taken: " << msec << " ms" << std::endl;

    //cout<<"new matrix:" <<std::endl;
    //print_matrix(A,N);

    return(0);
}

complex* FFT1D(complex *x, unsigned int N) {
    complex* F = (complex*) malloc(sizeof(struct complex_t) * N);
    complex * d, * e, * D, * E;
    unsigned int k;

    //base case
    if (N == 1) {
        F[0] = x[0];
        return F;
    }

    //create 2 arrays for odd and even terms
    e = (complex*) malloc(sizeof(struct complex_t) * N/2);
    d = (complex*) malloc(sizeof(struct complex_t) * N/2);

    for(k = 0; k < N/2; k++) {
        e[k] = x[2*k];
        d[k] = x[2*k + 1];
    }

    //run FFt recursively
    E = FFT1D(e, N/2);
    D = FFT1D(d, N/2);

    //X_k = E_k+twiddle*D_k
    //X_k+N/2 = E_k-twiddle*D_k
    for(k = 0; k < N/2; k++) {
        D[k] = mult(from_polar(1, -2.0*PI*k/N), D[k]);
        F[k]       = add(E[k], D[k]);
        F[k + N/2] = sub(E[k], D[k]);
    }

    free(D);
    free(E);
    free(d);
    free(e);
    return F;
}

void FFT2D(complex** A, unsigned int N) {

    //run fft on all rows in place
    for (unsigned int i=0; i<N; i++) {
        A[i] = FFT1D(A[i], N);
    }

    //buffer for reading columns in
    complex* col_buf = (complex*)malloc(sizeof(complex)*N);

    //run fft on all columns in place
    for (unsigned int j=0; j<N; j++) {
        get_col(A, col_buf, j, N);
        set_col(A, FFT1D(col_buf, N), j, N);
    }

    free(col_buf);
}
