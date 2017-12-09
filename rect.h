#pragma once
#include "object.h"
#include "Frame.h"

typedef unsigned char byte;

class rect : public object {
	public:
		rect(int x, int y, int w, int h, int xs, int ys, byte r, byte g, byte b);
		void draw();
		void advance(int time){x+=xs;y+=ys;} //parameter time is not needed for this function, however is kept to match the Clock's advance function
	private:
		byte r;
		byte g;
		byte b;
};
