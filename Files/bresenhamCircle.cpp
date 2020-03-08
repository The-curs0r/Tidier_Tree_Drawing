#include "bresenhamFunctions.h"
#include <gl/glut.h>

/**   
    *   void plot_points(int x, int y)
    *   
    *   Summary of Plot Pixel function:
    *       
    *       Colors a pixel at screen location of (x,y).
    *       Uses symmetry of circle to plot the points in other regions.
    *
    *   Parameters  :  Cartesian coordinates of the point in integer
    *   
    *   Return Value : Nothing
    *
    *   Description :
    *
    *       Plot Points function uses glVertex2i(int,int) function to color
    *       the required pixel on screen.
*/
void plot_points(int xc,int yc,int x, int y)
{
  glBegin(GL_POINTS);       //Plots the points
  glVertex2i(xc+x, yc+y);
  glVertex2i(xc+x, yc-y);
  glVertex2i(xc+y, yc+x);
  glVertex2i(xc+y, yc-x);
  glVertex2i(xc-x, yc-y);
  glVertex2i(xc-y, yc-x);
  glVertex2i(xc-x, yc+y);
  glVertex2i(xc-y, yc+x);
  glEnd();
}


/**   
    *   void bresenhamCircle(int xc, int yc, int radius)
    *   
    *   Summary of Bresenham Circle function:
    *       
    *       Determines where to plot the points to closely approximate the circumference
    *       of the circle of given radius centered at point (xc,yc).
    *
    *   Parameters  :  Cartesian coordinates of the center point and radius in integers
    *   
    *   Return Value : Nothing
    *
    *   Description :
    *
    *       Bresenham's circle algorithm is a crcle drawing algorithm that determines the points of an
    *       n-dimensional raster that should be selected in order to form a close 
    *       approximation to a circle of given center and radius.It uses the symmetry of circle to
    *       reduce the number of computations.
*/
void bresenhamCircle(int xc,int yc,int r)
{
  int x=0,y=r;
  float pk=(5.0/4.0)-r;

  plot_points(xc,yc,x,y);
  int k;
  while(x < y)  //Repeat until x=y
  {
    x = x + 1;
    if(pk < 0)
      pk = pk + 2*x+1;
    else
    {
      y = y - 1;
      pk = pk + 2*(x - y) + 1;
    }
    plot_points(xc,yc,x,y);
  }
  glFlush();
}
