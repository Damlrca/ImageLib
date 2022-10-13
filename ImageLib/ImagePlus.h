#pragma once
#include "Image.h"
#include <fstream>

// агрегация
// нет в ней никакого смысла, поэтому даже не тестирую в gtest
class ImageTXT {
private:
	Image img;
public:
	ImageTXT();
	ImageTXT(int h, int w);

	ImageTXT(const ImageTXT& _img);
	ImageTXT& operator=(const ImageTXT& _img);

	ImageTXT(ImageTXT&& _img) noexcept;
	ImageTXT& operator=(ImageTXT&& _img) noexcept;

	// конструкторы привидения типов? ImageTXT <- Image
	// но тогда нужно сделать и обратные функции? ImageTXT -> Image 
	
	// !!!
	// лучше уж использовать наследование!
	// !!!

	int height();
	int width();
	unsigned char& pixel(int _h, int _w);
	
	void upscale();

	~ImageTXT();

	void fsave(const char* name);
	void fload(const char* name);

	friend ostream& operator<<(ostream& out, const ImageTXT& img) { return operator<<(out, img.img); };
	friend istream& operator>>(istream& in, ImageTXT& img) { return operator>>(in, img.img); };
};

class ImagePlus : public Image {
public:
	ImagePlus();
	ImagePlus(int h, int w);

	ImagePlus(const Image& _img);
	ImagePlus& operator=(const Image& _img);

	ImagePlus(Image&& _img) noexcept;
	ImagePlus& operator=(Image&& _img) noexcept;

	ImagePlus(const ImagePlus& _img);
	ImagePlus& operator=(const ImagePlus& _img);

	ImagePlus(ImagePlus&& _img) noexcept;
	ImagePlus& operator=(ImagePlus&& _img) noexcept;

	~ImagePlus();

	void fsaveBIN(const char* name);
	void floadBIN(const char* name);
	void fsaveTXT(const char* name);
	void floadTXT(const char* name);
};