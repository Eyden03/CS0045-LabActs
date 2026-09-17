#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q02 - Horizontal Green Line
  ------------------------------------
 Objective: Practice GL_LINES and glLineWidth.
 This program draws one thick green horizontal line that spans most of the window.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0f, 1.0f, 0.0f);  // green
    glLineWidth(4.0f); // required line thickness

    glBegin(GL_LINES);
        glVertex2f(-0.8f, 0.0f); // left endpoint
        glVertex2f( 0.8f, 0.0f); // right endpoint
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q02 - Horizontal Green Line");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}