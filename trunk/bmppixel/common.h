#ifndef _COMMON_H_
#define _COMMON_H_
#pragma pack(1)
/*
#define TRUE 1
#define FALSE 0
typedef unsigned char bool;
*/

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long LONG;

typedef struct tagBITMAPFILEHEADER {
  WORD bfType;
  DWORD bfSize;
  WORD bfReserved1;
  WORD bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER{
  DWORD biSize; //本结构所占字节数，实际上该结构占用40个字节，但Windows每次还是需要您亲自添上
  LONG biWidth; //位图的宽度，单位为像素
  LONG biHeight; //位图的高度，单位为像素
  WORD biPlanes; //目标设备的平面数，约定必须为1
  WORD biBitCount;//每个像素所需的位数，必须是1（双色）、 4（16色）、8（256色）、24（真彩色）或32（32位真彩）之一
  DWORD biCompression; //位图压缩类型，必须是0（不压缩）、1（BI_RLE8压缩类型）或2（BI_RLE4压缩类型）之一
  DWORD biSizeImage; //位图的大小，以字节为单位，对于BI_RGB必须设置为0，对于压缩文件请参考MSDN
  LONG biXPelsPerMeter; //水平分辨率，每米像素数，一般不用关心，设为0
  LONG biYPelsPerMeter; //垂直分辨率，每米像素数，一般不用关心，设为0
  DWORD biClrUsed;//位图实际使用的颜色表中的颜色数，一般不用关心，设为0
  DWORD biClrImportant;//位图显示过程中重要的颜色数，一般不用关心，设为0
} BITMAPINFOHEADER;

typedef struct tagRGBQUAD {
  BYTE rgbBlue;//蓝色
  BYTE rgbGreen; // 绿色
  BYTE rgbRed; // 红色
  BYTE rgbReserved;// 保留
} RGBQUAD;
 /*
typedef struct tagBITMAPINFO
{
  BITMAPINFOHEADER bmiHeader; // 位图信息头
  RGBQUAD bmiColors[N]; // 颜色表
} BITMAPINFO;
*/
#endif
