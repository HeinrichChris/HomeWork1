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
	  static const int kSurfaceSize=625;

	  Surface* mySurface_;
	  uint8_t* myPixels;

	  //variables
	  int squareStartX;
	  int squareStartY;
	  int squareLength;
	  int cycleLevel;

	  //methods
	  void blackOutWindow(uint8_t* pixels);
	  void horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor);
	  void vertLine(uint8_t* pixels, int y1, int y2, int x, Color8u lineColor);
	  void square(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor);
	  void filledSquare(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor);
	  void diagLine(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor);

};

void HomeWork1App::setup()
{
	//initialize surface
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels = (*mySurface_).getData();

	//initialize variables
	squareStartX = 0;
	squareStartY = 0;
	squareLength = kSurfaceSize;
	cycleLevel = 1;

	//blackOutWindow(myPixels);
	//horLine(myPixels,200,400,200,Color(500,500,500));
	//vertLine(myPixels,100,300,300,Color(500,500,500));
	//square(myPixels,squareStartX,squareStartY,squareLength,Color(500,500,500));
	//filledSquare(myPixels,200,100,200,Color(500,500,500));
	//diagLine(myPixels,0,0,400,Color(500,500,500));
	
}

/* color the window by accessing the surface pixel's array directly. This is taken
 * from Cary Willard's code and is being used for educational purpose to understand how to 
 * correctly access the surface pixel array. This will now appear in my final project.
 */
void HomeWork1App::blackOutWindow(uint8_t* pixels)
{
	Color8u c = Color(0,0,0);

	for (int y=0; y<kSurfaceSize; y++) {
		for (int x=0; x<kSurfaceSize; x++) {
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

/* Draw an empty square that uses both horLine and vertLine methods.
 * parameter int x: the x-cordinate of the top left point of the square.
 * parameter int y: the y-cordinate of the top left point of the square.
 * parameter int sideLength: the length you want each side of the square to be.
 * parameter Color8u lineColor: the color you want the line to be.
 */
void HomeWork1App::square(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor)
{
	//top line
	horLine(pixels,x,(x+sideLength),y,lineColor);
	//right line
	vertLine(pixels,y,(y+sideLength),(x+sideLength),lineColor);
	//bottom line
	horLine(pixels,x, (x+sideLength),(y+sideLength),lineColor);
	//left line
	vertLine(pixels,y,(y+sideLength),x,lineColor);
};

/* Draw a filled in square that uses the horLine method
 * parameter int x: the x-cordinate of the top left point of the square.
 * parameter int y: the y-cordinate of the top left point of the square.
 * parameter int sideLength: the length you want each side of the square to be.
 * parameter Color8u lineColor: the color you want the line to be.
 */
void HomeWork1App::filledSquare(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor)
{
	for (int i=y; i<(y+sideLength); i++) {
		horLine(pixels,x,(x+sideLength),i,lineColor);
	}
};

/* Draw a diagonal line
 * parameter int x: the x-cordinate of the bottom point of the line.
 * parameter int y: the y-cordinate of the bottom point of the line.
 * parameter int sideLength: the length you want the line the be.
 * parameter Color8u lineColor: the color you want the line to be.
 */
void HomeWork1App::diagLine(uint8_t* pixels, int x, int y, int sideLength, Color8u lineColor)
{
	int starty = y; //will be increased by 1 after each loop

	for (int x1=x; x1<(x+sideLength); x1++) {
		//change the pixel color
		int offSet = 3*(x1 + starty * kSurfaceSize);
		pixels[offSet] = pixels[offSet] + lineColor.r; //red
		pixels[offSet+1] = pixels[offSet] + lineColor.g; //green
		pixels[offSet+2] = pixels[offSet] + lineColor.b; //blue
		
		starty++; //increase y by 1
	}
};

void HomeWork1App::mouseDown( MouseEvent event )
{
}

void HomeWork1App::update()
{
	if (cycleLevel = 1) {
		if (squareLength <= 0) {
			blackOutWindow(myPixels);
			cycleLevel = 2;
		}
		else {
			square(myPixels,squareStartX,squareStartY,squareLength,Color(500,500,500));
			squareStartX = squareStartX + 20;
			squareStartY = squareStartY + 20;
			squareLength = squareLength - 40;
		}
	}

}

void HomeWork1App::draw()
{
	// clear out the window with black
	//gl::clear( Color( 0, 0, 0 ) );
	gl::draw(*mySurface_);
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
