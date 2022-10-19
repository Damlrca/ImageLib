#include "ImageLib.h"

#include <gtest.h>

using namespace ImageLib;

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
			a.px(i, j) = rand() % 256;

	Image b = a;

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 40; j++)
			ASSERT_EQ(a.px(i, j), b.px(i, j));
}

TEST(test_Image, resize_test) {
	Image a(23, 48);
	a.resize(54, 72);
	EXPECT_EQ(54, a.height());
	EXPECT_EQ(72, a.width());
}

TEST(test_ImageFiles, TXT_test) {
	Image a(23, 16);
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			a.px(i, j) = rand() % 256;
	a.fsaveTXT("TXT_test.txt");
	Image b;
	b.floadTXT("TXT_test.txt");
	ASSERT_EQ(a.height(), b.height());
	ASSERT_EQ(a.width(), b.width());
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			ASSERT_EQ(a.px(i, j), b.px(i, j));
}

TEST(test_ImageFiles, BIN_test) {
	Image a(23, 16);
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			a.px(i, j) = rand() % 256;
	a.fsaveBIN("BIN_test.bin");
	Image b;
	b.floadBIN("BIN_test.bin");
	ASSERT_EQ(a.height(), b.height());
	ASSERT_EQ(a.width(), b.width());
	for (int i = 0; i < 23; i++)
		for (int j = 0; j < 16; j++)
			ASSERT_EQ(a.px(i, j), b.px(i, j));
}
