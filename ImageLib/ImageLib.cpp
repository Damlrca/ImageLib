#include "ImageLib.h"
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace ImageLib;
using namespace std;

unsigned char** Image::img_alloc(size_t h, size_t w) {
	if (h == 0 || w == 0)
		return nullptr;

	unsigned char** arr = new unsigned char* [h];
	try {
		arr[0] = new unsigned char[h * w];
	}
	catch (...) {
		delete[] arr;
		throw;
	}

	for (int i = 1; i < h; i++)
		arr[i] = arr[0] + i * w;

	return arr;
}

void Image::img_delete(unsigned char** arr) {
	if (arr) {
		delete[] arr[0];
		delete[] arr;
	}
}

Image::Image() : Image(0, 0) {}
Image::Image(size_t _h, size_t _w) {
	h = _h;
	w = _w;
	arr = img_alloc(h, w);
	if (arr)
		memset(arr[0], 0, h * w);
}

Image::Image(const Image& img) {
	h = img.h;
	w = img.w;
	arr = img_alloc(h, w);
	if (arr)
		memcpy(arr[0], img.arr[0], h * w);
}

Image& Image::operator=(const Image& img) {
	if (this == &img)
		return *this;

	unsigned char** temp = img_alloc(img.h, img.w);
	img_delete(arr);
	arr = temp;
	h = img.h;
	w = img.w;
	if (arr)
		memcpy(arr[0], img.arr[0], h * w);
	return *this;
}

Image::Image(Image&& img) noexcept {
	h = img.h;
	w = img.w;
	arr = img.arr;

	img.h = img.w = 0;
	img.arr = nullptr;
}

Image& Image::operator=(Image&& img) noexcept {
	img_delete(arr);

	h = img.h;
	w = img.w;
	arr = img.arr;

	img.h = img.w = 0;
	img.arr = nullptr;

	return *this;
}

void Image::resize(size_t _h, size_t _w) {
	unsigned char** temp_arr = img_alloc(_h, _w);
	img_delete(arr);
	h = _h;
	w = _w;
	arr = temp_arr;
	if (arr)
		memset(arr[0], 0, h * w);
}

Image::~Image() {
	img_delete(arr);
}

ostream& ImageLib::operator<<(ostream& out, const Image& img) {
	if (img.arr)
		for (int i = 0; i < img.h; i++) {
			for (int j = 0; j < img.w; j++) {
				out << setw(3) << static_cast<int>(img.arr[i][j]) << (j + 1 < img.w ? ' ' : '\n');
			}
		}
	return out;
}

istream& ImageLib::operator>>(istream& in, Image& img) {
	int temp;
	if (img.arr)
		for (int i = 0; i < img.h; i++)
			for (int j = 0; j < img.w; j++) {
				in >> temp;
				img.arr[i][j] = static_cast<unsigned char>(temp);
			}
	return in;
}

void Image::fsaveBIN(const char* name) const {
	ofstream fout(name, ios_base::binary);
	fout.write(reinterpret_cast<const char*>(&h), sizeof(int));
	fout.write(reinterpret_cast<const char*>(&w), sizeof(int));
	if (arr)
		fout.write(reinterpret_cast<const char*>(arr[0]), sizeof(unsigned char) * h * w);
	fout.close();
}

void Image::floadBIN(const char* name) {
	ifstream fin(name, ios_base::binary);
	int _h, _w;
	fin.read(reinterpret_cast<char*>(&_h), sizeof(int));
	fin.read(reinterpret_cast<char*>(&_w), sizeof(int));
	resize(_h, _w);
	if (arr)
		fin.read(reinterpret_cast<char*>(arr[0]), sizeof(unsigned char) * h * w);
	fin.close();
}

void Image::fsaveTXT(const char* name) const {
	ofstream fout(name);
	fout << h << " " << w << "\n";
	fout << *this;
	fout.close();
}

void Image::floadTXT(const char* name) {
	ifstream fin(name);
	int _h, _w;
	fin >> _h >> _w;
	resize(_h, _w);
	fin >> *this;
	fin.close();
}
