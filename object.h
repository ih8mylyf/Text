#pragma once

#include "Frame.h"

typedef unsigned char byte;

class object {
	public:
		//virtual ~object() { delete [] pixels; }
		virtual void draw();
		virtual void advance(int time){}
		void setCor(int x, int y);
		void setSize(int w, int h);
		void setSpd(int xs, int ys);
	protected:
		int x;
		int y;
		int w;
		int h;
		int xs;
		int ys;
		byte * pixels;
};
