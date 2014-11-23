void set_col(complex** A, complex* col, int j, unsigned int N);
void get_col(complex** A, complex* col, int j , unsigned int N);
complex** generate_matrix(unsigned int N);
int print_1d(complex* K, unsigned int N);
void print_matrix(complex** A, unsigned int N);
bool is_power_of2 (unsigned int N);

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
    complex** A = (complex**)malloc(sizeof(complex_t*) * N);
    srand (static_cast <unsigned> (time(0)));

    for (unsigned int i=0; i<N; i++) {
        A[i] = (complex *) malloc(sizeof(complex_t) * N);

        for (unsigned int j = 0; j<N; j++) {
            A[i][j].r = rand() % 10 + 1;
            A[i][j].i = 0.0;
        }
    }

    return A;
}

int print_1d(complex* K, unsigned int N) {
  cout << "N: " << N << std::endl;
  for (unsigned int i = 0; i<N; i++) {
    cout << "im: " << K[i].i << " re: " << K[i].r <<std::endl;
  }
    return(0);
}

void print_matrix(complex ** A, unsigned int N) {

    for (unsigned int i = 0; i<N; i++) {
        for (unsigned int j = 0; j<N; j++) {
            cout << " re: " << A[i][j].r << " im: " << A[i][j].i;
        }

        cout << std::endl;
    }
}

bool is_power_of2 (unsigned int N)
{
    while (((N & 1) == 0) && N > 1)
        N >>= 1;
    return (N == 1);
}
