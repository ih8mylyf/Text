#include <iostream>
#include <sstream>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include "Clock.h"

using namespace std;

extern Frame frame;

Clock::Clock(int x, int y) {
	setCor(x, y);
	setSize(384, 384);
	pixels = new byte[w * h * 3];

	const char * cmd =
		"ffmpeg           "
		"-i arial50.bmp   "
		"-f rawvideo      "
		"-pix_fmt rgb24   "
		"-                ";

#ifdef _WIN32
	FILE * pipe = _popen(cmd, "rb");
#else
	FILE * pipe = popen(cmd, "r");
#endif
	if (pipe == 0) {
		std::cout << "error: " << strerror(errno) << std::endl;
		exit(1);
	}
	fread(pixels, 3, w * h, pipe);

	fflush(pipe);
#ifdef _WIN32
	_pclose(pipe);
#else
	pclose(pipe);
#endif
}

void Clock::draw() {
	int x;
	x=this->x;
	for (int i = 0; i < time.size(); ++i) {
		glyph g(time[i]);
		for (int i = 0; i < g.fw; ++i) {
			for (int j = 0; j < g.fh; ++j) {
				byte red   = pixels[(g.fy + j) * w * 3 + (g.fx + i) * 3 + 0];
				byte green = pixels[(g.fy + j) * w * 3 + (g.fx + i) * 3 + 1];
				byte blue  = pixels[(g.fy + j) * w * 3 + (g.fx + i) * 3 + 2];
				frame.blendPixel(
					x + g.xOffset + i,
					y + g.yOffset + j,
					red,
					green,
					blue,
					128
				);
			}
		}
		x += g.xAdvance;
	}
}

void Clock::advance(int time){
	stringstream t;
	t << (int)time;
	this->time = t.str();
}
