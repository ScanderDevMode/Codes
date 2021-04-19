#include <stdio.h>
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define BITMAP_TYPE 0x4D42 //the bf type should be matching to this, if what we are loading is a bmp type image



typedef struct _BITMAP_HEADER {
	WORD	BF_Type; //should be matching with BITMAP_TYPE which verifies its a bitmap image.
	DWORD	BF_Size; //the size of the *.bmp file in bytes
	WORD	BF_Reserved1; //reserved for the pic, must be 0
	WORD	BF_Reserved2; //reserved for the pic, must be 0
	WORD	BF_OffBits; //specifies the offset in bytes, the distance between Bitmap header to bitmap bits
}BITMAP_HEADER, *PBITMAP_HEADER;



typedef struct _BITMAP_INFO_HEADER {

    DWORD biSize;  //specifies the number of bytes required by the struct
    LONG biWidth;  //specifies width in pixels
    LONG biHeight;  //species height in pixels
    WORD biPlanes; //specifies the number of color planes, must be 1
    WORD biBitCount; //specifies the number of bit per pixel
    DWORD biCompression;//spcifies the type of compression
    DWORD biSizeImage;  //size of image in bytes
    LONG biXPelsPerMeter;  //number of pixels per meter in x axis
    LONG biYPelsPerMeter;  //number of pixels per meter in y axis
    DWORD biClrUsed;  //number of colors used by th ebitmap
    DWORD biClrImportant;  //number of colors that are important

}BITMAP_INFO_HEADER, *PBITMAP_INFO_HEADER;



FILE* openFile(char *fileName, int *errorNumber) {
    
    if (!PathFileExistsA(fileName)) {
        *errorNumber = 1;
        return NULL;
    }

    FILE* file;
    errno_t e = fopen_s(&file, fileName, "a+b");

    if (e) {
        *errorNumber = e;
        return NULL;
    }
    
    //go to the start of the file
    fseek(file, 0, SEEK_SET);

    return file;
}


unsigned char* LoadBitmapFile(char *fileName, PBITMAPINFOHEADER bitmapInfoHeader, int *errorNo) {
    int ret = 0;
    *bitmapInfoHeader = { 0 };
    unsigned char* bitmapImage = NULL;

    //try to open the file
    FILE* fp = openFile(fileName, &ret);
    if (ret) {
        return NULL;
    }

    BITMAPFILEHEADER bitmapFileHeader = {0};

    //read the bitmap header
    ret = fread_s(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), sizeof(BITMAPFILEHEADER), 1, fp);
    if (!ret) {
        ret = -1;
        goto END;
    }


    //check if the file is a bitmap file
    if (bitmapFileHeader.bfType != BITMAP_TYPE) {
        ret = -1;
        goto END;
    }


    //read the bitmap info header
    fread_s(bitmapInfoHeader, sizeof(BITMAP_INFO_HEADER), sizeof(BITMAP_INFO_HEADER), 1, fp);

    
    //use the offset and move to the location of pixel data
    fseek(fp, bitmapFileHeader.bfOffBits, SEEK_SET);

    //allocate enough memory for the bitmap image data
    bitmapImage = (unsigned char*)calloc(1, bitmapInfoHeader->biSizeImage);

    //verify memory allocation
    if (!bitmapImage)
    {
        ret = -1;
        return NULL;
    }


    //read the pixel data
    ret = fread_s(bitmapImage, bitmapInfoHeader->biSizeImage,
        1, bitmapInfoHeader->biSizeImage, fp);

    if (!ret) {
        ret = -1;
        return NULL;
    }
    
    ret = 0;


    //swap the r and b values to get RGB (bitmap is BGR)
    for ( int imageIdx = 0; imageIdx < bitmapInfoHeader->biSizeImage; imageIdx += 3)
    {
        /*char tempRGB = bitmapImage[imageIdx];
        bitmapImage[imageIdx] = bitmapImage[imageIdx + 2];
        bitmapImage[imageIdx + 2] = tempRGB;*/

        bitmapImage[imageIdx] = 0;
    }



    //change the first color
 /*   bitmapImage[0] = (char)24;
    bitmapImage[1] = (char)24;
    bitmapImage[2] = (char)24;*/


    //write to the file after making the changes
    fseek(fp, bitmapFileHeader.bfOffBits, SEEK_SET);
    fwrite(bitmapImage, 1, bitmapInfoHeader->biSizeImage, fp);


END:
    if (fp)
        fclose(fp);

    if (ret) {
        if (errorNo)
            *errorNo = ret;
        
        if(bitmapImage)
            free(bitmapImage);

        return NULL;
    }

    return bitmapImage;
}





int main(int argc, char * argv[]) {
    int errorNo;
    BITMAPINFOHEADER infoHeader;

    char* fileName = (char *)"C:\\tempDirectory\\WorkingDirectory\\BlasterFrameWork\\Extra\\testScreen.bmp";
    

    unsigned char *bitmapData = LoadBitmapFile(fileName, &infoHeader, &errorNo);


    int r = (int)bitmapData[0];
    int g = (int)bitmapData[1];
    int b = (int)bitmapData[2];





	return 0;
}