#ifndef	_BLASTER_LIT_HEADER
#define	_BLASTER_LIT_HEADER

//preprocessor macro to interchange between export and import
#ifdef MAKE_DLL
#define EXPORT _declspec(dllexport)
#else
#define	EXPORT _declspec(dllimport)
#endif

//includes
#include "Pixel.h"



namespace BF {
	namespace Lit {
		//This header contains the class which is exported and contains all the main apis to interact with the Lit api.
		
		//ImageTypes supported currently
		typedef enum _ImageType {
			Unknown = 0,
			BITMAP = 1,
			NUM_OF_TYPES
		}ImageType;


		



		//struct for an Instance of an image
		typedef struct _ImageInstance{
			int instanceId;				//id of this instance
			char* fileName;				//full file name of the file loaded
			ImageType imageType;		//the type of the image loaded
			void* fileData;				//file buffer
			Pixel* pixels;				//Pixel pointer to store the pixels of the image, gets created when called from a constructor

			//constructors

			/*
			* This constructor helps in getting an ImageInstance create by scratch.
			* Params :
			*	fileName - the name of the image file
			*	instanceId - the instance Id you want to set for this Instance, by default it is 0
			*	imgType - the type of the image, by default it is set to BITMAP
			*	widthInPixels - the width of the pixel array to be created, by default set to 0
			*	heightInPixels - the height of the pixel array to be created, by default set to 0
			*	[NOTE *** If any one of the width and height of the pixels is passed as 0, then no pixel array will be created, you can create it later]
			*/
			_ImageInstance(char* fileName, int instanceId = 0, ImageType imgType = ImageType::BITMAP, unsigned int widthInPixels = 0, unsigned int heightInPixels = 0);
			
			_ImageInstance();
			
			~_ImageInstance();
		}ImageInstance;


		
		/*
			The Lit class contains the function list supported and the information parameters for the type of image files listed.
		*/
		class EXPORT Lit {
		private:
			ImageInstance	*images;
			
			int imageCount;


		public:

			//construtor
			Lit(); //activates the free version //for now this constructor will be used and will be full version
			Lit(char* lib_key); //activates the premium version

			//destructor
			~Lit();


			//apis ------------

			/*
			* Function to check if the premium version of the library is initiated
			*/
			bool isLibPremium();

			/*
			* Loads an image from the given file name and returns an Image Manipulation object of the respective type.
			* Params : 
			*	fileName - The full path of the image file to be loaded
			*	instanceId - a ref variable to recieve the instance Id of the loaded image
			*	errorId - recieves the error id if any error occurs
			* Returns :
			*	a ptr to an imageInstance of the loaded image file, if ok /
			*	NULL ptr, if fails
			*/
			ImageInstance* loadImageInstance(const char *fileName, int &instanceId, int &errorID);


			/*
			* Loads an image from the given file data and returns an Image Manipulation object of the respective type.
			* Params :
			*	fileName - Any fileName for referrence, by default is "img_file"
			*	fileData - the byte data of the image file to be loaded
			*	imgType - the type of the image data you are sending, by default this is set to BITMAP
			*	dataSizeInBytes - total size of the byte data
			*	instanceId - a ref variable to recieve the instance Id of the loaded image
			*	errorId - recieves the error id if any error occurs
			* Returns :
			*	a ptr to an imageInstance of the loaded image file, if ok /
			*	NULL ptr, if fails
			*/
			ImageInstance* loadImageInstance(const char* fileName, char *fileData, ImageType imgType, int dataSizeInBytes, int &instanceId, int &errorID);

		};

	}
}

#endif
