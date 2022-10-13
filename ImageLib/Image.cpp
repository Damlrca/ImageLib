#include "Image.h"

unsigned char** Image::img_alloc(int h, int w) {
	if (h < 0 || w < 0)
		throw size_err{};

	if (h == 0 || w == 0)
		return nullptr;

	unsigned char** arr = new unsigned char* [static_cast<size_t>(h)];
	try {
		arr[0] = new unsigned char[static_cast<size_t>(h) * static_cast<size_t>(w)];
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
Image::Image(int _h, int _w) {
	h = _h;
	w = _w;
	arr = img_alloc(h, w);
	if (arr)
		memset(arr[0], 0, static_cast<size_t>(h) * static_cast<size_t>(w));
}

Image::Image(const Image& img) {
	h = img.h;
	w = img.w;
	arr = img_alloc(h, w);
	if (arr)
		memcpy(arr[0], img.arr[0], static_cast<size_t>(h) * static_cast<size_t>(w));
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
		memcpy(arr[0], img.arr[0], static_cast<size_t>(h) * static_cast<size_t>(w));
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

int Image::height() { return h; };

int Image::width() { return w; };

unsigned char& Image::pixel(int _h, int _w) {
	if (_h < 0 || _h >= h || _w < 0 || _w >= w)
		throw index_err{};
	return arr[_h][_w];
}

void Image::upscale() {
	if (h == 0 || w == 0)
		return;

	unsigned char** temp_arr = img_alloc(h + h, w + w);

	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			temp_arr[i + i][j + j] = arr[i][j];
	
	img_delete(arr);
	arr = temp_arr;
	h += h;
	w += w;

	// integral promotion !
	for (int i = 0; i < h; i += 2)
		for (int j = 1; j < w; j += 2)
			temp_arr[i][j] = j + 1 < w ? (temp_arr[i][j - 1] + temp_arr[i][j + 1]) / 2 : temp_arr[i][j - 1];
	for (int i = 1; i < h; i += 2)
		for (int j = 0; j < w; j++)
			temp_arr[i][j] = i + 1 < h ? (temp_arr[i - 1][j] + temp_arr[i + 1][j]) / 2 : temp_arr[i - 1][j];
}

void Image::resize(int _h, int _w) {
	unsigned char** temp_arr = img_alloc(_h, _w);
	img_delete(arr);
	h = _h;
	w = _w;
	arr = temp_arr;
	if (arr)
		memset(arr[0], 0, static_cast<size_t>(h) * static_cast<size_t>(w));
}

Image::~Image() {
	img_delete(arr);
}

ostream& operator<<(ostream& out, const Image& img) {
	if (img.arr)
		for (int i = 0; i < img.h; i++) {
			for (int j = 0; j < img.w; j++) {
				out << setw(3) << static_cast<int>(img.arr[i][j]) << (j + 1 < img.w ? ' ' : '\n');
			}
		}
	return out;
}

istream& operator>>(istream& in, Image& img) {
	int temp;
	if (img.arr)
		for (int i = 0; i < img.h; i++)
			for (int j = 0; j < img.w; j++) {
				in >> temp;
				img.arr[i][j] = static_cast<unsigned char>(temp);
			}
	return in;
}