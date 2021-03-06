#include "image.h"

Image::Image(char* name) {
	this->name = name;
};

Image::Image(PIXELDATA** pixels, const char* name, int height, int width) {
	this->pixels = pixels;
	this->name = name;
	this->setHeader(height, width);
}

void Image::setHeader(int depth, int width) {
	memset(&this->header, 0, sizeof(BMPHEAD));
	this->header.depth = depth;
	this->header.width = width;
	this->header.id[0] = 'B';
	this->header.id[1] = 'M';

	size_t padding;
	if (3 * this->header.width % 4)
		padding = 4 - 3 * this->header.width % 4;
	else
		padding = 0;

	this->header.filesize = this->header.headersize + (this->header.width * 3 + padding) * this->header.depth;
	this->header.headersize = 54L;
	this->header.infoSize = 0x28L;
	this->header.biPlanes = 1;
	this->header.bits = 24;
	this->header.biCompression = 0L;
}

void Image::setPixels(int depth, int width) {
	this->pixels = new PIXELDATA * [depth];
	for (int i = 0; i < depth; i++)
		this->pixels[i] = new PIXELDATA[width];
}

void Image::createFile() {
	std::ofstream file;
	file.open(name, std::ios::binary);
	file.write(reinterpret_cast<char*>(&this->header), sizeof(this->header));

	char null;
	int padding;
	if (3 * this->header.width % 4)
		padding = 4 - 3 * this->header.width % 4;
	else
		padding = 0;

	for (int i = 0; i < this->header.depth; i++) {
		for (int k = 0; k < this->header.width; k++) {
			file.write(reinterpret_cast<char*>(&this->pixels[i][k].blueComponent), sizeof(pixels[i][k].blueComponent));
			file.write(reinterpret_cast<char*>(&this->pixels[i][k].greenComponent), sizeof(pixels[i][k].greenComponent));
			file.write(reinterpret_cast<char*>(&this->pixels[i][k].redComponent), sizeof(pixels[i][k]).redComponent);
		}
		file.write(&null, padding);
	}
	file.close();
}

BMPHEAD  Image::getHeader() {
	return this->header;
}
PIXELDATA** Image::getPixels() {
	return this->pixels;
}

void openImage::setHeader() {
	std::ifstream file;
	file.open(name, std::ios::binary);
	file.read(reinterpret_cast<char*>(&this->header), sizeof(this->header));
	file.close();
}

void openImage::setPixels() {
	pixels = new PIXELDATA * [header.depth];
	for (int i = 0; i < header.depth; i++) {
		pixels[i] = new PIXELDATA[header.width];
	}

	size_t padding;
	if (3 * this->header.width % 4)
		padding = 4 - 3 * this->header.width % 4;
	else
		padding = 0;

	std::ifstream file;
	file.open(name, std::ios::binary);
	file.seekg(sizeof(this->header), std::ios::beg);

	for (int i = 0; i < this->header.depth; i++) {
		for (int k = 0; k < this->header.width; k++) {
			file.read(reinterpret_cast<char*>(&this->pixels[i][k].blueComponent), sizeof(this->pixels[i][k].blueComponent));
			file.read(reinterpret_cast<char*>(&this->pixels[i][k].greenComponent), sizeof(this->pixels[i][k].greenComponent));
			file.read(reinterpret_cast<char*>(&this->pixels[i][k].redComponent), sizeof(this->pixels[i][k].redComponent));
		}
		file.seekg(padding, std::ios::cur);
	}
	file.close();
}

openImage::openImage(const char* name) {
	this->name = name;
	this->setHeader();
	this->setPixels();
}

unsigned int newImage::getRGBValue(int8_t value) {
	return (value + 256) % 256;
}

void newImage::interpolate(Image& source) {
	float xdif = ((float)(source.getHeader().width - 1) / (header.width - 1));
	float ydif = ((float)(source.getHeader().depth - 1) / (header.depth - 1));

	PIXELDATA * *temp = source.getPixels();
	PIXELDATA pixel;
	float x, y;
	int p1x, p1y, p2x, p2y;
	int inter1, inter2;
	for (int i = 0; i < header.depth; i++)
		for (int j = 0; j < header.width; j++) {


			x = j * xdif;
			y = i * ydif;


			p2x = (int)x;
			p2y = (int)y;
			p1x = (int)x + 1;
			p1y = (int)y + 1;

			float x1 = (p1x - x) / (p1x - p2x),
				x2 = (x - p2x) / (p1x - p2x),
				y1 = (p1y - y) / (p1y - p2y),
				y2 = (y - p2y) / (p1y - p2y);


			if ((int)x + 1 < source.getHeader().width)	p1x = (int)x + 1;
			else p1x = (int)x;
			if ((int)y + 1 < source.getHeader().depth)	p1y = (int)y + 1;
			else p1y = (int)y;

			inter1 = x1 * getRGBValue(temp[p2y][p2x].blueComponent) + x2 * getRGBValue(temp[p2y][p1x].blueComponent);
			inter2 = x1 * getRGBValue(temp[p1y][p2x].blueComponent) + x2 * getRGBValue(temp[p1y][p1x].blueComponent);
			pixel.blueComponent = y1 * inter1 + y2 * inter2;

			inter1 = x1 * getRGBValue(temp[p2y][p2x].redComponent) + x2 * getRGBValue(temp[p2y][p1x].redComponent);
			inter2 = x1 * getRGBValue(temp[p1y][p2x].redComponent) + x2 * getRGBValue(temp[p1y][p1x].redComponent);
			pixel.redComponent = y1 * inter1 + y2 * inter2;

			inter1 = x1 * getRGBValue(temp[p2y][p2x].greenComponent) + x2 * getRGBValue(temp[p2y][p1x].greenComponent);
			inter2 = x1 * getRGBValue(temp[p1y][p2x].greenComponent) + x2 * getRGBValue(temp[p1y][p1x].greenComponent);
			pixel.greenComponent = y1 * inter1 + y2 * inter2;

			pixels[i][j] = pixel;
		}
}

void newImage::setHeader(Image& source, double pow) {
	this->header = source.getHeader();
	this->header.width = (int)(this->header.width * pow);
	this->header.depth = (int)(this->header.depth * pow);

	size_t padding;
	if (3 * this->header.width % 4)
		padding = 4 - 3 * this->header.width % 4;
	else
		padding = 0;

	this->header.filesize = this->header.headersize + (this->header.width * 3 + padding) * this->header.depth;
}

void newImage::setPixels(Image& source) {
	PIXELDATA** temp = new PIXELDATA * [this->header.depth];
	for (int i = 0; i < this->header.depth; i++) {
		temp[i] = new PIXELDATA[this->header.width];
	}
	pixels = temp;
	interpolate(source);
}

newImage::newImage(const char* name, Image& source, double pow) {
	this->name = name;
	this->setHeader(source, pow);
	this->setPixels(source);
}

Image::~Image() {
	for (int i = 0; i < this->header.depth; i++)
		delete[] pixels[i];
	delete pixels;
}