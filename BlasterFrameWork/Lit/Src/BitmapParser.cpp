#include "BitmapParser.h"


using namespace BF::Lit;



//BMP specific constants
#define BMP_TYPE_CODE 0x4D42



bool BitmapParser::checkImageTypeFromData(void* imageData, int dataSizeInBytes)
{
	//check the first two bytes of the data
	if (dataSizeInBytes < sizeof(BitmapHeader))
		return false;

	if (*((short*)imageData) == BMP_TYPE_CODE)
		return true;

	return false;
}

Pixel* BF::Lit::BitmapParser::parseImageData(void* imageData, int dataSizeInBytes, ImageInstance* imgInstance)
{

	return nullptr;
}

const ImageParser* BF::Lit::getBitmapParserInstance()
{
	const BitmapParser parser;
	return &parser;
}


