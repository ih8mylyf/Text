#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include "object.h"


using namespace std;

extern Frame frame;

void object::setCor(int x, int y){
	this->x=x;
	this->y=y;
}

void object::setSize(int w, int h){
	this->w=w;
	this->h=h;
}

void object::setSpd(int xs, int ys){
	this->xs=xs;
	this->ys=ys;
}

void object::draw(){
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, 0x00, 0x00, 0xff);
		}
	}
}
