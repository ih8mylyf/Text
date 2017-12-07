#pragma once

#include <string>
#include "object.h"
#include "Frame.h"
#include "glyph.h"

using namespace std;

class Clock : public object {
	public:
		Clock(int x, int y);
		void draw();
		void advance(int time);
	private:
		string time;
};
