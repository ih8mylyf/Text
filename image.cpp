#include <stdio.h>
#include <cstring>
#include <iostream>
#include <cerrno>
#include "image.h"

using namespace std;

extern Frame frame;

image::image(int x, int y, int xs, int ys){
	setCor(x, y);
	setSpd(xs, ys);
}

void * image::load(const char * filename, int w, int h){
	setSize(w, h);
	pixels = new byte[w * h * 3];

	const char * cmd = 
		"ffmpeg            "
		"-i ball.png      "
		"-f rawvideo       "
		"-pix_fmt rgb24    "
		"-vf scale=221x228 "
		"-                 ";
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

void image::draw(){
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j){
			byte r = pixels[j * w * 3 + i * 3 + 0];
			byte g = pixels[j * w * 3 + i * 3 + 1];
			byte b = pixels[j * w * 3 + i * 3 + 2];
			frame.setPixel(x + i, y + j, r, g, b);
		}

}

