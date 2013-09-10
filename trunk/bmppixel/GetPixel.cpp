#include <iostream>
#include <fstream>
#include <stdio.h>
#include <assert.h>
#include "GetPixel.h"

using namespace std;

BITMAPFILEHEADER m_BitmapFileHeader;
BITMAPINFOHEADER * m_pBitmapInfoheader;
RGBQUAD * m_pRgbQuard;
BYTE * m_pData;
BYTE * pDib;

bool GetPixel(char *pBuf, int x, int y, unsigned short rgb[3])
{
  assert(pBuf);
  BITMAPFILEHEADER* pBiFileHeader = (BITMAPFILEHEADER *)pBuf;
  assert(pBiFileHeader->bfType == 0x4d42);
  //assert(sizeof(pBuf)/sizeof(BYTE) == pBiFileHeader->bfSize);

  BITMAPINFOHEADER* pBiInfoHeader = (BITMAPINFOHEADER *)(pBuf + sizeof(BITMAPFILEHEADER));
  if ( x>=pBiInfoHeader->biWidth || y>=pBiInfoHeader->biHeight )
  {
	  //assert(0);
	  return false;
  }

  BYTE * pData = (BYTE *)(pBuf + pBiFileHeader->bfOffBits);

  int rwidth = ((pBiInfoHeader->biWidth + 3) >> 2) <<2;
  int ry = pBiInfoHeader->biHeight -1 -y;
  if ( pBiInfoHeader->biBitCount == 8 ) {
	RGBQUAD * pRgbQuad = (RGBQUAD *)(pBuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
	rgb[0] = pRgbQuad[pData[ry*rwidth+x]].rgbBlue;
	return true;
  }
  else if ( pBiInfoHeader->biBitCount == 24 ) {
	  rgb[0] = pData[(ry*rwidth+x)*3];
	  rgb[1] = pData[(ry*rwidth+x)*3 + 1];
	  rgb[2] = pData[(ry*rwidth+x)*3 + 2];
	  return true;
  }
  return false;
}
