#include <iostream>
#include <fstream>
#include "GetPixel.h"

using namespace std;

char * pBuf;

int main(int argc, char *argv[])
{
	char filename[20] = "bma16.bmp";
	ifstream ifs(filename, ios::binary);
	ifs.seekg(0, ios::end);
	int size = ifs.tellg();
	ifs.seekg(0, ios::beg);

	pBuf = new char[size];
	ifs.read( pBuf, sizeof(BYTE)*size );

	while(1) {
		int x,y;
		cin >> x >> y;
		unsigned short rgb[3] = {0};
		if ( GetPixel(pBuf, x, y, rgb) )
		{
			cout << rgb[0] << ',' << rgb[1] << ',' << rgb[2] << endl;
		}
	}
}
