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
	  static const int appWidth=800;
	  static const int appHeight=600;
	  static const int kSurfaceSize=1024;

	  Surface* mySurface_;
	  uint8_t* myPixels;

	  //methods
	  void blackOutWindow(uint8_t* pixels);
	  void horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor);
	  void vertLine(uint8_t* pixels, int y1, int y2, int x, Color8u lineColor);

};

void HomeWork1App::setup()
{
	//initialize surface
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels = (*mySurface_).getData();

	//call blackOutWindow method
	blackOutWindow(myPixels);
	horLine(myPixels,200,400,200,Color(500,500,500));
	vertLine(myPixels,100,300,300,Color(500,500,500));
}

/* color the window by accessing the surface pixel's array directly. This is taken
 * from Cary Willard's code and is being used for educational purpose to understand how to 
 * correctly access the surface pixel array. This will now appear in my final project.
 */
void HomeWork1App::blackOutWindow(uint8_t* pixels)
{
	Color8u c = Color(0,0,0);

	for (int y=0; y<appHeight; y++) {
		for (int x=0; x<appWidth; x++) {
			int offSet = 3*(x + y * kSurfaceSize);
			pixels[offSet] = pixels[offSet] + c.r; //red
			pixels[offSet+1] = pixels[offSet] + c.g; //green
			pixels[offSet+2] = pixels[offSet] + c.b; //blue
		}
	}
}; 

//Draw a vertical line using the same approach as the horLine method
void HomeWork1App::vertLine(uint8_t* pixels, int y1, int y2, int x, Color8u lineColor)
{
	for (int y=y1; y<y2; y++) {
		int offSet = 3*(x + y*kSurfaceSize);
		pixels[offSet] = pixels[offSet] + lineColor.r; //red
		pixels[offSet+1] = pixels[offSet] + lineColor.g; //green
		pixels[offSet+2] = pixels[offSet] + lineColor.b; //blue
	}
};

/* This method should draw a horizontal line between two points. This is
 * a test method to try and draw something using the pixel array.
 */
void HomeWork1App::horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor)
{
	for (int x=x1; x<x2; x++) {
		int offSet = 3*(x + y*kSurfaceSize);
		pixels[offSet] = pixels[offSet] + lineColor.r; //red
		pixels[offSet+1] = pixels[offSet] + lineColor.g; //green
		pixels[offSet+2] = pixels[offSet] + lineColor.b; //blue
	}
};

void HomeWork1App::mouseDown( MouseEvent event )
{
}

void HomeWork1App::update()
{
}

void HomeWork1App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) );
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
