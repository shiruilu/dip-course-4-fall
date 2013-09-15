#include "BitMap.h"
#include <memory.h>
#include <fstream>
#include <assert.h>

using namespace std;

BitMap::BitMap()
{
	m_pBitmapInfoHeader = NULL;
	m_pRgbQuad = NULL;
	m_pData = NULL;
}

BitMap::~BitMap()
{
	if(m_pBitmapInfoHeader) {
		delete m_pBitmapInfoHeader;
		m_pBitmapInfoHeader = NULL;
	}
	if(m_pRgbQuad) {
		delete m_pRgbQuad;
		m_pRgbQuad = NULL;
	}
	if(m_pData) {
		delete m_pData;
		m_pData = NULL;
	}
}

unsigned int BitMap::GetNumberOfColors()
{
    int numberOfColors;
    if ((m_pBitmapInfoHeader->biClrUsed == 0) &&
                     (m_pBitmapInfoHeader->biBitCount < 9))
       //biClrUsed表示实际用到的颜色数，若0为2的biBitCount次中颜色
       //biBitCount为用到的颜色的位数，小于9则表示最大为8位，那么之多为256色
       {
              switch (m_pBitmapInfoHeader->biBitCount)
              {
                     case 1: numberOfColors = 2; break;
                     case 4: numberOfColors = 16; break;
                     case 8: numberOfColors = 256;
              }
       }
    else
       numberOfColors = (int) m_pBitmapInfoHeader->biClrUsed;
    return numberOfColors;
}

bool BitMap::LoadBmpFile(const char *filename)
{
  ifstream ifs(filename, ios::in | ios::binary);
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
/*
  char *pDib = new BYTE[size - sizeof(BITMAPFILEHEADER)];

  if( !pDib) {
    throw "out of memory!";
    return false;
  }
  ifs.read( (char *)pDib, size - sizeof(BITMAPFILEHEADER) );
*/
  m_pBitmapInfoHeader = (BITMAPINFOHEADER *)new BYTE[sizeof(BITMAPINFOHEADER)];
  ifs.read( (char *)m_pBitmapInfoHeader, sizeof(BITMAPINFOHEADER) );

  unsigned int colorTableSize = m_BitmapFileHeader.bfOffBits - sizeof(BITMAPFILEHEADER) - m_pBitmapInfoHeader->biSize;
  if (colorTableSize)
  {
	  m_pRgbQuad = (RGBQUAD *)new BYTE[colorTableSize];
	  ifs.read( (char *)m_pRgbQuad, colorTableSize );
  }

  int numberOfColors = GetNumberOfColors();

  if (numberOfColors * sizeof(RGBQUAD) != colorTableSize) {
    delete[] m_pBitmapInfoHeader;
    m_pBitmapInfoHeader = NULL;
	if (m_pRgbQuad)
	{
		delete[] m_pRgbQuad;
		m_pRgbQuad = NULL;
	}
    throw "颜色表大小计算错误！";
    return false;
  }
  /* 不能用这种方法如果位图的biCommpresion是BI_RGB，那么biSizeImage就是0.
  m_pData = new BYTE[m_pBitmapInfoHeader->biSizeImage];
  ifs.read( (char *)m_pData, m_pBitmapInfoHeader->biSizeImage );
  */
  m_pData = new BYTE[size - m_BitmapFileHeader.bfOffBits];
  ifs.read( (char *)m_pData, size - m_BitmapFileHeader.bfOffBits );
  return true;
}

bool BitMap::GetPixel(int x, int y, unsigned short rgb[3])
{
  if (!m_pData || 0x4d42!=m_BitmapFileHeader.bfType)
  {
	  return false;
  }

  assert(m_pData);
  assert(m_BitmapFileHeader.bfType == 0x4d42);

  if ( x>=m_pBitmapInfoHeader->biWidth || y>=m_pBitmapInfoHeader->biHeight )
  {
	  return false;
  }

  int rwidth = ((m_pBitmapInfoHeader->biWidth + 3) >> 2) <<2;
  int ry = m_pBitmapInfoHeader->biHeight -1 -y;
  if ( m_pBitmapInfoHeader->biBitCount == 8 ) {

	rgb[0] = m_pRgbQuad[m_pData[ry*rwidth+x]].rgbBlue;
	return true;
  }
  else if ( m_pBitmapInfoHeader->biBitCount == 24 ) {
	  rgb[0] = /*(unsigned short)*/(unsigned char)m_pData[(ry*rwidth+x)*3];
	  rgb[1] = (unsigned short)(unsigned char)m_pData[(ry*rwidth+x)*3 + 1];
	  rgb[2] = (unsigned short)(unsigned char)m_pData[(ry*rwidth+x)*3 + 2];
	  return true;
  }
}

bool BitMap::WriteBmpFile(const char *filename)
{
	assert(m_pData && m_pBitmapInfoHeader);
	if (!m_pData && !m_pBitmapInfoHeader)
	{
		return false;
	}

	ofstream ofs(filename, ios::binary);
	if (ofs.fail())
	{
		return false;
	}

	ofs.write( (char *)&m_BitmapFileHeader, sizeof(BITMAPFILEHEADER) );
	ofs.write( (char *)m_pBitmapInfoHeader, sizeof(BITMAPINFOHEADER) );
	if (m_pRgbQuad)
	{
		ofs.write( (char *)m_pRgbQuad, m_BitmapFileHeader.bfOffBits - \
				sizeof(BITMAPFILEHEADER) - m_pBitmapInfoHeader->biSize );
	}
	ofs.write( (char *)m_pData, \
           m_pBitmapInfoHeader->biHeight* \
           (((m_pBitmapInfoHeader->biWidth * m_pBitmapInfoHeader->biBitCount +31) >>5)<<2 ) \
           );

	ofs.close();
	return true;
}

bool BitMap::SubSample()
{
	assert(m_pData && m_pBitmapInfoHeader);
	if (!m_pData && !m_pBitmapInfoHeader)
	{
		return false;
	}

	assert(m_pBitmapInfoHeader->biHeight>0 && m_pBitmapInfoHeader->biWidth>0);
	long nHeight = (m_pBitmapInfoHeader->biHeight +1) >>1;
	long nWidth = (m_pBitmapInfoHeader->biWidth +1) >>1;
	long bytePerLine = ((nWidth * m_pBitmapInfoHeader->biBitCount + 31) >>5)<<2; // /32*4
	unsigned long dataSize = nHeight * bytePerLine;

	BYTE * pData = new BYTE[dataSize];
	memset(pData, 0, dataSize);
	long oldBytePerLine = \
		((m_pBitmapInfoHeader->biWidth * m_pBitmapInfoHeader->biBitCount +31) >>5)<<2;

	int b = m_pBitmapInfoHeader->biBitCount >>3; //每个像素占用字节数

	for (int h=0; h<nHeight; ++h)
		for (int w=0; w<nWidth; ++w)
			for (int i=0; i<b; ++i)
			{
				*(pData + h*bytePerLine+w*b+i) = \
					*(m_pData + (h<<1)*oldBytePerLine+(w<<1)*b+i);
			}
	// 修改文件头，信息头的相应信息
	m_BitmapFileHeader.bfSize = m_BitmapFileHeader.bfOffBits + dataSize;
	m_pBitmapInfoHeader->biSizeImage = dataSize;
	m_pBitmapInfoHeader->biHeight = nHeight;
	m_pBitmapInfoHeader->biWidth = nWidth;

	delete[] m_pData;
	m_pData = pData;
	return true;
}
