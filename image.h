#pragma once
#include "object.h"
#include "Frame.h"

class image : public object {
	public:
		image(int x, int y, int xs, int ys);
		void draw();
		void advance(int time){x+=xs;y+=ys;} //'time' not needed, but still put in place in order to match the Clock's advance function
		void * load(const char * filename, int w, int h);
};
