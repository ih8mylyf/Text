#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <stdio.h>
#include <cassert>
#include <cstring>
#include <cerrno>
#include <vector>


typedef unsigned char byte;   

using namespace std;

#define W 720
#define H 480

const double frames_per_second = 60; 
const int duration_in_seconds = 20;


class Frame {
public:
	Frame(int w, int h);
	~Frame();
	void setPixel(int x, int y, byte r, byte g, byte b);
	void blendPixel(int x, int y, byte r, byte g, byte b, byte a);
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
		//virtual ~object() { delete [] pixels; }
		virtual void draw();
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

class Clock : public object {
	public:
		Clock();
		void draw(const string & text, double x, double y);
		void glyph(char c);
	private:
		int fx;
		int fy;
		int fw;
		int fh;
		int xAdvance;
		int xOffset;
		int yOffset;
};


class image : public object {
	public: 
		image(int x, int y, int xs, int ys);
		void draw();
		void * load(const char * filename, int w, int h);
};


class rect : public object {
	public:
		rect(int x, int y, int w, int h, int xs, int ys, byte r, byte g, byte b);
		void draw();
	private:
		byte r;
		byte g;
		byte b;
};

Frame frame(720, 480);

Clock::Clock() {
	int w=384;
	int h=384;
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

void Clock::draw(const string & text, double x, double y) {
	int w=384;
	int h=384;
	for (int i = 0; i < text.size(); ++i) {
		glyph(text[i]);
		for (int i = 0; i < fw; ++i) {
			for (int j = 0; j < fh; ++j) {
				byte red   = pixels[(fy + j) * w * 3 + (fx + i) * 3 + 0];
				byte green = pixels[(fy + j) * w * 3 + (fx + i) * 3 + 1];
				byte blue  = pixels[(fy + j) * w * 3 + (fx + i) * 3 + 2];
				frame.blendPixel(
					x + xOffset + i,
					y + yOffset + j,
					red,
					green,
					blue,
					128
				);
			}
		}
		x += xAdvance;
	}
}



void Clock::glyph(char c){
	if (c == '0') {
		fx = 344;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
	} else if(c == '1') {
		fx = 354;
		fy = 56;
		fw = 22;
		fh = 40;
		xOffset = 8;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '2') {
		fx = 178;
		fy = 142;
		fw = 30;
		fh = 40;
		xOffset = 3;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '3'){
		fx = 312;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 3;
		yOffset = 8;
		xAdvance = 28;
	}else if(c == '4') {
		fx = 146;
		fy = 320;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '5') {
		fx = 146;
		fy = 278;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '6') {
		fx = 280;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 5;
		yOffset = 8;
		xAdvance = 28;
	}else if(c == '7') {
		fx = 210;
		fy = 142;
		fw = 28;
		fh = 40;
		xOffset = 7;
		yOffset = 10;
		xAdvance = 28;
	} else if(c == '8') {
		fx = 248;
		fy = 98;
		fw = 30;
		fh = 40;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
	} else  {
		fx = 216;
		fy = 98;
		fw = 30;
		fh = 42;
		xOffset = 4;
		yOffset = 8;
		xAdvance = 28;
}  
}


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

//Frame frame(720, 480);

void object::setCor(int x, int y){
	this->x=x;
	this->y=y;
}

void object::setSize(int w, int h){
	this->w=w;
	this->h=h;
}

void object::setSpd(int xs, int ys){
	this->xs=xs;
	this->ys=ys;
}

void object::draw(){
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, 0x00, 0x00, 0xff);
		}
	}
}
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
	delete [] pixels;
}

void Frame::setPixel(int x, int y, byte r, byte g, byte b) {
	if(isOutside(x, y)) return;
	pixels[y * w * 3 + x * 3 + 0] = r;
	pixels[y * w * 3 + x * 3 + 1] = g;
	pixels[y * w * 3 + x * 3 + 2] = b;
}

void Frame::blendPixel(int x, int y, byte r, byte g, byte b, byte a) {
	if (x < 0 || x >= w || y < 0 || y >= h) return;
    double q = a / 255.0;
    double p = 1 - q;
	pixels[y * w * 3 + x * 3 + 0] = p * pixels[y * w * 3 + x * 3 + 0] + q * r;
	pixels[y * w * 3 + x * 3 + 1] = p * pixels[y * w * 3 + x * 3 + 1] + q * g;
	pixels[y * w * 3 + x * 3 + 2] = p * pixels[y * w * 3 + x * 3 + 2] + q * b;
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

rect::rect(int x, int y, int w, int h, int xs, int ys, byte r, byte g, byte b){
	setCor(x, y);
	setSize(w, h);
	setSpd(xs, ys);
	this->r=r;
	this->g=g;
	this->b=b;
}

void rect::draw(){
	int x0 = x;
	int x1 = x + w;
	int y0 = y;
	int y1 = y + h;
	for (int y = y0; y < y1; ++y) {
		for (int x = x0; x < x1; ++x) {
			frame.setPixel(x, y, r, g, b);
		}
	}
	x+=xs;
	y+=ys;
}

int main(int argc, char * argv[]) {
	rect a(40, 40, 40, 50, 2, 0, 0x00, 0xff, 0x00);
	rect b(650, 0, 10, 20, 0, 4, 0x00, 0xff, 0xff);
	image ball(0, 50, 5, 0);
	ball.load("ball.png", 221, 228);	
	image ball2(720, 180, -2, 0);
	ball2.load("ball.png", 221, 228);
	image ball3(0, 380, 2, -2);
	ball3.load("ball.png", 221, 228);
	Clock TIME;
		

	vector<object *> objects;
	objects.push_back(&a);
	objects.push_back(&b);
	objects.push_back(&ball);
	objects.push_back(&ball2);
	objects.push_back(&ball3);





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
		for (int x = 0; x < objects.size() ; x++)
			objects[x]->draw();
		stringstream elapsedSeconds;
		elapsedSeconds << (int) (i / frames_per_second);
		TIME.draw(elapsedSeconds.str(), 50, 30);
		frame.write(pipe);
	}
	
	
	
	
	fflush(pipe);
	pclose(pipe);

	cout << "num_frames: " << num_frames << endl;
	cout << "Done." << endl;


	return 0;
}
