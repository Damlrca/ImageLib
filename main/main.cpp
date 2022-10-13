#include <iostream>
#include <fstream>
#include "Image.h"
#include "ImagePlus.h"
using namespace std;

class WhiteFill {
public:
	unsigned char operator() (int x, int y) {
		return 255;
	}
};

class ChessFill {
public:
	unsigned char operator() (int x, int y) {
		return (x + y) % 2 ? 255 : 0;
	}
};

//Ћ€мбды!
template<class F>
void fill(Image& img, F& met) {
	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++)
			img.pixel(i, j) = met(i, j);
}

int main() {
	// в будущем
	// битовые множества
	// unn-itmm-software/mp2-lab1-test
	
	// git
	// https://git-scm.com/
	// tortoise git

	// fork
	// kozinove

	//master //->рабоча€ ветка

	// Image
	// git -> bitfield

	// 
	// b = a & (1 << 2 - 1); // b = a % 4
	// 
	// add n
	// a |= (1 << n)
	// 
	// delete n
	// a &= ~(1 << n)
	// 
	// n = N >> 5 + (N & (1 << 5) - 1 != 0);
	// 
	// n = (N + 31) / 32;
	// n = (N + S - 1) / S;
	// 
	// n = (N + (1 << sizeof(int)???) - 1) >> (sizeof(int) + 1);
	// / 2 ^ (sizeof(int) * 8)
	// >> (sizeof(int) << 3) // неправильно, это делим на 2^32, нужно 2^p == 32
	// >> sizeof(int) == 4 + 1 ??
	// >> sizeof(short) == 2 + 2 ??
	// >> sizeof(long long) = 8 - 2 ??
	// sizeof(TYPE) == 2 ^ (p - 3) : размер типа данных в битах. // 00000001000
	// 

	return 0;
}

