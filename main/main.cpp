#include <iostream>
#include <fstream>
#include "ImageLib.h"
using namespace std;
using namespace ImageLib;

class WhiteFill {
public:
	unsigned char operator() (int x, int y) {
		return 255;
	}
};

class ChessFill {
public:
	unsigned char operator() (int x, int y) {
		return ((x + y) & 1) ? 255 : 0;
	}
};

template<class F>
void fill(Image& img, F& met) {
	for (int i = 0; i < img.height(); i++)
		for (int j = 0; j < img.width(); j++)
			img.px(i, j) = met(i, j);
}

int main() {
	Image t(20, 20);
	fill(t, [](int x, int y) {	return (x + y) % 3; });
	cout << t;
	return 0;
}

