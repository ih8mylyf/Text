#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <vector>
#include "Frame.h"
#include "object.h"
#include "Clock.h"
#include "image.h"
#include "rect.h"

typedef unsigned char byte;   

using namespace std;

#define W 720
#define H 480

const double frames_per_second = 60; 
const int duration_in_seconds = 20;

Frame frame(720, 480);

int main(int argc, char * argv[]) {
	rect a(40, 40, 40, 50, 2, 0, 0x00, 0xff, 0x00);
	rect b(650, 0, 10, 20, 0, 4, 0x00, 0xff, 0xff);
	image ball(0, 50, 5, 0);
	ball.load("ball.png", 221, 228);	
	image ball2(720, 180, -2, 0);
	ball2.load("ball.png", 221, 228);
	image ball3(0, 380, 2, -2);
	ball3.load("ball.png", 221, 228);
	Clock TIME(50, 30);

	vector<object *> objects;
	objects.push_back(&a);
	objects.push_back(&b);
	objects.push_back(&ball);
	objects.push_back(&ball2);
	objects.push_back(&ball3);
	objects.push_back(&TIME);

	const char * cmd = 
		"ffmpeg              "
		"-y                  "
		"-hide_banner        "
		"-f rawvideo         " // input to be raw video data
		"-pixel_format rgb24 "
		"-video_size 720x480 "
		"-r 60               " // frames per second
		"-i -                " // read data from the standard input stream
		"-pix_fmt yuv420p    " // to render with Quicktime
		"-vcodec mpeg4       "
		"-an                 " // no audio
		"-q:v 5              " // quality level; 1 <= q <= 32
		"output.mp4          ";

	// Run the ffmpeg command and get pipe to write into its standard input stream.
	FILE * pipe = popen(cmd, "w");
	if (pipe == 0) {
		cout << "error: " << strerror(errno) << endl;
		return 1;
	}

	int num_frames = duration_in_seconds * frames_per_second;

	for (int i = 0; i < num_frames; ++i){
		frame.clear();
		for (int j = 0; j < objects.size() ; j++){
			objects[j]->draw();
			objects[j]->advance(i / frames_per_second);
		}
		frame.write(pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;
	return 0;
}
