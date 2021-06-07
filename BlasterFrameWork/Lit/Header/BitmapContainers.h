#ifndef _BF_LIT_BITMAP_CONTAINER_HEADER_
#define _BF_LIT_BITMAP_CONTAINER_HEADER_

namespace BF {

	namespace Lit {

		//some microsoft defined types, better redability
		typedef unsigned int DWORD; //4 bytes
		typedef unsigned short WORD; //2 bytes
		typedef signed long LONG; //4 bytes
		typedef unsigned char BYTE; //1 byte



		//Structrue for Bitmap file header
		typedef struct _BitmapFileHeader {
			WORD bFileType; //the file type, should be 
			DWORD bFileSize;
			WORD bReserved1;
			WORD bReserved2;
			DWORD bPixelDataOffset;
		}BitmapFileHeader, * PBitmapFileHeader; //14 Bytes



		//Structure for the Bitmap Info Header
		typedef struct _BitmapInfoHeader {
			DWORD bHeaderSize; //total size of the image information header (40 bytes)
			LONG bImageWidth; //Image Width (Pixels)
			LONG bImageHeight; //Image Height (Pixels)
			WORD bPlanes; //always should be 0
			WORD bBitsPerPixel; //Number of bits used per pixel
			DWORD bCompression; //Image Compression Method
			DWORD bImageSize; //The size of the total image file (bytes)
			LONG bXPixelsPerMeter; //Horizontal Pixels Per Meter
			LONG bYPixelsPerMeter; //Vertical Pixels Per Meter
			DWORD bTotalColors; //The total number of colors used, if the number of pixels is greater than 8, this field is meaningless
			DWORD bImportantColors; //Important color numbers, generally useless
		}BitmapInfoHeader, * PBitmapInfoHeader; //40 bytes


		//structur for the bitmap headers
		typedef struct _BitmapHeader {
			PBitmapFileHeader bitmapFileHeader;
			PBitmapInfoHeader bitmapInfoHeader;
		}BitmapHeader, * PBitmapHeader; //54 bytes

	}

}

#endif