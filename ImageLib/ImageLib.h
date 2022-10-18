#ifndef __IMAGE_LIB
#define __IMAGE_LIB

#include <iostream>

namespace ImageLib {

	class Image {
	public:
		class image_err {};
		class size_err : public image_err {};
		class index_err : public image_err {};
	protected:
		size_t h;
		size_t w;
		unsigned char** arr;
	private:
		unsigned char** img_alloc(size_t h, size_t w);
		void img_delete(unsigned char** arr);
	public:
		explicit Image();
		explicit Image(size_t _h, size_t _w);

		Image(const Image& img);
		Image& operator=(const Image& img);

		Image(Image&& img) noexcept;
		Image& operator=(Image&& img) noexcept;

		size_t height() const { return h; };

		size_t width() const { return w; };

		unsigned char& px(int _h, int _w) { return arr[_h][_w]; }

		const unsigned char& px(int _h, int _w) const { return arr[_h][_w]; }

		unsigned char& at(int _h, int _w) {
			if (_h < 0 || _h >= h || _w < 0 || _w >= w)
				throw index_err{};
			return arr[_h][_w];
		}

		const unsigned char& at(int _h, int _w) const {
			if (_h < 0 || _h >= h || _w < 0 || _w >= w)
				throw index_err{};
			return arr[_h][_w];
		}

		void resize(size_t _h, size_t _w);

		~Image();

		friend std::ostream& operator<<(std::ostream& out, const Image& img);
		friend std::istream& operator>>(std::istream& in, Image& img);

		void fsaveBIN(const char* name) const;
		void floadBIN(const char* name);
		void fsaveTXT(const char* name) const;
		void floadTXT(const char* name);
	};

	std::ostream& operator<<(std::ostream& out, const Image& img);
	std::istream& operator>>(std::istream& in, Image& img);

}

#endif // !__IMAGE_LIB