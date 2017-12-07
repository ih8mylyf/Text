#pragma once

#include <string>
#include "Frame.h"

using namespace std;

typedef unsigned char byte;

class glyph {
private:
	glyph(char c);
	int fx;     
	int fy;     
	int fw;     
	int fh;      
	int xAdvance; 
	int xOffset; 
	int yOffset;  

	friend class Clock;
};
