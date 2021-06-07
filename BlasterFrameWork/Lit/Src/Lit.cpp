#include "Lit.h"
#include "Common.h"
#include "LitErrors.h"
#include "ImageParser.h"
#include "BitmapParser.h"


#define NULL 0


//bool indicator for premium/ not premium lib
bool premium = false;

using namespace BF::Lit;



//parser stack, containing the parsers to the ImageTypes
typedef const ImageParser* (*_getImageParserInstance) (); //the signature of the func pointer to hold the getInstance function
typedef struct Parser_Stack {
	ImageType imgType;
	_getImageParserInstance getImageParserInstance;
};

//the stack, add other 
Parser_Stack parser_Stack[] = {
	{ImageType::Unknown,	NULL},
	{ImageType::BITMAP,		getBitmapParserInstance}
};





Lit::Lit()
{
	imageCount = 0;
	images = NULL;

	premium = true; //<remove>
}

Lit::Lit(char* lib_key)
{
	imageCount = 0;
	images = NULL;

	premium = true;
}

Lit::~Lit()
{
	if (imageCount) {
		//de initialize the Image Instances memory
		for (int i = 0; i < imageCount; i++) {
			ImageInstance ins = images[i];
			free(ins.fileName);
		}

		free(images); //free the images
	}
}

bool Lit::isLibPremium()
{
	return premium;
}


//internal : uses the image file name extension(if any) to deduct the Image Type
ImageType getImageTypeByFileName(const char *fileName) {
	//check
	if (!fileName)
		return ImageType::Unknown;

	//find the extension
	int strLen = strlen(fileName);
	char* p = (char *)&fileName[strLen - 1]; //tmp ptr

	//check loop
	for (; 
		*p != '\\' &&
		*p != '/' &&
		*p != '.' &&
		strLen > 0
		;strLen--, p--
		);

	//check for invalid fileName constraints
	if (strLen == 0 ||
		*p == '\\' ||
		*p == '/')
		return ImageType::Unknown;

	p++; //take the pointer back to the start of the extension

	//return the type, add the data types as you go
	if (!stricmp(p, "bmp"))
		return ImageType::BITMAP;
	else
		return ImageType::Unknown;
}





//internal function to get the Parser related to the image type
const ImageParser* getImageParserOfType(ImageType imgType) {
	return parser_Stack[imgType].getImageParserInstance();
}




//internal function for loading up the image data into the arrays
//tries to use the supplied Image Type for parsing the data, if fails
//it then tries with all the other available types, if it fails with all the other types also, give up
bool parseImage(char *fileData, int dataSizeInBytes, ImageType imgType, ImageInstance *imgInstance){
	
	if (!fileData || dataSizeInBytes < 2 || !imgInstance)
		return NULL;

	//get the image parser of the specified type
	ImageParser* parser = (ImageParser*)getImageParserOfType(imgType); //can be replaced with refferences

	//verify the image type
	if (!parser->checkImageTypeFromData(fileData, dataSizeInBytes)) {
		//the specified type is incorrect, try to find the correct type of the image

		imgType = ImageType::Unknown;

		//start the search from index 1, as 0 is for UNKNOWN types
		for (int i = 1; i < ImageType::NUM_OF_TYPES; i++) {
			if ((ImageType)i == imgType)
				continue;
			parser = (ImageParser*)getImageParserOfType((ImageType)i);

			if (parser->checkImageTypeFromData(fileData, dataSizeInBytes)) {
				imgType = (ImageType)i;
				break;
			}
		}

		if (imgType == ImageType::Unknown) {
			//image type is not supported
			return false;
		}
	}
	
	//parse the image
	if (parser->parseImageData(fileData, dataSizeInBytes, imgInstance))
		return true;

	return false;
}




ImageInstance* Lit::loadImageInstance(const char *fileName = "imageFile", char* fileData, ImageType imgType, int dataSizeInBytes, int& instanceId, int& errorID) {
	if (!fileData || !dataSizeInBytes) {
		errorID = LIT_ERRORS::INVALID_ARGUMENT;
		return nullptr;
	}

	//create a new ImageInstance
	ImageInstance* imgInstance = new ImageInstance((char *)fileName, instanceId, imgType);
	if (!imgInstance) {
		errorID = LIT_ERRORS::NO_MEMORY;
		return nullptr;
	}


	//try to parse the img in the specified type
	if (!parseImage(fileData, dataSizeInBytes, imgType, imgInstance)) {
		//parsing failed, free and return
		errorID = LIT_ERRORS::TYPE_UNKNOWN;
		delete(imgInstance);
		return NULL;
	}
	
	return imgInstance;
}


ImageInstance* Lit::loadImageInstance(const char* fileName, int& instanceId, int &errorID)
{
	FILE* fp = NULL; //file pointer
	errorID = 0;

	RUN_ON_WIN
		//windows stuff goes here
		if (!PathFileExistsA(fileName)) {
			errorID = LIT_ERRORS::INVALID_ARGUMENT;
			return nullptr;
		}
	RUN_ON_END

	//open up the file
	fopen_s(&fp, fileName, "r + b");
	if (!fp) {
		errorID = LIT_ERRORS::NO_MEMORY;
		return nullptr;
	}

	//seek the file size
	long dataSizeInBytes = fseek(fp, 0, SEEK_END);

	//create the buffer
	char *fileData = (char *)calloc(dataSizeInBytes + 1, 1); //file data buffer

	//rewind the file
	rewind(fp);

	//read the file data
	int ret = fread(fileData, 1, dataSizeInBytes, fp);
	fclose(fp); //close the file
	if (!ret) { //check the data read
		errorID = LIT_ERRORS::UNKNOWN_ERROR;
		free(fileData);
		return nullptr;
	}

	ImageType imgType = getImageTypeByFileName(fileName);

	//call the load Instance function with file data mode
	ImageInstance *ins =  loadImageInstance(fileName, fileData, imgType, dataSizeInBytes, instanceId, errorID);
	
	//free the file data
	free(fileData);

	return ins;
}

BF::Lit::_ImageInstance::_ImageInstance(char* fileName, int instanceId = 0, ImageType imgType = ImageType::BITMAP, unsigned int widthInPixels, unsigned int heightInPixels) :
	instanceId(instanceId),
	imageType(imgType)
{
	fileName = _strdup(fileName);

	fileData = nullptr;

	if (widthInPixels && heightInPixels)
		pixels = new Pixel(widthInPixels, heightInPixels);
}



BF::Lit::_ImageInstance::_ImageInstance()
{
	instanceId = 0;
	fileName = nullptr;
	imageType = ImageType::Unknown;
	fileData = nullptr;
}

BF::Lit::_ImageInstance::~_ImageInstance()
{
	//free all the reserved memory
	if (fileName)
		free(fileName);
	if (fileData)
		free(fileData);
	if (pixels)
		delete(pixels);
}
