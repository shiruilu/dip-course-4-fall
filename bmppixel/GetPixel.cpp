#include <stdio.h>
#include <assert.h>
#include <file.h>
#include "GetPixel.h"

using namespace std;

BITMAPFILEHEADER m_BitmapFileHeader;
BITMAPINFOHEADER * m_pBitmapInfoheader;
RGBQUARD * m_pRgbQuard;
BYTE * m_pData;
BYTE * pDib;

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
  if (size != BitmapFileHeader.bfSize) {
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

bool GetPixel(char *pBuf, int x, int y, int rgb[3])
{
  assert(pBuf);
  return true;
}
