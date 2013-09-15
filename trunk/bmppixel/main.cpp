#include <iostream>
#include "BitMap.h"

using namespace std;

int main(int argc, char *argv[])
{
	BitMap bmp;
    #if 0
	char filename[20] = "bma16.bmp";
	char *of = "bma16_subsample.bmp";
    #endif
    #if 0
	char filename[20] = "lena512color.bmp";
	char of[50] = "lena512color_subsample.bmp";
	#endif
    #if 1
	char filename[20] = "lena512.bmp";
	char of[50] = "lena512_subsample.bmp";
	#endif
	bmp.LoadBmpFile(filename);
	bmp.SubSample();
	bmp.WriteBmpFile(of);
/*
	while(1) {
		int x,y;
		cin >> x >> y;
		unsigned short rgb[3] = {0};
		if ( bmp.GetPixel(x, y, rgb) )
		{
			cout << rgb[0] << ',' << rgb[1] << ',' << rgb[2] << endl;
		}
	}
*/
	return 0;
}
