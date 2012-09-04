/**
 * @author Ryan Daughters
 * @date 2012-09-04
 * CSE 274
 * My solution for Program 1
 *
 * @note This solution satisfies goals A.1 (Rectangle), A.2 (Circle), A.3 (Line),
 * A.6 (Tint), E.2 (Transparency), and E.6 (Mouse interaction).
 */

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

	  // surface object that will be used to access the pixel array
	  Surface* mySurface_;
	  uint8_t* myPixels;

	  //methods
	  void horLine(uint8_t* pixels, int x1, int x2, int y, Color8u lineColor);
	  void rectangle(uint8_t* pixels, int startx, int starty, int width, int height, Color8u lineColor);
	  void drawCircle(uint8_t* pixels, double center_x, double center_y, double r, Color8u lineColor);
	  void checkerBoard(uint8_t* pixels, int startX, int startY);
	  void tint(uint8_t* pixels, Color8u c);
	  void checkers(uint8_t*, double startx, double y, Color8u c);

};

void HomeWork1App::setup()
{
	//initialize surface
	mySurface_ = new Surface(kSurfaceSize,kSurfaceSize,false);
	myPixels = (*mySurface_).getData();

	tint(myPixels,Color(125.0,0,0));
	checkerBoard(myPixels,20,20); //draws the checkerboard
	checkers(myPixels,132.5,57.5,Color(0,0,0)); //row 1
	checkers(myPixels,57.5,132.5,Color(0,0,0)); //row 2
	checkers(myPixels,132.5,207.5,Color(0,0,0)); //row 3
	checkers(myPixels,57.5,432.5,Color(50,50,50)); //row 6
	checkers(myPixels,132.5,507.5,Color(50,50,50)); //row 7
	checkers(myPixels,57.5,582.5,Color(50,50,50)); //row 8
}

/* Draws a horizontal line between x1 and x2 at y.
 * @param unit8_t* pixels    surface object that will be modified
 * @param int      x1        starting x-intercept
 * @param int      x2        ending x-intercept
 * @param int      y         y-intercept of the line
 * @param Color8u  lineColor color you wish the line to be
 * @return                   null
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

/* Draw a filled in rectangle that has an upperleft most corner at (startx, starty).
 * @param uint8_t* pixels    surface object that will be modified
 * @param int      startx    x-cordinate of the top left point of the square
 * @param int      starty    y-cordinate of the top left point of the square
 * @param int      width     length you want the x-values to cover
 * @param int      height    length you want the y-values to cover
 * @param Color8u  lineColor color you want the line to be
 * @return                   null
 */
void HomeWork1App::rectangle(uint8_t* pixels, int startx, int starty, int width, int height, Color8u lineColor)
{
	for (int y=starty; y<(starty+height); y++) {
		horLine(pixels,startx,(startx+width),y,lineColor);
	}
};

/** Draw a circle with the center at (center_x, center_y) and a radius r. The core logic
 * of this method was take from Dr.Brinkman's HW01 solution that can be found
 * here: https://github.com/brinkmwj/HW01/blob/master/src/HW01App.cpp.
 *
 * @note this method creates a transparent circle that satisfies E.2
 *
 * @param unit8_t* pixels    surface object that will be modified
 * @param double   center_x  x-intercept of the center of the circle
 * @param double   center_y  y-intercept of the center of the circle
 * @param double   r         raidus of the circle
 * @param Color8u  lineColor color of the circle
 * @return     null
 */
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

/** Draw a checkerboard that is 8x8 and starts at (startX, startY).
 * @param uint8_t* pixels surface object that will be modified
 * @param int      startX x-intercept of the top left corner of the board
 * @param int      startY y-intercept of the top left corner of the board
 * @return                null
 */
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

/** Tint the screen
 * @param uint8_t* pixels surface object that will be modified
 * @param Color8u  c      color you wish to tint the app
 * @return                null
 */
void HomeWork1App::tint(uint8_t* pixels, Color8u c) 
{
	for (int y=0; y<kSurfaceSize; y++) {
		for (int x=0; x<kSurfaceSize; x++) {
			int offSet = 3*(x + y*kSurfaceSize);
			pixels[offSet] = pixels[offSet] + c.r;
		}
	}
};

/** Draw one row of 4 checkers that starts at (startx, starty)
 * @param uint8_t* pixels surface obejct that will be modified
 * @prarm double   startx x-intercept of the center of the far left circle
 * @param double   starty y-intercept of the center of the far left circle
 * @param Color8u  c      color you wish the checkers to be
 * @return                null
 */
void HomeWork1App::checkers(uint8_t* pixels, double startx, double y, Color8u c)
{
	for (int x=0; x<4; x++) {
		drawCircle(pixels, startx, y, 27.5, c);
		startx = startx + 150;
	}
};

void HomeWork1App::mouseDown( MouseEvent event )
{
	int x = event.getX();
	int y = event.getY();

	// when the user clicks the app, a circle will be created where they clicked
	drawCircle(myPixels,x,y,27.5,Color(255,0,0));
}

void HomeWork1App::update()
{
	writeImage("daughtrc.png", *mySurface_); //write the image to a file
}

void HomeWork1App::draw()
{
	gl::draw(*mySurface_); //draw the surface object
}

CINDER_APP_BASIC( HomeWork1App, RendererGl )
