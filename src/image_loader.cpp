#include "sys.h"

#include "sys.h"


void Image::init(std::string path)
{
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path.c_str());

	if (format == -1)
	{
		throw std::runtime_error("Couldn't load image file");
	}

	if (format == FIF_UNKNOWN)
	{
		format = FreeImage_GetFIFFromFilename(path.c_str());
		if (!FreeImage_FIFSupportsReading(format))
		{
			throw std::runtime_error("Can't read image file due to coruption.");
		}
	}

	FIBITMAP* temp = FreeImage_Load(format, path.c_str());


}

void Image::release()
{

}

FIBITMAP* Image::getBitmap()
{
	return this->bitmap;
}

void* Image::getPixels()
{
	return this->pixels;
}

uint32_t Image::getWidth()
{
	return this->width;
}

uint32_t Image::getHeight()
{
	return this->height;
}

uint32_t Image::getRowPitch()
{
	return this->rowPitch;
}

