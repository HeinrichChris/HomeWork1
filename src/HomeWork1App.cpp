#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/ImageIo.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HomeWork1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

  private:
	  // width and height of the screen
	  static const int kSurfaceSize=900;

	  Surface* mySurface_;
	  uint8_t* myPixels;

	  int startX;
	  int startY;

	  //methods
	  void horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor);
	  void rectangle(uint8_t* pixels, int startx, int starty, int width, int height, Color8u lineColor);
	  void drawCircle(uint8_t* pixels, double center_x, double center_y, double r, Color8u lineColor);
	  void checkerBoard(uint8_t* pixels, int startX, int startY);
	  void tint(uint8_t* pixels, Color8u c);

};

void HomeWork1App::setup()
{
	//initialize surface
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels = (*mySurface_).getData();

	tint(myPixels,Color(125.0,0,0));
	checkerBoard(myPixels,20,20);
	//drawCircle(myPixels,312.5,312.5,100,Color(500,500,500));
}

/* This method should draw a horizontal line between two points. This is
 * a test method to try and draw something using the pixel array.
 */
void HomeWork1App::horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor)
{
	for (int x=x1; x<x2; x++) {
		int offSet = 3*(x + y*kSurfaceSize);
		pixels[offSet] = pixels[offSet] + lineColor.r; //red
		pixels[offSet+1] = pixels[offSet+1] + lineColor.g; //green
		pixels[offSet+2] = pixels[offSet+2] + lineColor.b; //blue
	}
};

/* Draw an empty square that uses both horLine and vertLine methods.
 * parameter int x: the x-cordinate of the top left point of the square.
 * parameter int y: the y-cordinate of the top left point of the square.
 * parameter int sideLength: the length you want each side of the square to be.
 * parameter Color8u lineColor: the color you want the line to be.
 */
void HomeWork1App::rectangle(uint8_t* pixels, int startx, int starty, int width, int height, Color8u lineColor)
{
	for (int y=starty; y<(starty+height); y++) {
		horLine(pixels,startx,(startx+width),y,lineColor);
	}
};

// Draws a cirlce. Is taken from Dr. Brinkman's draw rings method.
void HomeWork1App::drawCircle(uint8_t* pixels, double center_x, double center_y, double r, Color8u lineColor)
{
	if (r <= 0) return;

	for (int y=center_y; y<center_y+r; y++) {
		for (int x=center_x; x<center_x+r; x++) {
			//boundary check
			if (y < 0 || x < 0 || x >= kSurfaceSize || y >= kSurfaceSize) continue;

			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <= r) {
				int offSet = 3*(x + y*kSurfaceSize);
				pixels[offSet] = pixels[offSet]/2 + lineColor.r; //red
				pixels[offSet+1] = pixels[offSet+1]/2 + lineColor.g; //green
				pixels[offSet+2] = pixels[offSet+2]/2 + lineColor.b; //blue
			}
		}
	}
	for (int y=center_y; y>center_y-r; y--) {
		for (int x=center_x; x<center_x+r; x++) {
			//boundary check
			if (y < 0 || x < 0 || x >= kSurfaceSize || y >= kSurfaceSize) continue;

			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <= r) {
				int offSet = 3*(x + y*kSurfaceSize);
				pixels[offSet] = pixels[offSet]/2 + lineColor.r; //red
				pixels[offSet+1] = pixels[offSet+1]/2 + lineColor.g; //green
				pixels[offSet+2] = pixels[offSet+2]/2 + lineColor.b; //blue
			}
		}
	}
	for (int y=center_y; y>center_y-r; y--) {
		for (int x=center_x; x>center_x-r; x--) {
			//boundary check
			if (y < 0 || x < 0 || x >= kSurfaceSize || y >= kSurfaceSize) continue;

			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <= r) {
				int offSet = 3*(x + y*kSurfaceSize);
				pixels[offSet] = pixels[offSet]/2 + lineColor.r; //red
				pixels[offSet+1] = pixels[offSet+1]/2 + lineColor.g; //green
				pixels[offSet+2] = pixels[offSet+2]/2 + lineColor.b; //blue
			}
		}
	}
	for (int y=center_y; y<center_y+r; y++) {
		for (int x=center_x; x>center_x-r; x--) {
			//boundary check
			if (y < 0 || x < 0 || x >= kSurfaceSize || y >= kSurfaceSize) continue;

			int distanceFromCenter = (int)sqrt((double)((x-center_x)*(x-center_x) + (y-center_y)*(y-center_y)));
			if(distanceFromCenter <= r) {
				int offSet = 3*(x + y*kSurfaceSize);
				pixels[offSet] = pixels[offSet]/2 + lineColor.r; //red
				pixels[offSet+1] = pixels[offSet+1]/2 + lineColor.g; //green
				pixels[offSet+2] = pixels[offSet+2]/2 + lineColor.b; //blue
			}
		}
	}
};

//draw a checkerboard
void HomeWork1App::checkerBoard(uint8_t* pixels, int startX, int startY)
{
	int reverse = 0;
	for (int y=0; y<8; y++) {
		for (int x=0; x<8; x++) {
			if (x%2 == 0) {
				if (reverse == 0)
					rectangle(pixels,startX,startY,75,75,Color(25.0,50.0,75.0));
				else
					rectangle(pixels,startX,startY,75,75,Color(500,100,100));
			}
			else {
				if (reverse == 0)
					rectangle(pixels,startX,startY,75,75,Color(500,100,100));
				else
					rectangle(pixels,startX,startY,75,75,Color(25.0,50.0,75.0));
			}
			startX = startX + 75;
		}
		startY = startY + 75;
		startX = 20;
		if (reverse == 0)
			reverse = 1;
		else
			reverse = 0;
	}
};

void HomeWork1App::tint(uint8_t* pixels, Color8u c) 
{
	for (int y=0; y<kSurfaceSize; y++) {
		for (int x=0; x<kSurfaceSize; x++) {
			int offSet = 3*(x + y*kSurfaceSize);
			pixels[offSet] = pixels[offSet] + c.r;
		}
	}
};

void HomeWork1App::mouseDown( MouseEvent event )
{
}

void HomeWork1App::update()
{
	writeImage("daughtrc.png", *mySurface_);
}

void HomeWork1App::draw()
{
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
