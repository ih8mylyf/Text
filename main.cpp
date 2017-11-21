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
const int duration_in_seconds = 10;


class Frame {
public:
	Frame(int w, int h);
	~Frame();
	void setPixel(int x, int y, byte r, byte g, byte b);
	void clear();
	bool isOutside(int x, int y) const;
	void write(FILE * file) const;


private:
	byte * pixels;
	int w;
	int h;
};


class object {	
	public:
		void draw();
	private:
		byte * pixels;
		int x;
		int y;
		int w;
		int h;
		int xs;
		int ys;
};

class image : public object {
	public: 
		image(int x, int y, int xs, int ys);
		~image() { delete [] pixels; }
		void * load(const char * filename, int w, int h);
		void draw();
	private:
		byte * pixels;
		int w;
		int h;
		int x;
		int y;
		int xs;
		int ys;
};


class rect : public object {
	public:
		rect(int x, int y, int w, int h, int xs, int ys, byte r, byte g, byte b);
		void setPos(int x, int y);
		void setColor(byte r, byte g, byte b);
		void setSize(int w, int h);
	private:
		byte * pixels;
		int x;
		int y;
		int w;
		int h;
		int xs;
		int ys;	
		byte r;
		byte g;
		byte b;
};

image::image(int x, int y, int xs, int ys){
	this->x=x;
	this->y=y;
	this->xs=xs;
	this->ys=ys;
}

void * image::load(const char * filename, int w, int h){
	this->w = w;
	this->h = h;
	pixels = new byte[w * h * 3];

	const char * cmd = 
		"ffmpeg            "
		"-i ball.png      "
		"-f rawvideo       "
		"-pix_fmt rgb24    "
		"-vf scale=100x100 "
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

Frame frame(720, 480);

void image::draw(){
	for (int i = 0; i < w; ++i)
		for (int j = 0; j < h; ++j){
			byte r = pixels[j * w * 3 + i * 3 + 0];
			byte g = pixels[j * w * 3 + i * 3 + 1];
			byte b = pixels[j * w * 3 + i * 3 + 2];
			frame.setPixel(x + i, y + j, r, g, b);
		}
	x+=xs;
	y+=ys;
}

Frame::Frame(int w, int h)  {
	this->w = w;
	this->h = h;
	pixels = new byte[w * h * 3];
}

Frame::~Frame() {
	delete pixels;
}

void Frame::setPixel(int x, int y, byte r, byte g, byte b) {
	pixels[y * w * 3 + x * 3 + 0] = r;
	pixels[y * w * 3 + x * 3 + 1] = g;
	pixels[y * w * 3 + x * 3 + 2] = b;
}

void Frame::clear() {
	memset(pixels, 0, h * w * 3);
}

bool Frame::isOutside(int x, int y) const {
	return x < 0 || x >= w || y < 0 || y >= h;
}

void Frame::write(FILE * file) const {
	fwrite(pixels, 3, w * h, file);
}

rect::rect(int x, int y, int w, int h, int xs, int xy, byte r, byte g, byte b){
	this->x=x;
	this->y=y;
	this->w=w;
	this->h=h;
	this->xs=xs;
	this->ys=ys;
	this->r=r;
	this->g=g;
	this->b=b;
	pixels = new byte[w * h * 3];
	for(int i = 0; i < w; ++i)
		for(int j = 0; j < h; ++j){
			pixels[j * w * 3 + i * 3 + 0]=r;
			pixels[j * w * 3 + i * 3 + 1]=g;
			pixels[j * w * 3 + i * 3 + 2]=b;
		}

}

void rect::setPos(int x, int y){
    this->x=x;
    this->y=y;
}

void rect::setSize(int w, int h){
    this->w=w;
    this->h=h;
}

void rect::setColor(byte r, byte g, byte b){
    this->r=r;
    this->g=g;
    this->b=b;
}


int main(int argc, char * argv[]) {
	// Construct the ffmpeg command to run.
	rect a(0, 0, 40, 10, 2, 0, 0x00, 0xff, 0x00);
	rect b(710, 460, 10, 20, 0, 2, 0x00, 0x00, 0xff);
	image ball(0, 50, 5, 0);
	ball.load("ball.png", 100, 100);	
	image ball2(720, 180, -2, 0);
	ball2.load("ball.png", 100, 100);
	image ball3(0, 380, 2, -2);
	ball3.load("ball.png", 100, 100);
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

	for (int i = 0; i < num_frames/2; ++i){
		frame.clear();
		ball.draw();
		ball2.draw();
		ball3.draw();
//		a.draw();
//		b.draw();
		frame.write(pipe);
	}
	
	
	
	/*	for (int i = 0; i < num_frames/2 ; ++i) {
		double time_in_seconds = i / frames_per_second;
		clear_frame();
		a.Down(time_in_seconds);
		b.Up (time_in_seconds);
		c.Right (time_in_seconds);
		d.Left (time_in_seconds);
		fwrite(frame, 3, W * H, pipe);
	}
	d.setSize(5000, 5000);
	fwrite(frame, 3, W * H, pipe);
	a = rect(350, 230, 20, 20, 50, 0x00, 0xff, 0x00);
	b= rect(340, 220, 40, 40, 50, 0x00, 0x00, 0xff);
	double time;
	for (int i = 0; i < num_frames; ++i){
		time = i / frames_per_second;		
		clear_frame();
		a.UpRight(time);
		a.DownLeft(time);
		a.DownRight(time);
		a.UpLeft(time);
		b.Right(time);
		b.Left(time);
		b.Up(time);
		b.Down(time);
		fwrite(frame, 3, W * H, pipe);
	}
*/	
	
	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;

	return 0;
}
