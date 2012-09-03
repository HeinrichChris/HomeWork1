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

};

void HomeWork1App::setup()
{
	//initialize surface
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels = (*mySurface_).getData();

	//call blackOutWindow method
	blackOutWindow(myPixels);
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
