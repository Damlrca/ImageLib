#include "Image.h"
#include "ImagePlus.h"

#include <gtest.h>

TEST(test_Image, size_test) {
	Image temp(3, 21);
	EXPECT_EQ(3, temp.height());
	EXPECT_EQ(21, temp.width());
}

TEST(test_Image, size_test_2) {
	Image temp(14, 0);
	EXPECT_EQ(14, temp.height());
	EXPECT_EQ(0, temp.width());
}

TEST(test_Image, copy_constructor_test) {
	Image a(20, 40);
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 40; j++)
			a.pixel(i, j) = rand() % 256;

	Image b = a;

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 40; j++)
			ASSERT_EQ(a.pixel(i, j), b.pixel(i, j));
}

TEST(test_Image, upscale_test) {
	Image a(21, 43);
	for (int i = 0; i < 21; i++)
		for (int j = 0; j < 43; j++)
			a.pixel(i, j) = rand() % 256;

	Image b = a;
	b.upscale();

	EXPECT_EQ(b.pixel(5, 7), ((a.pixel(2, 3) + a.pixel(2, 4)) / 2 + (a.pixel(3, 3) + a.pixel(3, 4)) / 2) / 2);
}

TEST(test_Image, resize_test) {
	Image a(23, 48);
	a.resize(54, 72);
	EXPECT_EQ(54, a.height());
	EXPECT_EQ(72, a.width());
}

TEST(test_ImagePlus, TXT_test) {
	ImagePlus a(23, 16);
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			a.pixel(i, j) = rand() % 256;
	a.fsaveTXT("TXT_test.txt");
	ImagePlus b;
	b.floadTXT("TXT_test.txt");
	ASSERT_EQ(a.height(), b.height());
	ASSERT_EQ(a.width(), b.width());
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			ASSERT_EQ(a.pixel(i, j), b.pixel(i, j));
}

TEST(test_ImagePlus, BIN_test) {
	ImagePlus a(23, 16);
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			a.pixel(i, j) = rand() % 256;
	a.fsaveBIN("BIN_test.bin");
	ImagePlus b;
	b.floadBIN("BIN_test.bin");
	ASSERT_EQ(a.height(), b.height());
	ASSERT_EQ(a.width(), b.width());
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			ASSERT_EQ(a.pixel(i, j), b.pixel(i, j));
}