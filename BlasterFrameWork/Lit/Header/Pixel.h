#ifndef _BLASTER_LIT_PIXEL_HEADER
#define _BLASTER_LIT_PIXEL_HEADER



namespace BF {
	namespace Lit {
		//this header describes the pixel strcuture and pixel apis
		//Is used to represent colors globaly through out the Library.
		//Universally in and out
	
		//represents a 32 bit rgba structure to contain the colors of a pixel,
		//this structure can also be used for the other bit types
		typedef struct _RGBA {
			char R;
			char G;
			char B;
			char A;
		}RGBA, *PRGBA;



		//Pixel class contains the pixel data and some apis to manipulate the pixel
		class Pixel {
		private :
			PRGBA		pixels;		//pixel array
			int			width;			//image width or pixel coloumns
			int			height;			//image height or pixel rows
			int			pixelCount;		//the total count of pixels in the pixels array

		public:
			//constructor
			Pixel(int width, int height);

			//destructor
			~Pixel();


			//API ---------------
			
			/*
			* This function is used to get the width and the height of the pixels
			* Params :
			*	width - reference to an int variable to recieve the width
			*	height - reference to an int variable to recieve the height
			*/
			void getWidthAndHeight(int &width, int &height);


			/*
			* This function is used to get a pixel at a specific postion
			* Params :
			*	row - the pixel's position in height.
			*	col - the pixel's position in  width.
			*/
			PRGBA getPixelAt(int row, int col);


			/*
			* This function is used to get the pixel array.
			* Params :
			*	count - refernece to an int variable to recieve the total pixel count in array.
			*/
			PRGBA getPixel(int &count);


			/*
			* Function to retrieve the total count of the pixel array.
			* Returns :
			*	returns the total count of the pixel array.
			*/
			int getTotalPixelCount();
		};
	}
}

#endif