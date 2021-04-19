#ifndef	_BLASTER_LIT_HEADER
#define	_BLASTER_LIT_HEADER

//preprocessor macro to interchange between export and import
#ifdef MAKE_DLL
#define EXPORT _declspec(dllexport)
#else
#define	EXPORT _declspec(dllimport)
#endif

#include 



namespace BF {
	namespace Lit {
		//This header contains the class which is exported and contains all the main apis to interact with the Lit api.
		

		//ImageTypes supported currently
		typedef enum _ImageType {
			BITMAP = 0
		}ImageType;



		//struct for an Instance of an image
		typedef struct _ImageInstance{
			int instanceId;				//id of this instance
			char* fileName;				//full file name of the file loaded
			ImageType imageType;		//the type of the image loaded

			
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
			* Returns :
			*	a ptr to an imageInstance of the loaded image file, if ok /
			*	NULL ptr, if fails
			*/
			ImageInstance* loadImageInstance(char *fileName, int &instanceId);


			/*
			* Loads an image from the given file data and returns an Image Manipulation object of the respective type.
			* Params :
			*	fileName - The full path of the image file to be loaded
			* Returns :
			*	a ptr to an imageInstance of the loaded image file, if ok /
			*	NULL ptr, if fails
			*/
			ImageInstance* loadImageInstance(char *fileData, int &instanceId);

		};

	}
}

#endif
