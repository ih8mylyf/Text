#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include <sstream>
#include "rect.h"

using namespace std;

extern Frame frame;

rect::rect(int x, int y, int w, int h, int xs, int ys, byte r, byte g, byte b){
	setCor(x, y);
	setSize(w, h);
	setSpd(xs, ys);
	this->r=r;
	this->g=g;
	this->b=b;
}

void rect::draw(){
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
	x+=xs;
	y+=ys;
}
