/** @file main.cpp
 *  @brief Entry point into our program.
 *  
 *  Welcome to the Great Looking Software Render 
 *  code base (Yes, I needed something with a gl prefix).
 *
 *  This is where you will implement your graphics API.
 *
 *  Compile on the terminal with: 
 *
 *  clang++ -std=c++11 main.cpp -o main
 *
 *  @author Mike Shah
 *  @bug No known bugs.
 */

// Load our libraries
#include <iostream>

// Some define values
#define WINDOW_HEIGHT 320
#define WINDOW_WIDTH 320

// C++ Standard Libraries
#include <iostream>

// User libraries
#include "GL.h"
#include "Color.h"
#include "TGA.h"
#include "Maths.h"

// Create a canvas to draw on.
TGA canvas(WINDOW_WIDTH,WINDOW_HEIGHT);


// Implementation of Bresenham's Line Algorithm
// The input to this algorithm is two points and a color
// This algorithm will then modify a canvas (i.e. image)
// filling in the appropriate colors.
void drawLine(Vec2 v0, Vec2 v1, TGA& image, ColorRGB c){
    bool steep = false;
    if(std::abs(v0.x-v1.x)<std::abs(v0.y-v1.y)){
        // If the line is steep we want to transpose the image.
        std::swap(v0.x,v0.y);
        std::swap(v1.x,v1.y);
        steep = true;
    }
    if(v0.x>v1.x){  // make it left-to-right
        std::swap(v0.x, v1.x);
        std::swap(v0.y, v1.y);
    }
    for(int x = v0.x; x <= v1.x; ++x){
        float t = (x-v0.x)/(float)(v1.x-v0.x);
        int y = v0.y*(1.0f-t) + v1.y*t;
        if(steep){
            canvas.setPixelColor(y,x,c);
        }else{
            canvas.setPixelColor(x,y,c);
        }
    }
}

// The determinant of vectors where p is the query point. 0 if on the line,
// - if on one side, + if on the other side.
// https://stackoverflow.com/questions/1560492/how-to-tell-whether-a-point-is-to-the-right-or-left-side-of-a-line  
int determinant(Vec2 v0, Vec2 v1, Vec2 p) {
   return ((v1.x - v0.x)*(p.y - v0.y) - (v1.y - v0.y)*(p.x - v0.x)); 
}

// Are the reference point and the compare point on the same side of the 
// line defined by (v0, v1)?
bool sameSide(Vec2 v0, Vec2 v1, Vec2 reference, Vec2 compare) {
	  int det1 = determinant(v0, v1, reference);
	  int det2 = determinant(v0, v1, compare);
    return ((det1 < 0) == (det2 < 0));
}

// Draw a triangle
void triangle(Vec2 v0, Vec2 v1, Vec2 v2,TGA& image, ColorRGB c){
    if(glFillMode==LINE){
        drawLine(v0,v1,image,c);
        drawLine(v1,v2,image,c);
        drawLine(v2,v0,image,c);
    }
    else if (glFillMode == FILL) {
				for (int x = 0; x < WINDOW_WIDTH; x++) {
					  for (int y = 0; y < WINDOW_HEIGHT; y++) {
					  	  Vec2 pixel = Vec2(x, y);
								if(sameSide(v0, v1, v2, pixel) &&
									 sameSide(v0, v2, v1, pixel) &&
									 sameSide(v1, v2, v0, pixel)) {
									canvas.setPixelColor(pixel.x, pixel.y, c);
								}
						}
				}
		}
}

// Main
int main(){

    // A sample of color(s) to play with
    ColorRGB red;
    red.r = 255; red.g = 0; red.b = 0;
        
    ColorRGB green;
    green.r = 0; green.g = 255; green.b = 0;
    
    ColorRGB blue;
    blue.r = 0; blue.g = 0; blue.b = 255;

    // Points for our Line
    Vec2 line[2] = {Vec2(0,0), Vec2(100,100)};

    // Set the fill mode
    glPolygonMode(FILL);

    // Draw a line
    drawLine(line[0],line[1],canvas,red);

    // Data for our triangle
    Vec2 tri[3] = {Vec2(160,60),Vec2(150,10),Vec2(75,190)};
    Vec2 tri2[3] = {Vec2(360,360),Vec2(200,200),Vec2(320,270)};
    Vec2 tri3[3] = {Vec2(100,200),Vec2(200,150),Vec2(150,230)};

    // Draw a triangle
    triangle(tri[0],tri[1],tri[2],canvas,red);
    triangle(tri2[0],tri2[1],tri2[2],canvas,green);
    triangle(tri3[0],tri3[1],tri3[2],canvas,blue);

    // Output the final image
    canvas.outputTGAImage("graphics_lab2.ppm");

    return 0;
}
