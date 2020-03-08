/*! \mainpage Tidier Drawings Of Trees
 *
 * \section intro_sec Introduction
 *
 * This is the documentation for Computer Graphics Assignment 1.<br>
 * Group members are : 2018A7PS0201H AKSHAY TIWARI<br>
 *                     &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;2018B5A70477H MUSHKAN SUREKHA<br>
 * Contains programs to:
 * 1. Draw a line
 * 2. Draw a circle
 * 3. Draw a tree
 * 
 * Bresenham's Line and Circle Drawing Algorithms have been used to draw line and circle respectively.<br>
 * Algorithm described in Tidier Drawings of Trees By EDWARD M. REINGOLD AND JOHN S. TILFORD (R1) has been used to
 * assign coordinates to node. They are later printed using Bresenham's Alogrithms.
 * \section install_sec Compilation Commands :
 * 1. For Line Drawing : g++ lineDrawing.cpp bresenhamLine.cpp -o LineDrawing -lopengl32 -lglew32 -lfreeglut -lglu32 (Output : LineDrawing.exe)
 * 2. For Circle Drawing : g++ circleDrawing.cpp bresenhamCircle.cpp -o CircleDrawing -lopengl32 -lglew32 -lfreeglut -lglu32 (Output : CircleDrawing.exe)
 * 3. For Tree Drawing : g++ tidierTreeDrawing.cpp bresenhamLine.cpp bresenhamCircle.cpp -o TidierTreeDrawing -lopengl32 -lglew32 -lfreeglut -lglu32 (Output : TidierTreeDrawing.exe)
 * \subsection inout Sample Inputs And Outputs With Timing Analysis :
 * 1. For Line Drawing :<br>https://docs.google.com/document/d/16EjwT9XEoPUz-Qydl9aCNqgZJaw-h6mUGWaPzc6aQxw/edit?usp=sharing
 * 2. For Circle Drawing :<br>https://docs.google.com/document/d/1as9-pjg96g8w6FEusnPrl_8lzQaXF8nRcBGiXvXXJlw/edit?usp=sharing
 * 3. For Tree Drawing :<br>https://docs.google.com/document/d/1TtxwlponClbFgAwxCS2KIOK-rhuyrojtOEuMwjrHgQU/edit?usp=sharing
 * \subsection issuecoding General Issues In Coding : 
 * 1. OpenGL setup was a really hard task. It took too much time to set up in Windows.<br>
 * 2. Bresenham's Line and Circle algorithms were implemented easily in c++ as they dont require much work.<br>
 * 3. The research paper took signficant amount of work to understand.<br>
 * 4. Algorithm implementation was not that easy but the pseudocode given helped in implementing it.<br>
 * 5. Passing wrong pointers was a mistake that took too long to recify.
 * 6. I learnt how to debug in VS Code during this course of this assignment which was used in recitifying the above mistake.
 * 7. Timing analysis also took a while to learn i.e. where to put start and end points.
 * 8. Looking up for OpenGL commands also took some time as I was unable to find good sources for them.
 * 9. We also implented a small function which allows user to select desired colors for components.
 * \subsection algoanalysis Algorithm Analysis :
 * The time required by Algorithm TR is completely determined by the while loop because SETUP iS executed exactly once per node of the tree.<br>
 * 2. Let F(T) be the number of times the test of the loop succeeds, i.e., the number of times the body of the loop is executed for a tree T.
 * 3. F(T) = n(T) - h(T). The proof can be shown by induction on N, the number of nodes in T.
 * 4. The best case is a degenerate tree in which no node has two sons; then n(T) = h(T) and the loop body is never executed. 
 * 5. The- worst case is a complete binary tree for which the loop is executed about n(T) - lg n(T) times.
 * 6. Algorithm TR can easily be extended to handle m-ary trees without affecting its linear performance.(This wasn't implemented in this assignment.)<br>
 * <br>Issues with algorithm : <br>
 * 1. Algorithm TR run into a problem for many trees in which one subtree is wide and the other consists of just a few nodes.
 * 2. A second issue in discretization is that coordinates must be given integer values.
 * \subsection rem Remarks :
 * The research paper gave us insight on how a problem as simple as drawing a tree can involve such detailed algorithm.<br>
 * Implementation of all the three algorithms was a challenging but rather fun task.<br>
 */