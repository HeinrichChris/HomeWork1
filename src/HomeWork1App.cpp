#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class HomeWork1App : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void HomeWork1App::setup()
{
}

void HomeWork1App::mouseDown( MouseEvent event )
{
}

void HomeWork1App::update()
{
}

void HomeWork1App::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
