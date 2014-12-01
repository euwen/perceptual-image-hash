#include <iostream>

#include "hash.hpp"

double HasherSerial::Hash(complex** imgFFT, int n) {
	std::vector<int> primes = generatePrimes(n);
	//start timing
	double start = timer();

	float counter = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			int max = i > j ? i : j;
			counter += imgFFT[i][j].r * primes[max];
		}
	}

	double sec = timer()-start;
	std::cout << "SerialHash: " << sec << " s" << std::endl;
	return counter;
}

double HasherParallel::Hash(complex** imgFFT,int n) {
	std::vector<int> primes = generatePrimes(n);
	//start timing
	double start = timer();

	float counter = 0;
	#pragma omp parallel for schedule(dynamic) shared(counter) num_threads(_num_parallel)
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
			int max = i > j ? i : j;
			#pragma omp critical
			counter += imgFFT[i][j].r * primes[max];
		}
	}
	double sec = timer()-start;
	std::cout << "ParallelHash("<<_num_parallel<<"): " << sec << " s" << std::endl;
	return counter;
}