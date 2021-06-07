#ifndef _BF_LIT_BITMAP_PARSER_HEADER_
#define _BF_LIT_BITMAP_PARSER_HEADER_

#include "Common.h"
#include "BitmapContainers.h"
#include "ImageParser.h"



namespace BF {
	namespace Lit {

		class BitmapParser : public ImageParser{
		public:
			bool checkImageTypeFromData(void* imageData, int dataSizeInBytes);
			Pixel* parseImageData(void* imageData, int dataSizeInBytes, ImageInstance* imgInstance);
		};

		const ImageParser* getBitmapParserInstance();
	}
}


#endif
