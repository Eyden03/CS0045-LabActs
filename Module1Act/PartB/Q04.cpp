#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;

/*
Exercise Q04 - Orange Rectangle
  ------------------------------------
 Objective: Practice GL_POLYGON with a non-square shape.
 This program draws a filled orange rectangle that is wider than it is tall.
 */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0f, 0.4f, 0.0f); // orange

    glBegin(GL_POLYGON);
        glVertex2f(-0.8f, -0.35f); // bottom-left
        glVertex2f(-0.8f,  0.35f); // top-left
        glVertex2f( 0.8f,  0.35f); // top-right
        glVertex2f( 0.8f, -0.35f); // bottom-right
    glEnd();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Q04 - Orange Rectangle");

    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}