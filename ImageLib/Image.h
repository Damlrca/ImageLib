#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class image_err {};
class size_err : public image_err {};
class index_err : public image_err {};

class Image {
protected:
	int h;
	int w;
	unsigned char** arr;
private:
	unsigned char** img_alloc(int h, int w);
	void img_delete(unsigned char** arr);
public:
	Image();
	Image(int _h, int _w);

	Image(const Image& img);
	Image& operator=(const Image& img);

	Image(Image&& img) noexcept;
	Image& operator=(Image&& img) noexcept;

	int height();
	int width();
	unsigned char& pixel(int _h, int _w);

	void upscale();
	void resize(int _h, int _w);

	~Image();

	friend ostream& operator<<(ostream& out, const Image& img);
	friend istream& operator>>(istream& in, Image& img);

	void fsaveBIN(const char* name);
	void floadBIN(const char* name);
	void fsaveTXT(const char* name);
	void floadTXT(const char* name);
};