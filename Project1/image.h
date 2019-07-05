#pragma once
#pragma pack(2)

#define _CRT_SECURE_NO_WARNINGS

#include <stdint.h>
#include <iostream>
#include <fstream>

typedef struct BMPHEAD {
	int8_t id[2];
	int32_t filesize;
	int16_t reserved[2];
	int32_t headersize;
	int32_t infoSize;
	int32_t width;
	int32_t depth;
	int16_t biPlanes;
	int16_t bits;
	int32_t biCompression;
	int32_t biSizeImage;
	int32_t biXPelsPerMeter;
	int32_t biYPelsPerMeter;
	int32_t biClrUsed;
	int32_t biClrImportant;
	BMPHEAD() {
		id[0] = 'B';
		id[1] = 'M';
	};
} BMPHEAD;

typedef struct PIXELDATA {
	int8_t redComponent;
	int8_t greenComponent;
	int8_t blueComponent;
} PIXELDATA;

class Image {
protected:
	PIXELDATA** pixels;
	BMPHEAD header;

	virtual void setHeader(int depth, int width);
	virtual void setPixels(int depth, int width);
public:
	const char* name;

	Image() {}
	Image(char* name);
	Image(PIXELDATA** pixels, const char* name, int height, int width);

	void createFile();
	BMPHEAD getHeader();
	PIXELDATA** getPixels();

	~Image();

};


class openImage : public Image {
private:
	void setHeader();
	void setPixels();
public:
	openImage(const char* name);
};

class newImage : public Image {
private:
	unsigned int getRGBValue(int8_t value);
	void interpolate(Image& source);
	void setHeader(Image& source, double pow);
	void setPixels(Image& source);
public:
	newImage(const char* name, Image& source, double pow);
};