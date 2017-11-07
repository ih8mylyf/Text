#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>

typedef unsigned char byte;

using namespace std;

#define W 720
#define H 480

const double frames_per_second = 30; 
const int duration_in_seconds = 5;

unsigned char frame[H][W][3];

class rect {
	public:
		rect(int x, int y, int w, int h, double s, byte r, byte g, byte b);
  void setPos(int x, int y);
  void setSize(int w, int h);
  void setSpeed(int s);
  void setColor(byte r, byte g, byte b);
 	void Down(double t);
		void Up(double t);
		void Right(double t);
		void Left(double t);
		void DownRight(double t);
		void DownLeft(double t);
		void UpRight(double t);
		void UpLeft(double t);
		void clamp(int * x, int * y);
	private:
		int w;
		int h;
		double s;
		int x;
		int y;
		byte r;
		byte g;
		byte b;
};

rect::rect(int x, int y, int w, int h, double s, byte r, byte g, byte b){
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
	this->s=s;
	this->r=r;
	this->g=g;
	this->b=b;
}

void rect::setPos(int x, int y){
    this->x=x;
    this->y=y;
}

void rect::setSize(int w. int h){
    this->w=w;
    this->h=h;
}

void rect::setColor(byte r, byte g, byte b){
    this->r=r;
    this->g=g;
    this->b=b;
}

void rect::Down(double t){
  int x0 = x;
	int x1 = x + w;
	int y0 = y+t*s;
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::Up(double t){
	int x0 = x;
	int x1 = x + w;
	int y0 = y-(t*s);
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::Right(double t){
	int x0 = x+t*s;
	int x1 = (x+t*s) + w;
	int y0 = y;
	int y1 = y + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::Left(double t){
	int x0 = x-(t*s);
	int x1 = (x+t*s) + w;
	int y0 = y;
	int y1 = y + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::DownRight(double t){
	int x0 = x+t*s;
	int x1 = (x+t*s) + w;
	int y0 = y+t*s;
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::DownLeft(double t){
	int x0 = x-t*s;
	int x1 = (x+t*s) + w;
	int y0 = y+t*s;
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::UpRight(double t){
	int x0 = x+t*s;
	int x1 = (x+t*s) + w;
	int y0 = y-t*s;
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}

void rect::UpLeft(double t){
	int x0 = x-t*s;
	int x1 = (x+t*s) + w;
	int y0 = y-t*s;
	int y1 = (y+t*s) + h;
	clamp(&x0, &y0);
	clamp(&x1, &y1);
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame[y][x][0] = r;
			frame[y][x][1] = g;
			frame[y][x][2] = b;
		}
	}
}



void rect::clamp(int * x, int * y){
	if (*x < 0) *x = 0; else if (*x >= W) *x = W - 1;
	if (*y < 0) *y = 0; else if (*y >= H) *y = H - 1;
}

void clear_frame() { memset(frame, 0, sizeof(frame)); }

int main(int argc, char * argv[]) {
	// Construct the ffmpeg command to run.
	rect a(0, 0, 20, 10, 80, 0x00, 0xff, 0x00);
	rect b(710, 10, 10, 20, 60, 0x00, 0x00, 0xff);
	rect c(0, 30, 50, 60, 40, 0xff, 0x00, 0x00);
	rect d(600, 90, 120, 70, 20, 0x00, 0xff, 0x00);
	
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

	// Write video frames into the pipe.
	int num_frames = duration_in_seconds * frames_per_second;
	for (int i = 0; i < num_frames; ++i) {
		double time_in_seconds = i / frames_per_second;
		clear_frame();
		a.Right(time_in_seconds);
		b.Left (time_in_seconds);
		c.Right (time_in_seconds);
		d.Left (time_in_seconds);
		fwrite(frame, 3, W * H, pipe);
	}

	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
