#include "bresenhamFunctions.h"
#include <gl/glut.h>

/**   
    *   void plotPixel(int x, int y)
    *   
    *   Summary of Plot Pixel function:
    *       
    *       Colors a pixel at screen location of (x,y)
    *
    *   Parameters  :  Cartesian coordinates of the point in integer
    *   
    *   Return Value : Nothing
    *
    *   Description :
    *
    *       Plot Pixel function uses glVertex2i(int,int) function to color
    *       the required pixel on screen.
*/
void plotPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x, y); //Plots the point
    glEnd();
}

/**   
    *   void bresenhamLine(int g_xCoor1, int g_xCoor2, int g_yCoor1, int g_yCoor2,int radius)
    *   
    *   Summary of Bresenham Line function:
    *       
    *       Determines where to plot the points to closely approximate a staright line
    *       between two given points.
    *       If radius is >0 then this function does not plot points inside the circlesof radius r
    *        centered at the endpoints. 
    *
    *   Parameters  :  Cartesian coordinates of the two points in integers
    *   
    *   Return Value : Nothing
    *
    *   Description :
    *
    *       Bresenham's line algorithm is a line drawing algorithm that determines the points of an
    *       n-dimensional raster that should be selected in order to form a close 
    *       approximation to a straight line between two points.
*/
void bresenhamLine(int g_xCoor1, int g_xCoor2, int g_yCoor1, int g_yCoor2,int radius)
{
    int i, decisionVar;
    int incX, incY, incrNE, incrE;
    int dx = g_xCoor2 - g_xCoor1;
    int dy = g_yCoor2 - g_yCoor1;

    //Changes order of points if necessary
    incX = 1;
    if (g_xCoor2 < g_xCoor1)
        incX = -1;
    incY = 1;
    if (g_yCoor2 < g_yCoor1)
        incY = -1;
    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;

    int x = g_xCoor1;
    int y = g_yCoor1;

    int check1=(x-g_xCoor1)*(x-g_xCoor1)+(y-g_yCoor1)*(y-g_yCoor1)-radius*radius;
    int check2=(x-g_xCoor2)*(x-g_xCoor2)+(y-g_yCoor2)*(y-g_yCoor2)-radius*radius;

    if (dx > dy) // slope<1
    {
        if(check1>=0 && check2>=0)
		    plotPixel(x, y);
        decisionVar = 2 * dy - dx;
        incrNE = 2 * (dy - dx);
        incrE = 2 * dy;
        for (i = 0; i < dx; i++)
        {
            int check1=(x-g_xCoor1)*(x-g_xCoor1)+(y-g_yCoor1)*(y-g_yCoor1)-radius*radius;
            int check2=(x-g_xCoor2)*(x-g_xCoor2)+(y-g_yCoor2)*(y-g_yCoor2)-radius*radius;
            if (decisionVar >= 0) //Midpoint (x+1,y+1/2) is below line, select NE pixel.
            {
                y += incY;
                decisionVar += incrNE;
            }
            else //Midpoint (x+1,y+1/2) is above line, select E pixel.
                decisionVar += incrE;
            x += incX;
            if(check1>=0 && check2>=0)
		        plotPixel(x, y);
        }
    }
    else // slope>=1
    {
        if(check1>=0 && check2>=0)
		    plotPixel(x, y);
        decisionVar = 2 * dx - dy;
        incrNE = 2 * (dx - dy);
        incrE = 2 * dx;
        for (i = 0; i < dy; i++)
        {
            int check1=(x-g_xCoor1)*(x-g_xCoor1)+(y-g_yCoor1)*(y-g_yCoor1)-radius*radius;
            int check2=(x-g_xCoor2)*(x-g_xCoor2)+(y-g_yCoor2)*(y-g_yCoor2)-radius*radius;   
            if (decisionVar >= 0) //Midpoint (x+1/2,y+1) is below line, select N pixel.
            {
                x += incX;
                decisionVar += incrNE;
            }
            else //Midpoint (x+1/2,y+1) is above line, select NE pixel.
                decisionVar += incrE;
            y += incY;
           if(check1>=0 && check2>=0)
		        plotPixel(x, y);
        }
    }
}