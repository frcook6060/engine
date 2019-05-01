#pragma once


/*
struct ImageData
{
	FIBITMAP* bitmap;
	void* pixels;
	uint32_t width;
	uint32_t height;
	uint32_t rowPitch;

};


void img_init(std::string path, ImageData* data);

void img_release(ImageData* data)
*/

class Image
{
private:
	FIBITMAP* bitmap;
	void* pixels;
	uint32_t width;
	uint32_t height;
	uint32_t rowPitch;
public:

	void init(std::string path);
	void release();

	FIBITMAP* getBitmap();
	void* getPixels();
	uint32_t getWidth();
	uint32_t getHeight();
	uint32_t getRowPitch();

};