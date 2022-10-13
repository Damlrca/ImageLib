#include "ImagePlus.h"

// ImageTXT

ImageTXT::ImageTXT() : ImageTXT(0, 0) {}
ImageTXT::ImageTXT(int h, int w) : img(h, w) {}

ImageTXT::ImageTXT(const ImageTXT& _img) : img(_img.img) {}
ImageTXT& ImageTXT::operator=(const ImageTXT& _img) {
	img = _img.img;
	return *this;
}

ImageTXT::ImageTXT(ImageTXT&& _img) noexcept : img (move(_img.img)) {}
ImageTXT& ImageTXT::operator=(ImageTXT&& _img) noexcept {
	img = move(_img.img);
	return *this;
}

int ImageTXT::height() {
	return img.height();
}
int ImageTXT::width() {
	return img.width();
}

unsigned char& ImageTXT::pixel(int _h, int _w) {
	return img.pixel(_h, _w);
}

void ImageTXT::upscale() {
	img.upscale();
}

ImageTXT::~ImageTXT() {}

void ImageTXT::fsave(const char* name) {
	ofstream fout(name);
	fout << img.height() << " " << img.width() << "\n";
	fout << img;
	fout.close();
}

void ImageTXT::fload(const char* name) {
	ifstream fin(name);
	int _h, _w;
	fin >> _h >> _w;
	img.resize(_h, _w);
	fin >> img;
	fin.close();
}

// ImagePlus

ImagePlus::ImagePlus() : ImagePlus(0, 0) {}
ImagePlus::ImagePlus(int h, int w) : Image(h, w) {}

ImagePlus::ImagePlus(const Image& _img) : Image(_img) {}
ImagePlus& ImagePlus::operator=(const Image& _img) {
	Image::operator=(_img);
	return *this;
}

ImagePlus::ImagePlus(Image&& _img) noexcept : Image(move(_img)) {}
ImagePlus& ImagePlus::operator=(Image&& _img) noexcept {
	Image::operator=(move(_img));
	return *this;
}

ImagePlus::ImagePlus(const ImagePlus& _img) : Image(_img) {}
ImagePlus& ImagePlus::operator=(const ImagePlus& _img) {
	Image::operator=(_img);
	return *this;
}

ImagePlus::ImagePlus(ImagePlus&& _img) noexcept : Image(move(_img)) {}
ImagePlus& ImagePlus::operator=(ImagePlus&& _img) noexcept {
	Image::operator=(move(_img));
	return *this;
}

ImagePlus::~ImagePlus() {}

void ImagePlus::fsaveBIN(const char* name) {
	ofstream fout(name, ios_base::binary);
	fout.write(reinterpret_cast<const char*>(&h), sizeof(int));
	fout.write(reinterpret_cast<const char*>(&w), sizeof(int));
	if (arr)
		fout.write(reinterpret_cast<const char*>(arr[0]), sizeof(unsigned char) * h * w);
	fout.close();
}

void ImagePlus::floadBIN(const char* name) {
	ifstream fin(name, ios_base::binary);
	int _h, _w;
	fin.read(reinterpret_cast<char*>(&_h), sizeof(int));
	fin.read(reinterpret_cast<char*>(&_w), sizeof(int));
	resize(_h, _w);
	if (arr)
		fin.read(reinterpret_cast<char*>(arr[0]), sizeof(unsigned char) * h * w);
	fin.close();
}

void ImagePlus::fsaveTXT(const char* name) {
	ofstream fout(name);
	fout << h << " " << w << "\n";
	fout << *this;
	fout.close();
}

void ImagePlus::floadTXT(const char* name) {
	ifstream fin(name);
	int _h, _w;
	fin >> _h >> _w;
	resize(_h, _w);
	fin >> *this;
	fin.close();
}