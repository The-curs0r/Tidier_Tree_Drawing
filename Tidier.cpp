#include <iostream>
#include <bits/stdc++.h>
#include <gl/glut.h>
using namespace std;

int minsep = 10, xc, yc, arr[100][2], i = 0, radius = 20;
struct Node *root;

struct Node
{
    struct Node *llink;
    struct Node *rlink;
    int xcoor, ycoor, offset;
    bool thread;
};

struct ExtremeDes
{
    struct Node *addr;
    int off, lev;
};

struct ExtremeDes *newExtrem()
{
    struct ExtremeDes *temp = new ExtremeDes;
    temp->addr = NULL;
    temp->off = temp->lev = -2;
    return temp;
};

struct Node *newNode()
{
    struct Node *temp = new Node;
    temp->llink = temp->rlink = NULL;
    temp->xcoor = temp->ycoor = temp->offset = 0;
    temp->thread = 0;
    return temp;
};
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
        { //Parent is a leaf
            (*rmost)->addr = parent; //Leaf is both rightmost and leftmost node of lowest level
            (*lmost)->addr = parent; //of the subtree consisting of itself
            (*rmost)->lev = level;
            (*lmost)->lev = level;
            (*rmost)->off = 0;
            (*lmost)->off = 0;
            parent->offset = 0;
        }
        else
        {                       //Parent is not a leaf
                                //Setup for subtree pushing; Place roots of subtree minimum distance apart
            cursep = minsep;
            rootsep = minsep;
            loffsum = 0;
            roffsum = 0;
            while (leftch != NULL && rightch != NULL)
            {                     //Consider each level in turn until one subtree exhausted
                                  //Push subtrees apart where necessary
                if (cursep < minsep)
                {
                    rootsep =rootsep+ (minsep - cursep); //Push apart
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

void storxy(struct Node *temp)
{
    if (!temp)
        return;
    storxy(temp->llink);
    // cout << temp->xcoor << "--" << temp->ycoor << "--" << temp->offset << "--" << temp->thread << "\n";
    arr[i][0] = 10*(temp->xcoor);
    arr[i][1] = 950 - 30 * (temp->ycoor);
    i++;
    storxy(temp->rlink);
    return;
}
// void inorder(struct Node *temp)
// {
//     if (!temp)
//         return;
//     inorder(temp->llink);
//     cout << temp->xcoor << "--" << temp->ycoor << "--" << temp->offset << "--" << temp->thread << "\n";
//     inorder(temp->rlink);
//     return;
// }

void myInit()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
    return;
}

void draw_pixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void draw_line(int xcoor1, int xcoor2, int ycoor1, int ycoor2) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;

	dx = xcoor2-xcoor1;
	dy = ycoor2-ycoor1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;
	incx = 1;
	if (xcoor2 < xcoor1) incx = -1;
	incy = 1;
	if (ycoor2 < ycoor1) incy = -1;
	x = xcoor1; y = ycoor1;
    int check1=(x-xcoor1)*(x-xcoor1)+(y-ycoor1)*(y-ycoor1)-radius*radius;
    int check2=(x-xcoor2)*(x-xcoor2)+(y-ycoor2)*(y-ycoor2)-radius*radius;
	if (dx > dy) {
        if(check1>=0 && check2>=0)
		    draw_pixel(x, y);
		e = 2 * dy-dx;
		inc1 = 2*(dy-dx);
		inc2 = 2*dy;
		for (i=0; i<dx; i++) {
            check1=(x-xcoor1)*(x-xcoor1)+(y-ycoor1)*(y-ycoor1)-radius*radius;
            check2=(x-xcoor2)*(x-xcoor2)+(y-ycoor2)*(y-ycoor2)-radius*radius;
			if (e >= 0) {
				y += incy;
				e += inc1;
			}
			else
				e += inc2;
			x += incx;
			if(check1>=0 && check2>=0)
		    draw_pixel(x, y);
		}

	} else {
		if(check1>=0 && check2>=0)
		    draw_pixel(x, y);
		e = 2*dx-dy;
		inc1 = 2*(dx-dy);
		inc2 = 2*dx;
		for (i=0; i<dy; i++) {
            check1=(x-xcoor1)*(x-xcoor1)+(y-ycoor1)*(y-ycoor1)-radius*radius;
            check2=(x-xcoor2)*(x-xcoor2)+(y-ycoor2)*(y-ycoor2)-radius*radius;
			if (e >= 0) {
				x += incx;
				e += inc1;
			}
			else
				e += inc2;
			y += incy;
			if(check1>=0 && check2>=0)
		        draw_pixel(x, y);
		}
	}
}

void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glEnd();
}

void bresenham_circle(int r)
{
    int x = 0, y = r;
    float pk = (5.0 / 4.0) - r;

    plot_point(x, y);
    int k;
    
    while (x < y)
    {
        x = x + 1;
        if (pk < 0)
            pk = pk + 2 * x + 1;
        else
        {
            y = y - 1;
            pk = pk + 2 * (x - y) + 1;
        }
        plot_point(x, y);
    }
    glFlush();
}

void drawline(struct Node *temp)
{
    if(!temp)
        return;
    int x1,x2,y1,y2;
    if(temp->llink)
    {
        x1=temp->xcoor;
        y1=temp->ycoor;
        x2=temp->llink->xcoor;
        y2=temp->llink->ycoor;
        // cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<" \n";
        draw_line(10*x1,10*x2,950-30*y1,950-30*y2);
    }
    if(temp->rlink)
    {
        x1=temp->xcoor;
        y1=temp->ycoor;
        x2=temp->rlink->xcoor;
        y2=temp->rlink->ycoor;
        // cout<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<" \n";
        draw_line(10*x1,10*x2,950-30*y1,950-30*y2);
    }
    drawline(temp->llink);
    drawline(temp->rlink);
    return;
}
void Init()
{
    /* Set clear color to white */
    glClearColor(0, 0, 0, 0);
    /* Set fill color to black */
    glColor3f(1.0, 1.0, 1.0);
    /* glViewport(0 , 0 , 640 , 480); */
    /* glMatrixMode(GL_PROJECTION); */
    /* glLoadIdentity(); */
    gluOrtho2D(0, 1000, 0, 1000);
}

void takeInput(Node* &node) {
    string left, right;
    node = newNode();

    cin >> left;
    if(left == "T") {
        i++;
        takeInput(node->llink); // taking input for left subtree
    }
    cin >> right;
        i++;
    if(right == "T") {
        takeInput(node->rlink); // taking input for right subtree
    }
    return;
}

void prog(){
    int max=i;
    for (int i = 0; i <= max; i++)
    {
        xc = arr[i][0];
        yc = arr[i][1];
        bresenham_circle(radius);
    }
    drawline(root);
}

int main(int argc, char **argv)
{
    takeInput(root);
    struct ExtremeDes *rmost = newExtrem();
    struct ExtremeDes *lmost = newExtrem();

    setup(root, 0, &rmost, &lmost);
    petrify(root, 50);
    storxy(root);

    glutInit(&argc, argv);
    /* Set the initial display mode */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    /* Set the initial window position and size */
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1000, 1000);
    /* Create the window with title "DDA_Line" */
    glutCreateWindow("Tidier_Drawing_Of_Tree");
    /* Initialize drawing colors */
    Init();
    /* Call the displaying function */
    /* Keep displaying untill the program is closed */
    glutDisplayFunc(prog);
    glutMainLoop();
    return 0;
}