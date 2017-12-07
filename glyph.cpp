#include "glyph.h"

using namespace std;

extern Frame frame;


glyph::glyph(char c){
	if (c == '0') {
		fx = 344;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
	} else if(c == '1') {
		fx = 354;
		fy = 56;
		fw = 22;
		fh = 40;
		xOffset = 8;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '2') {
		fx = 178;
		fy = 142;
		fw = 30;
		fh = 40;
		xOffset = 3;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '3'){
		fx = 312;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 3;
		yOffset = 8;
		xAdvance = 28;
	}else if(c == '4') {
		fx = 146;
		fy = 320;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '5') {
		fx = 146;
		fy = 278;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '6') {
		fx = 280;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 5;
		yOffset = 8;
		xAdvance = 28;
	}else if(c == '7') {
		fx = 210;
		fy = 142;
		fw = 28;
		fh = 40;
		xOffset = 7;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '8') {
		fx = 248;
		fy = 98;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
	} else  {
		fx = 216;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
}  
}

