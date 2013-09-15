#ifndef _BITMAP_H_
#define _BITMAP_H_

#include "common.h"

class BitMap
{
private:
	/* variables */
	BITMAPFILEHEADER m_BitmapFileHeader;
	BITMAPINFOHEADER * m_pBitmapInfoHeader;
	RGBQUAD * m_pRgbQuad;
	BYTE * m_pData;
	//BYTE * pDib;
	/* functions */
	unsigned int GetNumberOfColors();
public:
	BitMap();
	~BitMap();
	bool LoadBmpFile(const char *filename);
	bool GetPixel(int x, int y, unsigned short rgb[3]);
	bool WriteBmpFile(const char *filename);
	bool SubSample();
};

#endif
