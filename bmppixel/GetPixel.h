#ifndef _GET_PIXEL_H_
#define _GET_PIXEL_H_

#include "common.h"

//enum { NULL_POINTER, EXCEED } error_code;

//bool LoadBmp(const char * filename);
bool GetPixel(char *pBuf, int x, int y, unsigned short rgb[3]);

#endif
