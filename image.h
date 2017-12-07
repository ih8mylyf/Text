#pragma once
#include "object.h"
#include "Frame.h"

class image : public object {
	public:
		image(int x, int y, int xs, int ys);
		void draw();
		void advance(int time){x+=xs;y+=ys;}
		void * load(const char * filename, int w, int h);
};
