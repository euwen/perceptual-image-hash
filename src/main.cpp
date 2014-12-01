#include <iostream>
#include <ctime>
#include <string.h>

#include "fft/util.hpp"
#include "hash/hash.hpp"
#include "fft/serialfft.hpp"
#include "fft/parallelfft.hpp"
#include "bmp/bmpProcess.hpp"

#define PARALLEL_EXEC 1

#if PARALLEL_EXEC == 1
extern "C" {
	_declspec(dllexport) unsigned int NvOptimusEnablement = 0x00000001;
}
#endif

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cout << "usage: ./percephash \"filename.bmp\".\n" << std::endl;
		return -1;
	}
	srand (static_cast <unsigned> (time(0)));

	bmpProcessor bmp(argv[1]);

	int N = bmp.GetSize();

	if (!is_power_of2(N)) {
		std::cout << "N must be a power of 2" << std::endl;
		return -1;
	}
	complex** redMatrix = bmp.GetRed();
	complex** greenMatrix = bmp.GetGreen();
	complex** blueMatrix = bmp.GetBlue();

	FFT* fft = NULL;

	if (PARALLEL_EXEC == 0)
		fft = new SerialFFT();
	else
		fft = new ParallelFFT();

	fft->FFT2D(redMatrix, N);

	HasherSerial hasherSerial;
	hasherSerial.Hash(redMatrix, N);

	std::vector<int> numThreads{2, 4, 8, 16};
	for(auto nt = numThreads.begin(); nt != numThreads.end(); nt++){
		HasherParallel hasher(*nt);
		hasher.Hash(redMatrix, N);
	}
	return 0;
}
