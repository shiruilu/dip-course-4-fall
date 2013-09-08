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
/*
bool LoadBmp(const char * filename)
{
  ifstream ifs(filename, ios::binary);
  ifs.seekg(0, ios::end);
  int size = ifs.tellg();
  ifs.seekg(0, ios::beg);
  ifs.read( (char *)&m_BitmapFileHeader, sizeof(BITMAPFILEHEADER) );

  if (m_BitmapFileHeader.bfType != 0x4d42) {
    throw "文件类型不正确！";
    return false;
  }
  if (size != m_BitmapFileHeader.bfSize) {
    throw "文件大小描述不正确！";
    return false;
  }

  pDib = new BYTE[size - sizeof(BITMAPFILEHEADER)];

  if( !pDib) {
    throw "out of memory!";
    return false;
  }
  ifs.read( (char *)pDib.size - sizeof(BITMAPFILEHEADER) );

  m_pBitmapInfoHeader = (BITMAPINFOHEADER *)pDib;
  m_pRgbQuard = (RGBQUARD *)(pDib + sizeof(BITMAPINFOHEADER));
  int colorTableSize = m_BitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER) - m_pBitmapInfoHeader->biSize;
  int numberOfColors = GetNumberOfColors();

  if (numberOfColors * sizeof(RGBQUARD) != colorTableSize) {
    delete[] pDib;
    pDib = NULL;
    throw "颜色表大小计算错误！";
    return false;
  }
  m_pData = pDib + sizeof(BITMAPINFOHEADER) + colorTableSize;
  return true;
}
*/
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

  RGBQUAD * pRgbQuad = (RGBQUAD *)(pBuf + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER));
  BYTE * pData = (BYTE *)(pBuf + pBiFileHeader->bfOffBits);

  int rwidth = ((pBiInfoHeader->biWidth + 3) >> 2) <<2;
  int ry = pBiInfoHeader->biHeight -1 -y;
  if ( pBiInfoHeader->biBitCount == 8 ) {

	rgb[0] = pRgbQuad[pData[ry*rwidth+x]].rgbBlue;
	return true;
  }
  else if ( pBiInfoHeader->biBitCount == 24 ) {
	  rgb[0] = pData[(ry*rwidth+x)*3];
	  rgb[1] = pData[(ry*rwidth+x)*3 + 1];
	  rgb[2] = pData[(ry*rwidth+x)*3 + 2];
	  return true;
  }
}
