/** 
    * File:    circleDrawing.cpp
    * 
    * Author1:  Akshay Tiwari (2018A7PS0201H)
    * Author2:  Mushkan Surekha  (2018B5A70477H)
    * Date:     21-02-2020 
    * Course:   Computer Graphics (IS F311) 
    * 
    * Summary of File: 
    * 
    *   Program To Display A Circle Of Given Radius At Given Center.
    *   Circle is plotted using Bresenham's Circle Drawing Algorithm. 
    * 
    * Compilation Command : g++ circleDrawing.cpp bresenhamCircle.cpp -o CircleDrawing -lopengl32 -lglew32 -lfreeglut -lglu32
*/
#include <bits/stdc++.h>
#include <math.h>
#include <GL/glut.h>
#include "bresenhamFunctions.h"

using namespace std;

int g_xc;       ///<x Coordinate of center of circle
int g_yc;       ///<y Coordinate of center of circle
int g_radius;   ///<Radius of circle
int g_hexValue; ///<Hex value of background and circle color
float g_cRed;   ///<Red Value of circle color
float g_cGreen;///<Green Value of circle color
float g_cBlue;///<Blue Value of circle color
float g_alpha = 1.0;///<Transparency of circle and background
float g_bRed;///<Red Value of background color
float g_bGreen;///<Green Value of background color
float g_bBlue;///<Blue Value of background color

/**   
    *   void myInit()
    *   
    *   Summary of myInit function:
    *       
    *       Initializes a window to display the circle.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing (Viewport window is initialized)
    *
    *   Description :
    *
    *       Initializes a window to display the circle. Background and circle
    *       colors are set to the ones given by the user. Window size is set to
    *       size of screen.
*/
void myInit()
{
    glClearColor(g_bRed, g_bGreen, g_bBlue, g_alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(g_cRed, g_cGreen, g_cBlue, g_alpha);
    glMatrixMode(GL_PROJECTION);  //Set current matrix mode to projection
    gluOrtho2D(0, 1920, 0, 1080); //Set up 2D orthographic viewing region
}
/**   
    *   void myDisplay()
    *   
    *   Summary of myInit function:
    *       
    *       Main loop function of the program.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing  (Displays the circle in viewport window)
    *
    *   Description :
    *
    *       Main loop function of the program. Keeps displaying
    *       a circle until user closes the window.
*/
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);//Clears buffers to preset values
    bresenhamCircle(g_xc, g_yc, g_radius);
}
/**   
    *   void colorInputs()
    *   
    *   Summary of colorInputs function:
    *       
    *       Takes color inputs from user.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing (Color variables are set accordingly)
    *
    *   Description :
    *
    *       Takes color inputs of background and circle from user as
    *       hex values. Sets the color variables accordingly.
*/
void colorInputs()
{
    cout << "\n\nBasic Colors With Hex Code :" << endl
         << "Black : 0x000000\nWhite : 0xFFFFFF\nRed : 0xFF0000\nLime : 0x00FF00\nBlue : 0x0000FF\nYellow : 0xFFFF00\nCyan / Aqua : 0x00FFFF" << endl
         << "Magenta / Fuchsia : 0xFF00FF\nSilver : 0xC0C0C0\nGray : 0x808080\nMaroon : 0x800000\nOlive : 0x808000\nGreen : 0x008000" << endl
         << "Purple : 0x800080\nTeal : 0x008080\nNavy : 0x000080\n\n";
    cout << "Enter Circle Color's HEX Code:\n";
    cin >> hex >> g_hexValue;
    g_cRed = ((g_hexValue >> 16) & 0xFF) / 255.0;
    g_cBlue = ((g_hexValue)&0xFF) / 255.0;
    g_cGreen = ((g_hexValue >> 8) & 0xFF) / 255.0;
    cout << "Enter Background Color's HEX Code:\n";
    cin >> hex >> g_hexValue;
    g_bRed = ((g_hexValue >> 16) & 0xFF) / 255.0;
    g_bBlue = ((g_hexValue)&0xFF) / 255.0;
    g_bGreen = ((g_hexValue >> 8) & 0xFF) / 255.0;
}
/**   
    *   int main(int argc, char **argv)
    *   
    *   Summary of main function:
    *       
    *       The core function of program. 
    *
    *   Parameters  :  Nothing (or command line inputs)
    *   
    *   Return Value : Exit code 0 when program is closed
    *
    *   Description :
    *
    *       The core function of program. First function to be called.
    *       Takes required inputs from user.
*/
int main(int argc, char **argv)
{

    float x1, y1, rad;
    cout << "Enter x coordinate :\n";
    cin >> x1;
    cout << "Enter y coordinate :\n";
    cin >> y1;
    cout << "Enter radius of circle : \n";
    cin >> rad;
    g_xc = (int)(round(x1));
    g_yc = (int)(round(y1));
    g_radius = (int)(round(rad));
    colorInputs();
    glutInit(&argc, argv);      //Initialise GLUT library 
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Set the initial display mode 
    glutInitWindowPosition(0, 0);//Set the initial window position
    glutInitWindowSize(1920, 1080);//Set the initial window size
    glutCreateWindow("Bresenham Circle Drawing");//Create the window with title "Bresenham Circle Drawing"
    myInit();   //Initializes the window with background and circle colors
    glutDisplayFunc(myDisplay);//Call the displaying function
    glutMainLoop();//Keep displaying untill the program is closed 
    return 0;
}
