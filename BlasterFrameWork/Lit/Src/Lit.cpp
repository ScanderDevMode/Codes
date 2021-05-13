#include "Lit.h"
#include "Common.h"

#define NULL 0


//bool indicator for premium/ not premium lib
bool premium = false;



BF::Lit::Lit::Lit()
{
	imageCount = 0;
	images = NULL;

	premium = true;
}

BF::Lit::Lit::Lit(char* lib_key)
{
	imageCount = 0;
	images = NULL;

	premium = true;
}

BF::Lit::Lit::~Lit()
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

bool BF::Lit::Lit::isLibPremium()
{
	return isLibPremium;
}

BF::Lit::ImageInstance* BF::Lit::Lit::loadImageInstance(char* fileName, int& instanceId)
{
	

	return nullptr;
}
