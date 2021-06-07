#include "Pixel.h"

#include "Common.h"


namespace BF {
	namespace Lit {
	
		//constructor
		Pixel::Pixel(unsigned int width, unsigned int height) :
			pixelCount(width * height),
			pixels(NULL)
		{
			//initiate the memory
			if (width && height) {
				this->width = width;
				this->height = height;
				this->pixels = (PRGBA)calloc(this->pixelCount, sizeof(RGBA));
			}
		}

		Pixel::Pixel() : 
			width(0),
			height(0),
			pixelCount(0),
			pixels(NULL)
		{
		}


		//destructor
		Pixel::~Pixel()
		{
			//de-allocate the pixels memory and other stuff if neccessary
			if (this->pixels)
				for (int i = 0; i < pixelCount; i++)
					free(&this->pixels[i]);
		}

		void Pixel::getWidthAndHeight(int& width, int& height)
		{
			width = this->width;
			height = this->height;
		}

		const PRGBA Pixel::getPixelAt(int row, int col)
		{
			if ((0 < row < height) && (0 < col < width)) return &pixels[((row * this->width) - (this->width - col)) - 1]; //position = (row x width) - (width - col) // -1 for array index
			else return 0;
		}

		const PRGBA Pixel::getPixels(int& count)
		{
			if (pixels) {
				count = pixelCount;
				return pixels;
			}
			else {
				count = 0;
				return NULL;
			}
		}

		const PRGBA Pixel::getPixelAtIndex(int index)
		{
			if (index > -1 && index < pixelCount)
				return &pixels[index];
			return NULL;
		}

		int Pixel::getTotalPixelCount()
		{
			return pixelCount;
		}

		const PRGBA Pixel::setPixelAtIndex(RGBA color, int row, int col)
		{
			if (row > height || col > width)
				return NULL;

			PRGBA pixel = getPixelAt(row, col);

			*pixel = color;

			return PRGBA();
		}

		const PRGBA Pixel::setPixelsWidthAndHeight(int width, int height)
		{
			if (width == 0) {
				width = this->width;
			}

			if (height == 0) {
				height = this->height;
			}

			if (pixelCount &&
				this->width &&
				this->height &&
				pixels
			) {
				
				//we already have an existing pixel array, reallocate that
				int temp_pixelCount = width * height;

				//create the new pixels array
				pixels = (PRGBA)realloc(pixels, temp_pixelCount * sizeof(RGBA));

				memset(pixels + pixelCount, 0, (temp_pixelCount - pixelCount) * sizeof(RGBA)); // set the newly added memory to zero

				//update the local variables
				this->width = width;
				this->height = height;
				pixelCount = temp_pixelCount;
			}
			else {
				//no previously create pixel array, so create one
				this->width = width;
				this->height = height;
				pixelCount = width * height;
				pixels = (PRGBA)calloc(pixelCount, sizeof(RGBA));
			}

			return pixels;
		}
	


	}
}