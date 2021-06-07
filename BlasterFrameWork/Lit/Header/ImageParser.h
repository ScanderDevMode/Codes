#ifndef _BLASTER_IMAGE_PARSER_FACTORY_HEADER_
#define _BLASTER_IMAGE_PARSER_FACTORY_HEADER_

#include "Lit.h"
#include "Pixel.h"


namespace BF {
	namespace Lit {
		class ImageParser {
		public:
			virtual bool checkImageTypeFromData(void* imageData, int dataSizeInBytes) = 0;
			virtual Pixel* parseImageData(void* imageData, int dataSizeInBytes, ImageInstance* imgInstance) = 0;
		};
	}
}

#endif