/** 
    * File:    lineDrawing.cpp
    * 
    * Author1:  Akshay Tiwari (2018A7PS0201H)
    * Author2:  Mushkan Surekha  (2018B5A70477H)
    * Date:     21-02-2020 
    * Course:   Computer Graphics (IS F311) 
    * 
    * Summary of File: 
    * 
    *   Program To Display A Line Between Two Points
    *   Line is plotted using Bresenham's Line Drawing Algorithm. 
    * 
    * Compilation Command : g++ lineDrawing.cpp bresenhamLine.cpp -o LineDrawing -lopengl32 -lglew32 -lfreeglut -lglu32
*/
#include <gl/glut.h>
#include <bits/stdc++.h>
#include "bresenhamFunctions.h"

using namespace std;

int g_xCoor1;        ///<x Coordinate of first point
int g_yCoor1;        ///<y Coordinate of first point
int g_xCoor2;        ///<x Coordinate of second point
int g_yCoor2;        ///<y Coordinate of second point
int g_hexValue;      ///<Hex value of background and line color
float g_lRed;        ///<Red Value of line color
float g_lGreen;      ///<Green Value of line color
float g_lBlue;       ///<Blue Value of line color
float g_alpha = 1.0; ///<Transparency of line and background
float g_bRed;        ///<Red Value of background color
float g_bGreen;      ///<Green Value of background color
float g_bBlue;       ///<Blue Value of background color

/**   
    *   void myInit()
    *   
    *   Summary of myInit function:
    *       
    *       Initializes a window to display the line.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing (Viewport window is initialized)
    *
    *   Description :
    *
    *       Initializes a window to display the line. Background and line
    *       colors are set to the ones given by the user. Window size is set to
    *       size of screen.
*/
void myInit()
{
    glClearColor(g_bRed, g_bGreen, g_bBlue, g_alpha);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor4f(g_lRed, g_lGreen, g_lBlue, g_alpha);
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
    *   Return Value : Nothing  (Displays the line in viewport window)
    *
    *   Description :
    *
    *       Main loop function of the program. Keeps displaying
    *       a line between given points until user closes the window.
*/
void myDisplay()
{
    bresenhamLine(g_xCoor1, g_xCoor2, g_yCoor1, g_yCoor2, 0);
    glFlush();
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
    *       Takes color inputs of background and line from user as
    *       hex values. Sets the color variables accordingly.
*/
void colorInputs()
{
    cout << "\n\nBasic Colors With Hex Code :" << endl
         << "Black : 0x000000\nWhite : 0xFFFFFF\nRed : 0xFF0000\nLime : 0x00FF00\nBlue : 0x0000FF\nYellow : 0xFFFF00\nCyan / Aqua : 0x00FFFF" << endl
         << "Magenta / Fuchsia : 0xFF00FF\nSilver : 0xC0C0C0\nGray : 0x808080\nMaroon : 0x800000\nOlive : 0x808000\nGreen : 0x008000" << endl
         << "Purple : 0x800080\nTeal : 0x008080\nNavy : 0x000080\n\n";
    cout << "Enter Line Color's HEX Code:\n";
    cin >> hex >> g_hexValue;
    g_lRed = ((g_hexValue >> 16) & 0xFF) / 255.0;
    g_lBlue = ((g_hexValue)&0xFF) / 255.0;
    g_lGreen = ((g_hexValue >> 8) & 0xFF) / 255.0;
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
    float x1, y1, x2, y2;
    cout << "Enter first point :\n";
    cin >> x1 >> y1;
    cout << "Enter second point :\n";
    cin >> x2 >> y2;
    g_xCoor1 = (int)(round(x1));
    g_xCoor2 = (int)(round(x2));
    g_yCoor1 = (int)(round(y1));
    g_yCoor2 = (int)(round(y2));
    colorInputs();

    glutInit(&argc, argv);  //Initialise GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//Set the initial display mode 
    glutInitWindowSize(1920, 1080);//Set the initial window size
    glutInitWindowPosition(0, 0);//Set the initial window position
    glutCreateWindow("Bresenham Line Drawing");//Create the window with title "Bresenham Line Drawing"
    myInit();//Initializes the window with background and line colors
    glutDisplayFunc(myDisplay);//Call the displaying function
    glutMainLoop();//Keep displaying untill the program is closed 
    return 0;
}