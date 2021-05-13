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


			//overloaded operators

			//overloaded = operator
			//&
			_RGBA& operator= (const _RGBA& obj) {
				this->A = obj.A;
				this->R = obj.R;
				this->G = obj.G;
				this->B = obj.B;

				return *this;
			}
			
			//overloaded = operator
			//*
			PRGBA operator= (const PRGBA obj) {
				this->A = obj->A;
				this->R = obj->R;
				this->G = obj->G;
				this->B = obj->B;
			}
		}RGBA, *PRGBA;



		//Pixel class contains the pixel data and some apis to manipulate the pixel
		class Pixel {
		private :
			PRGBA		pixels;			//2d pixel array
			int			width;			//image width or pixel coloumns
			int			height;			//image height or pixel rows
			int			pixelCount;		//the total count of pixels in the pixels array

		public:
			//constructor
			Pixel(int width, int height);
			Pixel();

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
			*	row - the pixel's position in height. starts with 1 and ends on height
			*	col - the pixel's position in  width. starts with 1 and ends on width
			* Returns :
			*	returns the RGBA Pixel at the enquired position if ok,
			*	returns NULL if fails
			*/
			const PRGBA getPixelAt(int row, int col);


			/*
			* This function is used to get the pixel array.
			* Params :
			*	count - refernece to an int variable to recieve the total pixel count in array.
			* Returns :
			*	returns the RGBA pixels array if ok,
			*	returns NULL if fails
			*/
			const PRGBA getPixels(int &count);


			/*
			* This function is used to get a pixel at a specific index of the array.
			* Params :
			*	index - the index of the element in the array to be retrieved. between 0 to pixelCount - 1
			* Returns :
			*	returns the RGBA Pixel at the enquired position if ok,
			*	returns NULL if fails
			*/
			const PRGBA getPixelAtIndex(int index);


			/*
			* Function to retrieve the total count of the pixel array.
			* Returns :
			*	returns the total count of the pixel array.
			*/
			int getTotalPixelCount();


			/*
			* Function to set a pixel at the position of row and col with the color 'color'
			* Params :
			*	color - the color to set at the pixel
			*	row - the row at which the pixel resides, starts with 1 and ends on height
			*	col - the col at which the pixel resides, starts with 1 and ends on width
			* returns :
			*	returns the pointer to the pixel, if ok.
			*	returns NULL if fails.
			*/
			const PRGBA setPixelAtIndex(RGBA color, int row, int col);

		};
	}
}

#endif