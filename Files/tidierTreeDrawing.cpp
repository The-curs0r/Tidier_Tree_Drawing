/** 
    * File:    tidierTreeDrawing.cpp
    * 
    * Author1:  Akshay Tiwari (2018A7PS0201H)
    * Author2:  Mushkan Surekha  (2018B5A70477H)
    * Date:     21-02-2020 
    * Course:   Computer Graphics (IS F311) 
    * 
    * Summary of File: 
    * 
    *   Program to print a given tree on the screen.
    *   Algorithm for finding the coordinates is given in this 
    *   research paper : Tidier Drawings of Trees By
    *   EDWARD M. REINGOLD AND JOHN S. TILFORD. (R1)
    * 
    * Compilation Command : g++ tidierTreeDrawing.cpp bresenhamLine.cpp bresenhamCircle.cpp -o TidierTreeDrawing -lopengl32 -lglew32 -lfreeglut -lglu32
*/
#include <bits/stdc++.h>
#include <gl/glut.h>
#include "bresenhamFunctions.h"

using namespace std;

int minsep = 10;     ///<Minimum separation between nodes in x direction
int xc;              ///<x Coordinate of center of node being plotted
int yc;              ///<y Coordinate of center of node being plotted
int arr[100][2];     ///<Array to store x and y Coordinate of center of nodes after petrify function
int i = 0;           ///<Loop variable
int radius = 20;     ///<Radius of each node
int g_hexValue;      ///<Hex value of background and edge and node color
float g_lRed;        ///<Red Value of edge color
float g_lGreen;      ///<Green Value of edge color
float g_lBlue;       ///<Blue Value of edge color
float g_alpha = 1.0; ///<Transparency of edge and node and background
float g_bRed;        ///<Red Value of background color
float g_bGreen;      ///<Green Value of background color
float g_bBlue;       ///<Blue Value of background color
float g_cRed;        ///<Red Value of node color
float g_cGreen;      ///<Green Value of node color
float g_cBlue;       ///<Blue Value of node color
struct Node *root;   ///<Pointer to root node of the tree

struct Node
{
    struct Node *llink; ///<Pointer to left subtree of node
    struct Node *rlink; ///<Pointer to right subtree of node
    int xcoor;          ///<Absolute x coordinate of node
    int ycoor;          ///<Absolute y coordinate of node
    int offset;         ///<Distance to each child
    bool thread;        ///<Boolean value indicating if threading is required
};

struct ExtremeDes
{
    struct Node *addr; ///<Pointer to address of node
    int off;           ///<Offset from root of subtree
    int lev;           ///<Current tree level
};
/**   
    *   struct ExtremeDes *newExtrem()
    *   
    *   Summary of ExtremeDes function:
    *       
    *       Creates a new ExtremeDes structure and returns it.
    *
    *   Parameters  :  None
    *   
    *   Return Value : Newly generated ExtremeDes.
    *
    *   Description :
    *
    *       Creates a new ExtremeDes structure by setting up 
    *       required paremeters and returns it.
*/
struct ExtremeDes *newExtrem()
{
    struct ExtremeDes *temp = new ExtremeDes;
    temp->addr = NULL;
    temp->off = temp->lev = -2;
    return temp;
};
/**   
    *   struct Node *newNode()
    *   
    *   Summary of newNode function:
    *       
    *       Creates a new Node structure and returns it.
    *
    *   Parameters  :  None
    *   
    *   Return Value : Newly generated Node.
    *
    *   Description :
    *
    *       Creates a new Node structure by setting up 
    *       required paremeters and returns it.
*/
struct Node *newNode()
{
    struct Node *temp = new Node;
    temp->llink = temp->rlink = NULL;
    temp->xcoor = temp->ycoor = temp->offset = 0;
    temp->thread = 0;
    return temp;
};
/**   
    *   void setup(struct Node *parent, int level, ExtremeDes **rmost, ExtremeDes **lmost)
    *   
    *   Summary of setup function:
    *       
    *       Implements algorithm given in the research paper R1.
    *
    *   Parameters  :  Node pointer pointing to root of the tree
    *                  Current level of corresponding subtree.
    *                  Rightmost and leftmost extreme descendants of current subtree.
    *   
    *   Return Value : Nothing (Relative positioning to all nodes is assigned)
    *
    *   Description :
    *
    *       This procedure implements the algorithm in R1, assigning relative
    *       positionings to all nodes in the tree pointed to by root node.
*/
void setup(struct Node *parent, int level, ExtremeDes **rmost, ExtremeDes **lmost) //rmost and lmost are extreme descendants
{

    struct Node *leftch = newNode();              //Left child of parent
    struct Node *rightch = newNode();             //Right child of parent
    struct ExtremeDes *left_right = newExtrem();  //Rightmost node on lowest level of left subtree of parent
    struct ExtremeDes *left_left = newExtrem();   //Leftmost node on lowest level of left subtree of parent
    struct ExtremeDes *right_left = newExtrem();  //Leftmost node on lowest level of right subtree of parent
    struct ExtremeDes *right_right = newExtrem(); //Rightmost node on lowest level of right subtree of parent
    int cursep, rootsep;                          //Separation at current level;Current separation at parent node
    int loffsum, roffsum;                         //Offset from left and right sons to parent

    if (parent == NULL)
    {
        (*lmost)->lev = -1; //Avoid selecting as extreme
        (*rmost)->lev = -1;
        return;
    }
    else
    {
        parent->ycoor = level;   //Y coordinate of parent is its level (decr???)
        leftch = parent->llink;  //Follows contour of left subtree
        rightch = parent->rlink; //Follows contour of right subtree
        // left_left->addr = leftch;
        // left_right->addr = leftch;
        // right_left->addr = rightch;
        // right_right->addr = rightch;
        setup(leftch, level + 1, &left_right, &left_left);    //Position left subtree recursively
        setup(rightch, level + 1, &right_right, &right_left); //Position right subtree recursively
        if (rightch == NULL && leftch == NULL)
        {                            //Parent is a leaf
            (*rmost)->addr = parent; //Leaf is both rightmost and leftmost node of lowest level
            (*lmost)->addr = parent; //of the subtree consisting of itself
            (*rmost)->lev = level;
            (*lmost)->lev = level;
            (*rmost)->off = 0;
            (*lmost)->off = 0;
            parent->offset = 0;
        }
        else
        { //Parent is not a leaf
            //Setup for subtree pushing; Place roots of subtree minimum distance apart
            cursep = minsep;
            rootsep = minsep;
            loffsum = 0;
            roffsum = 0;
            while (leftch != NULL && rightch != NULL)
            { //Consider each level in turn until one subtree exhausted
                //Push subtrees apart where necessary
                if (cursep < minsep)
                {
                    rootsep = rootsep + (minsep - cursep); //Push apart
                    cursep = minsep;
                }
                //Advance leftch and rightch
                if (leftch->rlink != NULL)
                {
                    loffsum = loffsum + leftch->offset;
                    cursep = cursep - leftch->offset;
                    leftch = leftch->rlink;
                }
                else
                {
                    loffsum = loffsum - leftch->offset;
                    cursep = cursep + leftch->offset;
                    leftch = leftch->llink;
                }
                if (rightch->llink != NULL)
                {
                    roffsum = roffsum - rightch->offset;
                    cursep = cursep - rightch->offset;
                    rightch = rightch->llink;
                }
                else
                {
                    roffsum = roffsum + rightch->offset;
                    cursep = cursep + rightch->offset;
                    rightch = rightch->rlink;
                }
            }

            parent->offset = (rootsep + 1) / 2; //Set offset in parent node
            loffsum = loffsum - parent->offset; //Accumulate offset of parent in Accumulated loffset
            roffsum = roffsum + parent->offset; //Accumulate offset of parent in Accumulated roffset

            //For lmost
            if ((right_left->lev > left_left->lev) || (parent->llink == NULL))
            {
                *lmost = right_left;
                (*lmost)->off = (*lmost)->off + parent->offset;
            }
            else
            {
                *lmost = left_left;
                (*lmost)->off = (*lmost)->off - parent->offset;
            }

            //For rmost
            if ((left_right->lev > right_right->lev) || (parent->rlink == NULL))
            {
                *rmost = left_right;
                (*rmost)->off = (*rmost)->off - parent->offset;
            }
            else
            {
                *rmost = right_right;
                (*rmost)->off = (*rmost)->off + parent->offset;
            }

            //If subtree of parent were of uneven heights,check to see if threading necessary.
            //Atmost one thread needs to be inserted
            if (leftch != NULL && leftch != parent->llink)
            {
                right_right->addr->thread = true;
                right_right->addr->offset = abs((right_right->off + parent->offset) - loffsum);
                if ((loffsum - parent->offset) <= right_right->off)
                {
                    right_right->addr->llink = leftch;
                }
                else
                {
                    right_right->addr->rlink = leftch;
                }
            }
            else if (rightch != NULL && rightch != parent->rlink)
            {
                left_left->addr->thread = true;
                left_left->addr->offset = abs((left_left->off - parent->offset) - roffsum);
                if (roffsum - parent->offset >= left_left->off)
                {
                    left_left->addr->rlink = rightch;
                }
                else
                {
                    left_left->addr->llink = rightch;
                }
            }
        }
        return;
    }
}
/**   
    *   void petrify(struct Node *parent, int xpos)
    *   
    *   Summary of petrify function:
    *       
    *       Converts relative offsets of all node to absolute coordinates.
    *
    *   Parameters  :  Node pointer pointing to root of the tree
    *                  X coordinate of root of tree.
    *   
    *   Return Value : Nothing (Absolute coordinates are generated and stored)
    *
    *   Description :
    *
    *      This procedure performs a preorder tranversal of the tree and
    *      converts relative offsets of all node to absolute coordinates.
*/
void petrify(struct Node *parent, int xpos)
{
    if (parent != NULL)
    {
        parent->xcoor = xpos;
        if (parent->thread)
        {
            parent->thread = false;
            parent->rlink = NULL;
            parent->llink = NULL;
        }
        petrify(parent->llink, xpos - parent->offset);
        petrify(parent->rlink, xpos + parent->offset);
    }
    return;
}
/**   
    *   void storxy(struct Node *temp)
    *   
    *   Summary of storxy function:
    *       
    *       Stores the final centers of nodes in a 2D array.
    *
    *   Parameters  :  Node pointer pointing to root of the tree
    *   
    *   Return Value : Nothing (Centers are stored in array)
    *
    *   Description :
    *
    *       Stores the centers of nodes after adjustment in a 2D array.
    *       X coordinate stored first, then Y coordinate is stored.
*/
void storxy(struct Node *temp)
{
    if (!temp)
        return;
    storxy(temp->llink);
    arr[i][0] = 10 * (temp->xcoor);
    arr[i][1] = 950 - 30 * (temp->ycoor);
    i++;
    storxy(temp->rlink);
    return;
}
/**   
    *   void drawline(struct Node *temp)
    *   
    *   Summary of myInit function:
    *       
    *       Draws the edges of the tree.
    *
    *   Parameters  :  Node pointer pointing to root of the tree
    *   
    *   Return Value : Nothing (Edges of tre are displayed in viewport)
    *
    *   Description :
    *
    *       Draws the edges of the tree using Bresenham line function.
    *       Line is plotted between center of two circles.
    *       Does not plot the edges if they are within the node circle.
*/
void drawline(struct Node *temp)
{
    if (!temp)
        return;
    int x1, x2, y1, y2;
    if (temp->llink)
    {
        x1 = temp->xcoor;
        y1 = temp->ycoor;
        x2 = temp->llink->xcoor;
        y2 = temp->llink->ycoor;
        bresenhamLine(10 * x1, 10 * x2, 950 - 30 * y1, 950 - 30 * y2, radius);
    }
    if (temp->rlink)
    {
        x1 = temp->xcoor;
        y1 = temp->ycoor;
        x2 = temp->rlink->xcoor;
        y2 = temp->rlink->ycoor;
        bresenhamLine(10 * x1, 10 * x2, 950 - 30 * y1, 950 - 30 * y2, radius);
    }
    drawline(temp->llink);
    drawline(temp->rlink);
    return;
}
/**   
    *   void myInit()
    *   
    *   Summary of myInit function:
    *       
    *       Initializes a window to display the tree.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing (Viewport window is initialized)
    *
    *   Description :
    *
    *       Initializes a window to display the tree. Background and tree
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
    *   void takeInput()
    *   
    *   Summary of takeInput function:
    *       
    *       Takes tree as input from user.
    *
    *   Parameters  :  Node pointer pointing to root of the tree
    *   
    *   Return Value : Nothing (Generates a binary tree according to input)
    *
    *   Description :
    *
    *       Takes nodes of tree as input from user. Input is taken in inorder fashion
    *       i.e. if left tree exists then input T and recurse into that tree.
    *       Then recurse back taking input for right subtrees of each node.
*/
void takeInput(Node *&node)
{
    string left, right;
    node = newNode();

    cin >> left;
    if (left == "T")
    {
        i++;
        takeInput(node->llink); // taking input for left subtree
    }
    cin >> right;
    i++;
    if (right == "T")
    {
        takeInput(node->rlink); // taking input for right subtree
    }
    return;
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
    *       Takes color inputs of background and edge and node from user as
    *       hex values. Sets the color variables accordingly.
*/
void colorInputs()
{
    cout << "\n\nBasic Colors With Hex Code :" << endl
         << "Black : 0x000000\nWhite : 0xFFFFFF\nRed : 0xFF0000\nLime : 0x00FF00\nBlue : 0x0000FF\nYellow : 0xFFFF00\nCyan / Aqua : 0x00FFFF" << endl
         << "Magenta / Fuchsia : 0xFF00FF\nSilver : 0xC0C0C0\nGray : 0x808080\nMaroon : 0x800000\nOlive : 0x808000\nGreen : 0x008000" << endl
         << "Purple : 0x800080\nTeal : 0x008080\nNavy : 0x000080\n\n";
    cout << "Enter Node Color's HEX Code:\n";
    cin >> hex >> g_hexValue;
    g_cRed = ((g_hexValue >> 16) & 0xFF) / 255.0;
    g_cBlue = ((g_hexValue)&0xFF) / 255.0;
    g_cGreen = ((g_hexValue >> 8) & 0xFF) / 255.0;
    cout << "Enter Edge Color's HEX Code:\n";
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
    *   void myDisplay()
    *   
    *   Summary of myInit function:
    *       
    *       Main loop function of the program.
    *
    *   Parameters  :  Nothing
    *   
    *   Return Value : Nothing  (Displays the tree in viewport window)
    *
    *   Description :
    *
    *       Main loop function of the program. Keeps displaying
    *       a tree until user closes the window.
*/
void myDisplay()
{
    glColor4f(g_cRed, g_cGreen, g_cBlue, g_alpha);
    int max = i;
    for (int i = 0; i < max; i++)
    {
        xc = arr[i][0];
        yc = arr[i][1];
        bresenhamCircle(xc, yc, radius);
    }
    glColor4f(g_lRed, g_lGreen, g_lBlue, g_alpha);
    drawline(root);
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
    cout << "Input the tree : ";
    takeInput(root);
    colorInputs();
    struct ExtremeDes *rmost = newExtrem();
    struct ExtremeDes *lmost = newExtrem();
    setup(root, 0, &rmost, &lmost);
    petrify(root, 94);
    i = 0;
    storxy(root);
    glutInit(&argc, argv);                       //Initialise GLUT library
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //Set the initial display mode
    glutInitWindowSize(1920, 1080);              //Set the initial window size
    glutInitWindowPosition(0, 0);                //Set the initial window position
    glutCreateWindow("Tidier Drawing Of Tree");  //Create the window with title "Tidier Drawing Of Tree"
    myInit();                                    //Initializes the window with background and line colors
    glutDisplayFunc(myDisplay);                  //Call the displaying function
    glutMainLoop();                              //Keep displaying untill the program is closed
    return 0;
}