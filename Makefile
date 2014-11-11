main: fft hash
	g++ -o main main.cpp fft.o hash.o

fft:
	g++ -c -o fft.o fft.cpp

hash:
	g++ -c -o hash.o hash.cpp
